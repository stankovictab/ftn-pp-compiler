// Djordje Stankovic IN13/2018

// Iz tabele mi se ne brisu parametri funkcija, jer onda ne mogu da proverim argumente pri pozivu funkcije, ako ne koristim neku novu strukturu (TODO:)
// Pri proveri mogucnosti definisanja varijabli moze da se gleda lookup na VAR za celu tabelu, jer se samo varijable i brisu na kraju funkcija, nema ponavljanja gore, pa ce uvek da se misli na funkciju u kojoj smo trenutno, iako sam drugacije implementirao
// Ne prosirivati tabelu simbola, nego dodavati strukture ovde (nizove, matrice, itd.)

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
	int var_num = 0;
	int fun_idx = -1;
	int fcall_idx = -1;

	// Dodaci
	int vartype = 0;
	int return_flag = 0;
	int current_function = 0; // TODO: Zameni sa fun_idx jer izgleda da je to to vec definisano
	int parameter_number = 0;
	int argument_number = 0;
	unsigned switch_type = 0;
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

			print_symtab();
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
				// Ako ne postoji funkcija, dodaj je (bez atributa), i taj indeks stavi u current_function (indeks funkcije koja se obradjuje, koristi se u proverama za varijable kasnije, etc)
				fun_idx = insert_symbol($2, FUN, $1, NO_ATR, NO_ATR);
				current_function = fun_idx;
				}
			else 
				err("Redefinition of function '%s'.\n", $2);
		}
	LPAREN parameters_full 
		{
			// Kada analiziramo sve parametre update-ujemo broj parametra za simbol funkcije
			set_atr1(fun_idx, parameter_number);
		}
	RPAREN body
		{
			// Kada se funkcija zavrsi, moramo da izbrisemo sve njene varijable (ne diramo parametre, jer ih koristimo za pozive funkcija) - clear_symbols brise od ovog indeksa pa na dole, sto i ostavlja samo varijable, a ovaj indeks je pocetak varijabli
			clear_symbols(fun_idx + parameter_number + 1);
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
			// fun_idx je indeks ove funkcije
			// Trazimo da li postoji funkcija u tabeli
			fun_idx = lookup_symbol($2, FUN);
			if(fun_idx == NO_INDEX){
				// Ako ne postoji funkcija, dodaj je (bez atributa), i taj indeks stavi u current_function (indeks funkcije koja se obradjuje, koristi se u proverama za varijable kasnije, etc)
				fun_idx = insert_symbol($2, FUN, $1, NO_ATR, NO_ATR);
				current_function = fun_idx;
			}
			else 
				err("Redefinition of function '%s'.\n", $2);
		}
	LPAREN parameters_full 
		{
			// Kada analiziramo sve parametre update-ujemo broj parametra za simbol funkcije
			set_atr1(fun_idx, parameter_number);
		}
	RPAREN body
		{
			// Kada se funkcija zavrsi, moramo da izbrisemo sve njene varijable (ne diramo parametre, jer ih koristimo za pozive funkcija) - clear_symbols brise od ovog indeksa pa na dole, sto i ostavlja samo varijable, a ovaj indeks je pocetak varijabli
			clear_symbols(fun_idx + parameter_number + 1);
			var_num = 0;
			// Resetujemo return flag za nove funkcije
			return_flag = 0;
			// Resetujemo broj parametra za nove funkcije
			parameter_number = 0;
		}
	;

parameters_full
	: /* empty */
		{
			// Postavljamo broj parametara funkcije na 0 ako nema parametara
			set_atr1(fun_idx, 0);
		}
	| parameters
	/*  Moramo da razdvojimo parametre u 3 dela zbog rekurzije.
		Da smo pisali u 2 ovde na ovaj nacin :
		parameters_full : | parameter | paramers_full COMMA parameter
		onda bi proslo int f(, int a, int b){},
		jer bi empty gledao kao jedan parametar */
	;

parameters
	: parameter
	| parameters COMMA parameter
	;

