// Djordje Stankovic IN13/2018

// Iz tabele mi se ne brisu parametri funkcija, jer onda ne mogu da proverim argumente pri pozivu funkcije, ako ne koristim neku novu strukturu (TODO:)
// Pri proveri mogucnosti definisanja varijabli moze da se gleda lookup na VAR za celu tabelu, jer se samo varijable i brisu na kraju funkcija, nema ponavljanja gore, pa ce uvek da se misli na funkciju u kojoj smo trenutno, iako sam drugacije implementirao
// Ne prosirivati tabelu simbola, nego dodavati strukture ovde (nizove, matrice, itd.)

// Nacin na koji "menjamo" atribute u tabeli simbola je samo menjanjem unosa pri pozivanju insert_symbol ili set_atr, ne menja se nista u symtab.h i .c

/*
Default atributi u Tabeli Simbola :
Atribut 1 :
- Za lokalnu promenljivu - redni broj promenljive (u funkciji, u opsegu),
- Za parametar - redni broj parametra,
- Za funkciju – broj parametara,
- Za ostale simbole - nije definisano.
Atribut 2 :
- Za funkcije - tip parametra,
- Za ostale simbole - nije definisano

Moje izmene :
Za parametar je atr2 indeks funkcije za koji je
*/

// TODO: Matrica umesto parametri u tabeli simbola
// Ako to radimo tako moramo da menjamo dosta stvari koje proveravaju postojanje parametara u tabeli simbola, kao npr parametri u definisanju funkcie
// Mozda moze i bez ovoga, samo da nastavim

// TODO: int prvavar = 3; unsigned drugavar = 3u; ne moze?

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "defs.h"
	#include "symtab.h"
	#include <string.h> // Za strcmp

	int yyparse(void);
	int yylex(void);
	int yyerror(char *s);
	void warning(char *s);

	extern int yylineno;
	char char_buffer[CHAR_BUFFER_LENGTH];
	int error_count = 0;
	int warning_count = 0;
	int var_num = 0; // Trenutan broj lokalnih varijabli u funkciji, resetuje se za svaku funkciju
	int fun_idx = -1; // Indeks funkcije u kojoj se trenutno nalazimo
	int fcall_idx = -1; // Indeks funkcije koju pozivamo

	// Dodaci
	int vartype = 0;
	int return_flag = 0;
	int parameter_number = 0; // Brojac parametara pri definisanju funkcije, potreban za atr1 funkcije u tabeli simbola
	int argument_number = 0;
	unsigned switch_type = 0; // TODO: Zasto unsigned? Da li je i bitno uopste?
	int switch_number = 0;
	int switch_array[100] = {-2147483648}; // Sve se inicijalizuje na INT_MIN, niz se koristi za proveru vec koriscenih literala u switch_statement
%} 

%union {
	int i;
	char *s;
}

%token <i> TYPE
%token IF
%token ELSE
%token RETURN
%token <s> ID
%token <s> INT_NUMBER
%token <s> UINT_NUMBER
%token LPAREN
%token RPAREN
%token LCURLYBRACKET
%token RCURLYBRACKET
%token ASSIGN
%token SEMICOLON
%token <i> AROP
%token <i> RELOP

%token <i> VOIDTYPE
%token COMMA
%token INCREMENT
%token FOR
%token TO
%token STEP
%token SWITCH
%token CASETOKEN
%token ARROW
%token OTHERWISE
%token FINISH
%token LSQUAREBRACKET
%token RSQUAREBRACKET

// Ovde arguments umesto argument
%type <i> num_exp exp literal function_call arguments rel_exp

%nonassoc ONLY_IF
%nonassoc ELSE

%%

program
	: function_list
		{  
			// Javlja gresku ako main() uopste ne postoji u tabeli simbola
			if(lookup_symbol("main", FUN) == NO_INDEX)
				err("Undefined reference to 'main'.\n");
		 }
	;

function_list
	: function
	| function_list function
	;

function
	: TYPE ID
		{
			// fun_idx je indeks ove funkcije
			// Trazimo da li postoji funkcija u tabeli
			fun_idx = lookup_symbol($2, FUN);
			if(fun_idx == NO_INDEX){
				// Ako ne postoji funkcija, dodaj je, bez atributa
				fun_idx = insert_symbol($2, FUN, $1, NO_ATR, NO_ATR);
				}
			else 
				err("Redefinition of function '%s'.\n", $2);
		}
	LPAREN parameters_full 
		{
			// Kada analiziramo sve parametre, update-ujemo broj parametra za simbol funkcije
			set_atr1(fun_idx, parameter_number);
		}
	RPAREN body
		{
			// Kada se funkcija zavrsi moramo da izbrisemo sve njene lokalne varijable (TODO: ne diramo parametre, jer ih koristimo za pozive funkcija) 
			// clear_symbols brise od ovog indeksa pa na dole, pa ce nam ostati samo TODO: parametri
			int var_start_index = fun_idx + parameter_number + 1;
			clear_symbols(var_start_index);
			var_num = 0;
			// Non-void funkcije moraju imati povratnu vrednost, pa koristimo flag da proverimo da li smo ga iskoristili
			if(return_flag == 0)
				warn("Function '%s' needs to have the 'return' keyword.\n", $2);
			// Resetujemo return flag za nove funkcije
			return_flag = 0;
			// Resetujemo broj parametra za nove funkcije
			parameter_number = 0;
		}
	| VOIDTYPE ID
		{
			fun_idx = lookup_symbol($2, FUN);
			if(fun_idx == NO_INDEX){
				fun_idx = insert_symbol($2, FUN, $1, NO_ATR, NO_ATR);
			}
			else 
				err("Redefinition of function '%s'.\n", $2);
		}
	LPAREN parameters_full 
		{
			set_atr1(fun_idx, parameter_number);
		}
	RPAREN body
		{
			clear_symbols(fun_idx + parameter_number + 1);
			var_num = 0;
			// Jedina razlika u odnosu na gornju alternativu - ovde ne proveravamo return_flag kao gore jer void funkcije nemaju povratnu vrednost
			return_flag = 0;
			parameter_number = 0;
		}
	;

parameters_full
	: /* empty */
		{
			set_atr1(fun_idx, 0);
		}
	| parameters
	/*  Moramo da razdvojimo parametre u 3 dela (3 pojma) zbog rekurzije.
		Da smo pisali u 2 bilo bi
		parameters_full : | parameter | parameters_full COMMA parameter
		onda bi proslo int f(, int a, int b){},
		jer bi empty gledao kao jedan parametar,
		a ovako kazemo da ova alternativa moze imati >= 1 parametar. */
	;

parameters
	: parameter
	| parameters COMMA parameter
	;

parameter
	: TYPE ID // Parametar ne moze biti VOIDTYPE
		{
			// Pre ubacivanja proveravamo da li je trenutni parametar vec definisan za trenutnu funkciju preko tabele simbola
			// Gledamo od indeksa funkcije do kraja tabele, jer varijabli nema
			// Ne ubrajamo simbol funkcije za slucaj int foo(unsigned foo){...}
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $2) == 0){
					err("Redifinition of parameter '%s'.\n", $2);
				}
			}
			// Za svaki parametar koji prodje moramo da povecamo broj parametara za atr1 funkcije
			parameter_number++;
			// Pri ubacivanju se postavlja redni broj parametra, kao i indeks funkcije za koji je
			insert_symbol($2, PAR, $1, parameter_number, fun_idx); 
		}
	;

body
	: LCURLYBRACKET variable_list statement_list RCURLYBRACKET
	;

// variable_list moze da ima vise linija definicija, gde svaka linija moze da ima ili jednu ili vise varijabli
// Da smo stavili variable_list : | variable_list variables SEMICOLON to bi bila samo jedna linija
variable_list
	: /* empty */
	| variable_list variables_def_line
	;

variables_def_line
	: TYPE // Ne moze biti VOIDTYPE, a sve varijable u liniji imaju isti tip
		{
			// Mora u ovoj akciji da se izmeni vartype, da bi mogao da se koristi u variables_only
			vartype = $1;
		}
	variables_only SEMICOLON 
		{
			// Kada smo iskoristili vartype, moramo da ga resetujemo (cim se napravi variables_def_line)
			vartype = 0;
		}
	;