parameter
	: TYPE ID // Ne moze biti VOIDTYPE
		{
			// Za svaki parametar moramo da povecamo broj parametara za tabelu simbola
			parameter_number++;
			// Proveravamo da li je trenutni parametar vec definisan tako sto prolazimo kroz tabelu simbola od indeksa funkcija (nju ne ubrajamo) na nize, i gledamo nazive ostalih simbola do kraja tabele, jer se varijable jos uvek nisu definisale, pa bi uporedjivali samo parametre te funkcije
			for(int j = current_function + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $2) == 0){
					err("Redifinition of parameter '%s'.\n", $2);
				}
			}
			// Ako ne dodje do greske znaci da ne postoji parametar sa takvim nazivom. Ovde smo mogli i current_function da stavimo.
			insert_symbol($2, PAR, $1, 1, fun_idx);
		}
	;

body
	: LCURLYBRACKET variable_list statement_list RCURLYBRACKET
	;

// Ova implementacija moze da ima vise linija definicija
// Da smo stavili variable_list : | variable_list variables SEMICOLON to bi bila samo jedna linija
variable_list
	: /* empty */
	| variable_list variables_def
	;

variables_def 
	: TYPE // Ne moze biti VOIDTYPE
		{
			// Mora u ovoj akciji da se izmeni vartype, da bi mogao da se koristi u variables_only
			vartype = $1;
		}
	variables_only SEMICOLON 
		{
			// Kada smo iskoristili vartype, moramo da ga resetujemo (cim se napravi variables_def)
			vartype = 0;
		}
	;

variables_only
	: ID
		{
			// Mora da proverava $1 sada, i da koristi vartype kao tip simbola
			// Pri deklarisanju varijable trebamo da proverimo da li vec u toj trenutnoj funkciji postoje varijable ili parametri sa tim imenom
			// To znaci da varijabla moze imati isto ime kao neka prethodna funkcija ili njeni parametri
			// Ne mozemo da gledamo po lookup_symbol(VAR|PAR) jer to gleda celu tabelu (od nazad pa do 13. registra (FUNREG)) - pravi problem zbog parametara, jer se oni ne brisu na kraju funkcije
			// Iteriramo od indeksa funkcije u kojoj je deklarisana varijabla (current_function) do kraja tabele simbola (get_last_element)
			// Poredimo imena sa svakim simbolom (varijable i parametri), i ako se poklopi javljamo gresku
			// Ako ne nadjemo nista da se poklapa, dodajemo u tabelu

			for(int i = current_function + 1; i <= get_last_element(); i++){
				// Mozemo da preskocimo prvi jer je to ustvari funkcija
				if(strcmp(get_name(i), $1) == 0){
					err("Variable or parameter by the name '%s' already exists.\n", $1);
				}
			}
			insert_symbol($1, VAR, vartype, ++var_num, NO_ATR);
		}
	| variables_only COMMA ID
		{
			// Ista provera i za ovu alternativu
			for(int i = current_function + 1; i <= get_last_element(); i++){
				// Mozemo da preskocimo prvi jer je to ustvari funkcija
				if(strcmp(get_name(i), $3) == 0){
					err("Variable or parameter by the name '%s' already exists.\n", $3);
				}
			}
			insert_symbol($3, VAR, vartype, ++var_num, NO_ATR);
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
			// current_function nije ono sto nam treba, treba da nadjemo atr1 (broj parametara) funkcije koje pozivamo
			// To radimo tako sto idemo od trenutne funkcije u tabeli simbola na gore i gledamo atr1 od simbola funkcije koju pozivamo
			// Ili samo uzmemo fcall_idx koji bas za to sluzi
			for(int j = current_function; j > FUN_REG; j--){ // FUN_REG je makro za 13
				//int argument = lookup_symbol(get_name(j), FUN);
				if(fcall_idx == j){
					if(get_atr1(fcall_idx) > 0)
						err("Function doesn't require any arguments.\n");
				}
			}
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
			for(int j = current_function + 1; j <= get_last_element(); j++){
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
			for(int j = current_function + 1; j <= get_last_element(); j++){
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
	| arguments COMMA literal
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
	: FOR LPAREN TYPE ID ASSIGN literal TO literal RPAREN statement 
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
			for(int i = current_function + 1; i <= get_last_element(); i++){
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