variables_only
	: ID
		{
			// Pri deklarisanju varijable trebamo da proverimo da li vec u toj trenutnoj funkciji postoje varijable ili parametri sa tim imenom
			// To znaci da varijabla moze imati isto ime kao neka prethodna funkcija ili njeni parametri
			// Ne mozemo da gledamo po lookup_symbol(VAR|PAR) jer to gleda celu tabelu (od nazad pa do 13. registra (FUNREG)) 
			// To pravi problem zbog parametara, jer se oni ne brisu na kraju funkcije
			// Idemo od indeksa funkcije u kojoj je deklarisana varijabla (fun_idx) do kraja tabele
			// Ne gledamo sam simbol funkcije jer lokalna varijabla moze da ima isto ime kao njena funkcija
			// Poredimo imena sa svakim simbolom (varijable i parametri), i ako se poklopi javljamo gresku, ako ne nadje isto ime dodajemo
			// Za tip varijable koristimo vartype koji je postavljen u variables_def_line

			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), $1) == 0){
					err("Variable or parameter by the name '%s' already exists.\n", $1);
				}
			}
			var_num++;
			insert_symbol($1, VAR, vartype, var_num, NO_ATR);
		}
	| variables_only COMMA ID
		{
			// Ista provera i za ovu alternativu
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), $3) == 0){
					err("Variable or parameter by the name '%s' already exists.\n", $3);
				}
			}
			var_num++;
			insert_symbol($3, VAR, vartype, var_num, NO_ATR);
		}
	;

statement_list
	: /* empty */
	| statement_list statement
	;

statement
	: compound_statement
	| assignment_statement
	| function_call SEMICOLON
	| if_statement
	| return_statement
	| increment_statement // Za a++;
	| loop
	| switch_statement // Ovime ne sprecavamo switch u switch-u, mada se to nece ni pregledati
	;

compound_statement
	: body // Bilo je LCURLYBRACKET statement_list RCURLYBRACKET
	// TODO: Moram da razlikujem svaki compound_statement, da bi nove definisane promenljive u tom telu bile nezavisne od starijih
	// To cu uraditi za sledecu tacku, za sad se mogu definisati samo one koje se nisu pre
	;

assignment_statement
	: ID ASSIGN num_exp SEMICOLON
		{
		int idx = lookup_symbol($1, VAR|PAR);
		if(idx == NO_INDEX)
			err("Invalid lvalue '%s' in assignment.\n", $1);
		else
			if(get_type(idx) != get_type($3))
			err("Incompatible types in assignment.\n");
		}
	;

num_exp
	: exp
	| num_exp AROP exp
		{
		if(get_type($1) != get_type($3))
			err("Invalid operands: arithmetic operation (incompatible types).\n");
		}
	;

exp
	: literal
	| ID increment_optional
		{
			// Moglo je i da se odvoji na ID i ID INCREMENT ovde, mozda preglednije
			$$ = lookup_symbol($1, VAR|PAR);
			if($$ == NO_INDEX)
				err("'%s' undeclared.\n", $1);
		}
	| function_call
	| LPAREN num_exp RPAREN
		{ $$ = $2; }
	;

literal
	: INT_NUMBER
		{ $$ = insert_literal($1, INT); }

	| UINT_NUMBER
		{ $$ = insert_literal($1, UINT); }
	;

increment_optional
	: /* empty */
	| INCREMENT
	;

function_call
	: ID 
		{
			// Ovo je indeks funkcije koju pozivamo u tabeli simbola, koristi se kod argumenata
			fcall_idx = lookup_symbol($1, FUN); 
			if(fcall_idx == NO_INDEX)
				err("'%s' is not a function.\n", $1);
		}
	LPAREN argument_list RPAREN
		{
			// Resetujemo broj argumenata za neki drugi poziv funkcije
			argument_number = 0;
			// function_call dobija semanticku vrednost
			$$ = lookup_symbol($1, FUN);
		}
	;

argument_list
	: /* empty */
		{
			// Ako nismo prosledili argumente, moramo da proverimo da li funkcija zapravo zahteva parametre
			if(get_atr1(fcall_idx) > 0)
				err("Function requires arguments!\n");
		}
	| arguments
	;

// Mora da se doda kao poseban pojam da ne bi proslo nesto kao
// b = f(,a,c);
// TODO: Ne moze poziv funkcije sa num_exp, ali moze sa ID i sa literalom - to znaci da ne moze f(a+b) ili f(g())
// num_exp ima exp koji ima ID u sebi, pa ne moze da se stavi ovde samo num_exp
// Ovo cu popraviti za sledecu tacku
arguments
	: ID
		{
			// Ovo je samo za pozive funkcija koje imaju 1 parametar
			// Argument u pozivu funkcije moze da bude varijabla i parametar trenutne funkcije, pa njih trazimo
			// Ne mozemo da trazimo po VAR|PAR po celoj tabeli kao pre jer bi to uzelo i parametre drugih funkcija, tako da moramo samo za trenutnu
			int flag = 0;
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				int argument = lookup_symbol(get_name(j), VAR|PAR); 
				// Treba za else if, ok je ovde da stoji VAR|PAR jer ne moze ispod indeksa funkcije da nadje parametar neke druge
				if(strcmp(get_name(j), $1) == 0){
					flag = 1;
					// Pronasao varijablu ili parametar te funkcije sa istim imenom
					argument_number = 1; // Sa 0 na 1
					// Ovo proverava broj parametara funkcije koja je pozvana
					if ((get_atr1(fcall_idx) == 1) && (argument_number != get_atr1(fcall_idx)))
						err("Wrong number of arguments sent over to function '%s'", get_name(fcall_idx));
					// Ako smo ovde dospeli, to znaci da funkcija ima tacno jedan parametar
					// Proveravamo da li je tip argumenta isti kao tip parametra
					// Taj parametar je na prvom indeksu ispod funkcije u tabeli simbola, pa je umesto ovog argument_number moglo da stoji i 1
					if (get_type(argument) != get_type(fcall_idx + argument_number)) 
						err("Forwarded argument '%s' of wrong type.\n", $1);
				}
			}
			if(flag == 0)
			// Ako ne nadje znaci da nije definisan
			err("Argument '%s' is not defined.\n", $1);
		}
	| arguments COMMA ID
		{
			// Za prvi argument u listi je vec uradio proveru gore, sad radi za ostale
			int flag = 0;
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				int argument = lookup_symbol(get_name(j), VAR|PAR); 
				// Treba za else if, ok je ovde da stoji VAR|PAR jer ne moze ispod indeksa funkcije da nadje parametar neke druge
				if(strcmp(get_name(j), $3) == 0){
					flag = 1;
					// Pronasao varijablu ili parametar te funkcije sa istim imenom
					argument_number++; // Sa 1 na n
					// Ovo proverava broj parametara funkcije koja je pozvana
					if (argument_number > get_atr1(fcall_idx)) // Mora da bude > !
						err("Wrong number of arguments sent over to function '%s'", get_name(fcall_idx));
					if (get_type(argument) != get_type(fcall_idx + argument_number)) 
						err("Forwarded argument '%s' of wrong type.\n", $3);
				}
			}
			if(flag == 0)
			// Ako ne nadje znaci da nije definisan
			err("Argument '%s' is not defined.\n", $3);
		}
	| literal
		// TODO:
	| arguments COMMA literal
		// TODO:
	;

if_statement
	: if_part %prec ONLY_IF
	| if_part ELSE statement
	;

if_part
	: IF LPAREN rel_exp RPAREN statement
	;

rel_exp
	: num_exp RELOP num_exp
		{
			if(get_type($1) != get_type($3))
				err("Invalid operands: relational operator.\n");
		}
	;

return_statement
	: RETURN num_exp SEMICOLON
		{
			// Javlja se return, postavljamo flag (cak iako tip povratne vrednosti nije dobar)
			return_flag = 1;
			if(get_type(fun_idx) != get_type($2))
				err("Incompatible types in return.\n");

			if(get_type(fun_idx) == VOID)
				err("Function of type VOID can't return an expression.\n");
		}
	| RETURN SEMICOLON
		{
			// Posto void funkcija ne zahteva return, ne moramo postavljati flag
			// Posto je ovo samo za void funkcije, za one koje nisu void moramo da kazemo da mora da vrati neki num_exp
			if(get_type(fun_idx) != VOID)
				warn("Non-void function has to return a value.\n");
		}
	;

increment_statement
	: ID INCREMENT SEMICOLON
		{
			if(lookup_symbol($1, VAR|PAR) == NO_INDEX)
        		err("'%s' is not declared.\n", $1);
		}
	;

loop
	: FOR LPAREN TYPE ID ASSIGN literal TO literal RPAREN statement // TODO: ne akcija posle statement, i ovde i dole
	// Mora statement, ne moze statement_list, baca konflikte
		{
			// Literal moze da bude i INT i UINT
			if($3 != get_type($6)
				|| $3 != get_type($8)) 
				err("Types of literals aren't the same in loop.\n");
			
			// get_name($n) je vrednost literala (njegovo ime), ali string, mora atoi()
			if(atoi(get_name($6)) >= atoi(get_name($8)))
				err("Start of loop isn't smaller than the end.\n");
			
			// TODO: Deo za izvrsavanje je za sledecu kontrolnu tacku
		} 
	| FOR LPAREN TYPE ID ASSIGN literal TO literal STEP literal RPAREN statement
		{
			if($3 != get_type($6)
				|| $3 != get_type($8)
				|| $3 != get_type($10)) 
				err("Types of literals aren't the same in loop.\n");

			if(atoi(get_name($6)) >= atoi(get_name($8)))
				err("Start of loop isn't smaller than the end.\n");
		}
	;

switch_statement
	: SWITCH LSQUAREBRACKET ID 
		{
			// Provera da li je ID po kojem se radi switch vec definisana promenljiva, ako jeste ok je
			// Takodje, pamtimo tip te promenljive za proveru u svakom case-u da li je literal dobrog tipa
			int switcher = 0;
			int flag = 0;
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				// Mozemo da preskocimo prvi jer je to ustvari funkcija
				if(strcmp(get_name(i), $3) == 0){
					// Nadjen, postavljamo flag za gresku i switcher za tip
					flag = 1;
					switcher = i;
				}
			}
			if(flag == 0) err("Variable or parameter '%s' in switch statement not defined.\n", $3);
			switch_type = get_type(switcher);
			// Vracamo za sledeci switch
			for(int i = 0; i < 100; i++)
				switch_array[i] = -2147483648;
			// TODO: Deo za izvrsavanje je za sledecu tacku
		}
		RSQUAREBRACKET LCURLYBRACKET case_list otherwise_optional RCURLYBRACKET
	;

case_list
	: CASETOKEN literal {
		// Posto bi $2 bio indeks u tabeli, moramo lookup_symbol da dobijemo vrednost
		// get_type($2) bi vratilo tip literala, jer je $2 indeks
		
		if(get_type($2) != switch_type)
			err("Type of literal not the same as type of switcher.\n");

		for(int i = 0; i < 100; i++){
			if (switch_array[i] == atoi(get_name($2)))
				err("Literal already in use in switch statement.\n");
		}

	} ARROW statement finish_optional
	| case_list CASETOKEN literal {
		if(get_type($3) != switch_type)
			err("Type of literal not the same as type of switcher.\n");

		for(int i = 0; i < 100; i++){
			if (switch_array[i] == atoi(get_name($3)))
				err("Literal already in use in switch statement.\n");
		}
	} ARROW statement finish_optional
	;

finish_optional
	: /* empty */
	| FINISH SEMICOLON
	;

otherwise_optional
	: /* empty */
	| OTHERWISE ARROW statement
	;

%%

int yyerror(char *s) {
	fprintf(stderr, "\nline %d: ERROR: %s", yylineno, s);
	error_count++;
	return 0;
}

void warning(char *s) {
	fprintf(stderr, "\nline %d: WARNING: %s", yylineno, s);
	warning_count++;
}

int main() {
	int synerr;
	init_symtab();

	synerr = yyparse();

	clear_symtab();
	
	if(warning_count)
	printf("\n%d warning(s).\n", warning_count);

	if(error_count)
	printf("\n%d error(s).\n", error_count);

	if(synerr)
	return -1; //syntax error
	else
	return error_count; //semantic errors
}