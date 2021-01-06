// Djordje Stankovic IN13/2018

// Iz tabele mi se ne brisu parametri funkcija, jer iz tabele simbola proveravam argumente pri pozivu funkcije

/*
Default atributi u Tabeli Simbola :
Atribut 1 :
- Za lokalnu promenljivu (varijablu) - redni broj promenljive po definisanju u funkciji,
- Za parametar - redni broj parametra (mora da bude zbog GK-a),
- Za funkciju – broj parametara,
- Za ostale simbole - nije definisano.
Atribut 2 :
- Za funkcije - tip (jedinog) parametra,
- Za ostale simbole - nije definisano.

Moje izmene :
Za parametar je atr2 block_level, i uvek je 0 (bitan je zbog provere nivoa)
Za funkcije atr2 vise nije nista, jer tipove parametara pamtimo u tabeli simbola.
Za varijable je atr2 block_level.
Za GVAR je isto atr2 block_level, i uvek je -1.

symtab.h nije menjan.
symtab.c je menjan, mora da se stavi "GVAR" u symbol_kinds u print_symtab() jer stavlja (null) umesto GVAR u tabeli.
defs.h je menjan, dodat je samo VOID kao tip.
To je to, 4 fajla sam menjao.
Nacin na koji "menjamo" atribute u tabeli simbola je samo menjanjem unosa pri pozivanju insert_symbol ili set_atr.
*/

// Umesto idx = j je stajalo idx = lookup_symbol(get_name(j), VAR|PAR); (izbrisi posle ako radi sve)

// TODO: Izvrsavanje na pdf-u je ustvari GK

// TODO: //RETURN: za GK za sve moje testove

// == block_level se stavlja kada se radi definisanje, a nista se ne stavlja (ili <=) kada se radi provera da li postoji promenljiva (varijabla ili parametar)

// TODO: Vidi cemu sluzi free_if_reg() svuda

// TODO: Za for onaj hardcode JGES treba da moze i JGEU

// TODO: Niz koji cuva sve elemente koji treba da se inkrementuju pa oni tek posle u GK
// Za npr a = a++ + b++; NE treba da se broji koliko puta je bilo inkrementiranja pa da se tolko uveca a
// Mora da se vidi koji su se ID-evi inkrementovali, da se oni posle ovoga inkrementuju
// Treba da napravim testove za inkrement u svim slucajevima ako vec ne postoji

// Za a==1, a = a++ + a++ ce biti ovako:
// prvo a++ ce biti 1, jer se ++ radi tek posle
// Kada dodje do + izmedju, uradio se taj ++, i sada su nove vrednosti za a 2, ali je leva strana jos uvek 1
// Onda ce biti 1+2 sve to, a ovo drugo a++ nema uticaja jer ce ga override-ovati celokupna dodela
// (a++ ce povecati a na kraju ++, a ne tek na ;)
// Tako da je rezultat 3, a ne 4
// dakle ++ ce menjati sledece a, a ne to na kojem je zakaceno, osim poslednjeg ++ koji ne menja nista
// Za a==1, a = ++a + ++a ce biti 6, jer prvo inkrementuje a pa opet ink a, pa sabira a i a

// ASM parsing error znaci da HipSim-u ne saljes .asm fajl
// Ako nema //RETURN:, to ce biti PASSED
// Samo ok testovi treba da imaju //RETURN:

// TODO: Svaki test u C da vidis result pa uporedi sa -r rezultatom

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "defs.h"
	#include "symtab.h"
	#include <string.h> // Za strcmp
	#include "codegen.h" // KT2

	#define ARRAY_LIMIT 100
	#define INT_MIN -2147483648

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
	int block_level = 0; // Brojac nivoa za ugnjezdene blokove koda (atr2 kod VAR-ova)
	int stack_of_loop_starts_indexes [ARRAY_LIMIT] = {0}; // Stek sa indeksima varijabli koje su inicijalizovane u definicijama iteracija, potreban za brisanje simbola iz tabele na kraju loop-a
	int stack_indexer = -1;
	int loop_transferring_type = 0; // (NO_TYPE)
	int loop_transferring_id = 0;
	int loop_transferring_first_literal = 0;
	int loop_transferring_second_literal = 0;
	unsigned switch_type = 0; // unsigned je jer get_type vraca unsigned
	int switch_array[ARRAY_LIMIT]; // Niz literala trenutnog switch-a za proveru koriscenih (ne moze ovde sve da se inicijalizuje na INT_MIN, nego mora u switch-u)
	int switch_array_indexer = 0;

	// KT2
	int out_lin = 0;
	int lab_num = -1;
	FILE *output; // Vidi main() skroz dole, tu se inicijalizuje

	int argument_pusher_array[ARRAY_LIMIT]; // Niz indeksa registra koji imaju vrednosti num_exp-ova koji se prosledjuju u pozivu funkcije, da bi mogao da argumente push-ujem na stackframe u obrnutom redosledu
	int increment_todo_array[ARRAY_LIMIT] = {0}; // Niz indeksa ID-eva koji trebaju da se inkrementuju
	int increment_array_indexer = 0;
	int loop_counter = 0; // Za labele for-a TODO: Zasto 1
	int transferring_second_literal_array[ARRAY_LIMIT] = {0};
	int transferring_id_array[ARRAY_LIMIT] = {0};
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

// Ovde arguments, argument_list i if_part
%type <i> num_exp exp literal function_call arguments rel_exp argument_list if_part increment_optional loop_first_part

%nonassoc ONLY_IF
%nonassoc ELSE

%%

program
	: global_list function_list
		{  
			// Javlja gresku ako main() uopste ne postoji u tabeli simbola
			if(lookup_symbol("main", FUN) == NO_INDEX)
				err("Undefined reference to 'main'.\n");
		 }
	;

global_list
	: /*empty*/
	| global_list global_var
	;

global_var
	: TYPE ID SEMICOLON
	{
		// Dodatna provera, ne mogu globalne promenljive i funkcije da imaju isto ime (ne moze int main; iznad int main(){}), ali moze da se trazi po celoj tabeli
		int idx = lookup_symbol($2, GVAR|FUN); 
		if (idx != NO_INDEX) 
		{
				err("Global variable or function by the name '%s' already exists.", $2);
		} else {
			insert_symbol($2, GVAR, $1, NO_ATR, -1); // block_level za globalne promenljive je -1
			// Generisanje koda za GVAR
			code("\n%s:\n\t\tWORD\t1", $2);
		}
	}
	;

function_list
	: function
	| function_list function
	;

function
	: TYPE ID
		{
			// Trazimo da li postoji funkcija ili globalna promenljiva u tabeli sa istim imenom
			fun_idx = lookup_symbol($2, FUN|GVAR);
			if(fun_idx == NO_INDEX){
				// Ako ne postoji, dodaj je, uz inicijalizovanje broja parametara na 0 (tek treba da se puni) (atr2 vise nije nista za funkcije)
				fun_idx = insert_symbol($2, FUN, $1, 0, NO_ATR);
				}
			else 
				err("Redefinition of function '%s'.\n", $2);

			// Postavljanje labele za funkciju, frame pointer-a i stack pointer-a
			code("\n%s:", $2);
        	code("\n\t\tPUSH\t%%14");
        	code("\n\t\tMOV \t%%15,%%14");
		}
	LPAREN parameters_full 
		{
			// Kada analiziramo sve parametre, update-ujemo broj parametra za simbol funkcije (mada ovo i nema neku svrhu da se postavlja)
			set_atr1(fun_idx, parameter_number);
		}
	RPAREN body
		{
			// Kada se funkcija zavrsi moramo da izbrisemo sve njene lokalne varijable (ne diramo parametre, jer ih koristimo za pozive funkcija) 
			// clear_symbols brise od ovog indeksa pa na dole, pa ce nam ostati samo parametri
			int var_start_index = fun_idx + parameter_number + 1;
			clear_symbols(var_start_index);
			// Resetujemo var_num za sledece funkcije
			var_num = 0;
			// Non-void funkcije moraju imati povratnu vrednost, pa koristimo flag da proverimo da li smo ga iskoristili
			if(return_flag == 0)
				warn("Function '%s' needs to have the 'return' keyword.\n", $2);
			// Resetujemo return flag za nove funkcije
			return_flag = 0;
			// Resetujemo broj parametra za nove funkcije
			parameter_number = 0;

			// Izlaz iz funkcije - exit labela, "brisanje" stackframe-a i ret
			code("\n@%s_exit:", $2);
			code("\n\t\tMOV \t%%14,%%15"); // Podizemo %esp
			code("\n\t\tPOP \t%%14"); // Resetujemo %ebp
			code("\n\t\tRET"); // Povratnu adresu stavljamo u PC
		}
	| VOIDTYPE ID
		{
			fun_idx = lookup_symbol($2, FUN);
			if(fun_idx == NO_INDEX){
				fun_idx = insert_symbol($2, FUN, $1, 0, NO_ATR);
			}
			else 
				err("Redefinition of function '%s'.\n", $2);

			code("\n%s:", $2);
        	code("\n\t\tPUSH\t%%14");
        	code("\n\t\tMOV \t%%15,%%14");
		}
	LPAREN parameters_full 
		{
			set_atr1(fun_idx, parameter_number);
		}
	RPAREN body
		{
			int var_start_index = fun_idx + parameter_number + 1;
			clear_symbols(var_start_index);
			var_num = 0;
			// Jedina razlika u odnosu na gornju alternativu je sto ovde ne proveravamo return_flag kao gore jer void funkcije nemaju povratnu vrednost
			return_flag = 0;
			parameter_number = 0;

			code("\n@%s_exit:", $2);
			code("\n\t\tMOV \t%%14,%%15");
			code("\n\t\tPOP \t%%14");
			code("\n\t\tRET");
		}
	;

parameters_full
	: /* empty */
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
			// Ne radimo lookup_symbol() da ne bi uzeli parametre neke trece funkcije u razmatranje
			// Gledamo od indeksa trenutne funkcije do kraja tabele, jer varijabli nema
			// Ne ubrajamo simbol funkcije za slucaj int foo(unsigned foo){...}
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $2) == 0){ // Provera za block_level nema smisla ovde
					err("Redifinition of parameter '%s'.\n", $2);
				}
			}
			// Za svaki parametar koji prodje moramo da povecamo broj parametara za update-ovanje atr1 funkcije
			parameter_number++;
			// Pri ubacivanju parametra, postavlja mu se indeks funkcije za koji je, kao i nivo, koji je uvek 0 (sluzi za kasniju proveru u operacijama)
			insert_symbol($2, PAR, $1, parameter_number, 0);
		}
	;

body
	: LCURLYBRACKET variable_list 
		{
			// Ako je bilo promenljivih definisano u funkciji, napravi mesta za njih na stackframe-u (pomeri %esp na dole) i napravi labelu za statement-e
			if(var_num)
				code("\n\t\tSUBS\t%%15,$%d,%%15", 4 * var_num);
				// Pomeramo %esp na dole da napravimo mesta (jedna promenljiva -> 4 bajta)
				// Lokalne promenljive ce ostati na stackframe-u dok se ne overwrite-uju, pa zato nema ADDS za ovaj SUBS, nema potrebe, jer ce odmah u exit labeli funkcije da se radi MOV %14, %15, sto pomera %esp na gore
			code("\n@%s_body:", get_name(fun_idx)); 
			// Od ove labele krece body koji ce se generisati iz ostalih pojmova koji prave statement_list-u
		}
	statement_list RCURLYBRACKET
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
			// Kada smo iskoristili vartype, moramo da ga resetujemo (cim se napravi variables_def_line) (ovo je mozda nepotrebno)
			vartype = 0;
		}
	;

variables_only
	: ID
		{
			// Pri deklarisanju varijable trebamo da proverimo da li vec u toj trenutnoj funkciji postoje varijable ili parametri sa tim imenom
			// To znaci da varijabla moze imati isto ime kao neka prethodna funkcija ili njeni parametri
			// Ne mozemo da gledamo po lookup_symbol(VAR|PAR) jer to gleda celu tabelu (od nazad pa do 13. registra (FUNREG)) 
			// To pravi problem zbog parametara, jer se oni ovde ne brisu iz tabele na kraju funkcije
			// Idemo od indeksa funkcije u kojoj je deklarisana varijabla (fun_idx) do kraja tabele
			// Ne gledamo sam simbol funkcije jer lokalna varijabla moze da ima isto ime kao njena funkcija
			// Poredimo imena sa svakim simbolom (varijable i parametri), i ako se poklopi javljamo gresku, ako ne nadje isto ime dodajemo
			// Za tip varijable koristimo vartype koji je postavljen u variables_def_line
			// Takodje dodajemo proveru za nivo bloka, da na trenutnom nivou ne moze da se definise promenljiva koja je tu vec definisana (bitno je da je definisana, a ne koja tu samo postoji, jer ako smo pre imali int a;, i u novom bloku opet int a;, to moze jer ce se vrednost a overwrite-ovati samo u tom scope-u, vidi compound_statement)
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), $1) == 0 && get_atr2(i) == block_level){ // Mora == kada definisemo varijablu
					err("Variable or parameter by the name '%s' already exists on this level.\n", $1);
				}
			}
			var_num++;
			insert_symbol($1, VAR, vartype, var_num, block_level);
		}
	| variables_only COMMA ID
		{
			// Ista provera i za ovu alternativu
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), $3) == 0 && get_atr2(i) == block_level){
					err("Variable or parameter by the name '%s' already exists on this level.\n", $3);
				}
			}
			var_num++;
			insert_symbol($3, VAR, vartype, var_num, block_level);
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
	| increment_statement
	| loop
	| switch_statement
	;

// Svaki compound_statement se razlikuje po svom nivou, koji je atr2 kod njegovih lokalnih varijabli
// GVAR ovo nece imati, samo VAR, a nivo 0 je nivo main-a, odnosno nulti blok
// Pri definisanju varijabli sada moramo da proveravamo nivo na kojem se definise
// Sve novodefinisane varijable u bloku se brisu na kraju bloka iz tabele simbola
// Ako je na prvom nivou x definisano, moze i na drugom nivou opet da se definise, ali ce se vrednost overwrite-ovati (kao sa GVAR-ovima)
// Ako se ne redefinise, nego se samo vrednost promeni, vrednost ce se promeniti i u prethodnom bloku (tako je u C-u)
compound_statement
	: LCURLYBRACKET
		{
			// Na pocetku novog bloka se povecava brojac (prvi novi blok ce biti nivoa 1)
			block_level++;
		}
	variable_list statement_list RCURLYBRACKET // Ovo je zapravo body, razdvojen zbog semantike (mozda dodje do konflikta? ali nece zbog ove akcije gore?)
		{
			// Brisemo sve novodefinisane varijable (da bi vratili vrednost starima sa istim imenom)
			// Nadjemo prvi simbol sa trenutnim block_level-om i brisemo sve ispod njega (ukljucujuci i literale)
			for(int j = fun_idx + 1; j <= get_last_element(); j++)
				if(get_atr2(j) == block_level)
					clear_symbols(j);
			// Vracamo se u nivo pre
			block_level--;
		}
	;

assignment_statement
	: ID ASSIGN num_exp SEMICOLON
		{
		int idx = NO_INDEX;
		// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
		// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
		for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $1) == 0) // U ovoj proveri moze, a i ne mora, da se stavi && get_atr2(j) <= block_level, zato sto svi simboli u tabeli sigurno nece imati block_level veci od trenutnog, zato sto se svaki prethodni novi blok izbrisao, vidi compound_statement (ako smo u nivou 0, nece postojati nista iz nivoa 1)
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
			}
		if(idx == NO_INDEX)
			idx = lookup_symbol($1, GVAR);
		if(idx == NO_INDEX)
			err("Local or global variable or parameter by the name '%s' in assignment doesn't exist.\n", $1);
		else if(get_type(idx) != get_type($3))
			err("Incompatible types in assignment.\n");
		
		// Generisanje koda za dodelu - vrednost num_exp-a ide u ID (treba da ostane ovde)
		gen_mov($3, idx);

		// Inkrementujemo te ID-eve koji su sami inkrementovani
		// TODO: Pretpostavljamo da je svaki ID maksimalno jednom inkrementovan u assign statement-u, jer su oni tako na pdf-u prikazali asembler, zapravo po gcc-u treba da se uveca za 1 ako se ID inkrementovao dvaput u izrazu, ili da se uveza za 3 ako se pojavio triput, etc
		// Takodje, a = a++; nece da inkrementuje po gcc-u ali ovde hoce
		for(int i = 0; i < ARRAY_LIMIT; i++){
			if(increment_todo_array[i] != 0){
				if(get_type(idx) == INT){
					code("\n\t\tADDS\t");
					
				}else{
					code("\n\t\tADDU\t");
				}
				gen_sym_name(increment_todo_array[i]);
				code(",$1,");
				gen_sym_name(increment_todo_array[i]);
			}
		}

		// Reset
		increment_array_indexer = 0;
		for(int i = 0; i < ARRAY_LIMIT; i++)
			increment_todo_array[i] = 0;
		}
	;

num_exp
	: exp
	| num_exp AROP exp
		{
			// Semanticka vrednost num_exp-a je indeks registra u kojem se nalazi njegova vrednost
			// Tip num_exp-a je tip vrednosti koju taj izraz daje, a taj tip je nasledjen od exp-a, i stavljen je kao tip tog registra koji ima njegovu vrednost
			// Zna se i tip poziva funkcije (povratne vrednosti) iz toga sto je semanticka vrednost function_call-a indeks funkcije, 
			// pa ce tu semanticku vrednost imati i exp, pa ce get_type($3) uzeti tacan tip iz simbola kind-a FUN
			if(get_type($1) != get_type($3))
				err("Invalid operands: arithmetic operation (incompatible types).\n");
			int type = get_type($1);
			// num_exp ce biti npr ADDS %1, %3, %4
			// biramo aritmeticku operaciju na osnovu parsiranog AROP-a i tipa num_exp-a - $2 je vrsta operacije (ADD ili SUB), a ovaj proizvod je ili 0 ili 4 (AROP_NUMBER je makro za 4) i bira signed ili unsigned verziju operacije (ima 4 zbog MUL i DIV)
			code("\n\t\t%s\t", ar_instructions[$2 + (type - 1) * AROP_NUMBER]);
			// Operandi
			gen_sym_name($1); // Ovo je valjda uvek registar
			code(",");
			gen_sym_name($3); // Ovo ne mora da bude registar
			code(",");
			// Oslobadjamo odmah zauzete registre u obrnutom redosledu
			free_if_reg($3);
			free_if_reg($1);
			$$ = take_reg(); // Semanticka vrednost je indeks registra sa rezultatom
			gen_sym_name($$); // Generise asm kod za taj registar kao rezultat operacije
			set_type($$, type); // Postavljamo tip registra koji sadrzi vrednost num_exp-a na tip samog num_exp-a
		}
	;

// Semanticka vrednost exp-a je indeks toga u tabeli simbola (ili indeks literala ili varijable, ili registra u kojem je povratna vrednost poziva funkcije, ili sta god je sem vrednost num_exp-a u zagradi (vidi pojam)
// Takodje, tip exp-a je tip toga sta je redukovao
exp
	: literal
	| ID increment_optional
		{
			int idx = NO_INDEX;
			// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
			// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $1) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
			}
			if(idx == NO_INDEX)
				idx = lookup_symbol($1, GVAR);
			if(idx == NO_INDEX)
				err("'%s' undeclared.\n", $1);
			$$ = idx; // Semanticka vrednost exp-a sa ID-em je indeks ID-a u tabeli simbola

			// Provera da li je bilo inkrementa nad tim ID-em
			if($2 == 1){
				increment_todo_array[increment_array_indexer] = idx;
				increment_array_indexer++;
			}
		}
	| function_call
		{
			// Kada pozivamo funkciju zelimo da njenu povratnu vrednost prebacimo u registar opste namene
			$$ = take_reg(); // Zauzima se registar opste namene
			gen_mov(FUN_REG, $$); // Prebaca se iz %13 u taj registar
		}
	| LPAREN num_exp RPAREN
		{ $$ = $2; /* exp nasledjuje semanticku vrednost num_exp-a u zagradi */ }
	;

literal
	: INT_NUMBER
		{ $$ = insert_literal($1, INT); }

	| UINT_NUMBER
		{ $$ = insert_literal($1, UINT); }
	;

increment_optional
	: /* empty */
		{
			$$ = 0; // Nije bilo inkrementa
		}
	| INCREMENT
		{
			$$ = 1; // Bilo je inkrementa
		}
	;

function_call
	: ID 
		{
			// Ovo je indeks funkcije koju pozivamo u tabeli simbola, koristi se kod argumenata
			fcall_idx = lookup_symbol($1, FUN); 
			if(fcall_idx == NO_INDEX)
				err("'%s' is not a function.\n", $1);

			// Reset niza na pocetku poziva
			for(int i = 0; i < ARRAY_LIMIT; i++)
				argument_pusher_array[i] = INT_MIN;
		}
	LPAREN argument_list RPAREN
		{
			// Ovde je pre pisalo samo $$ = lookup_symbol($1, FUN);
			// U micku su koristili semanticku vrednost argument_list-e za broj argumenata, ja imam globalnu varijablu
			// Takodje su ovde radili proveru broja argumenata, ja to radim u argument_list

			// Generisanje koda za argumente - push-ujemo ih na stackframe u obrnutom redosledu, mora pre CALL-a
			for(int i = argument_number - 1; i >= 0; i--){
				free_if_reg(argument_pusher_array[i]);
				code("\n\t\t\tPUSH\t");
				gen_sym_name(argument_pusher_array[i]); // Generisace asm kod za registar u kojem je vrednost num_exp-a
			}

			// Pravi se poziv uz ime funkcije, koje ce biti labela
			code("\n\t\t\tCALL\t%s", get_name(fcall_idx));
			// Nakon poziva, kada funkcija zavrsi sa radom, moramo da izbrisemo mesta za argumente koji su joj prosledjeni (ovaj if nije ni potreban)
			if(argument_number > 0)
				code("\n\t\t\tADDS\t%%15,$%d,%%15", argument_number * 4);
			set_type(FUN_REG, get_type(fcall_idx)); // Postavlja tip za %13
			$$ = FUN_REG; // Semanticka vrednost poziva je uvek 13

			// Resetujemo broj argumenata za sledeci poziv
			argument_number = 0;
		}
	;

// Mora da se doda kao poseban pojam da ne bi proslo nesto kao
// b = f(,a,c);
argument_list
	: /* empty */
		{
			// Ako nismo prosledili argumente, moramo da proverimo da li funkcija zapravo zahteva parametre
			if(get_atr1(fcall_idx) > 0)
				err("Function '%s' requires arguments!\n", get_name(fcall_idx));
			// argument_number ostaje 0
		}
	| arguments	
		{
			// Moramo ovde da proverimo broj argumenata, jer argumenti mogu da budu svakakvi, pa nema smisla to proveravati u akcijama dole
			// U tim akcijama dole se znaci samo postavlja argument_number, ali se ovde proverava
			if(get_atr1(fcall_idx) > argument_number)
				err("Too few arguments passed to function '%s'.\n", get_name(fcall_idx));
			else if(get_atr1(fcall_idx) < argument_number)
				err("Too many arguments passed to function '%s'.\n", get_name(fcall_idx));
		}
	;

/*
Samo num_exp ako se stavi, pokrivace i ID i literale (a i numericke izraze i pozive funkcija i inkremente, sve mora da radi)
Dakle u ovoj proveri trebamo da proveravamo da li se tip poklapa sa trazenim tipom parametra,
i trebamo da postavimo argument_number za ovu proveru gore

Razlog zasto ne moramo da proveravamo da li VAR|PAR|GVAR koje smo prosledili uopste postoje je zato sto num_exp to automatski radi
(Ne bismo mogli da napravimo exp uopste a da varijabla nije bila definisana, tako da mora da postoji ako se napravio num_exp)
Da sam ovo znao ne bi radio sve one provere i razdvajao na ID-eve i literale

TODO: Ne moze poziv u pozivu zbog toga sto je argument_number globalna promenljiva, pa se izmesa kada se radi poziv u pozivu,
za to bi morao da pravim niz dubina poziva funkcija, gde svaka dubina ima svoj argument number
*/
arguments
	: num_exp
		{
			// Cim nadje jedan parametar radice ovu proveru, a ako nadje vise nastavice u sledecoj alternativi
			argument_number = 1;
			// get_type() za num_exp radi, a radice i u GK zbog indeksa registra sa tipom
			if(get_type(fcall_idx + argument_number) != get_type($1)) 
        		err("Forwarded argument '%s' of wrong type.\n", get_name($1));
			// Punimo niz indeksa registra num_exp-ova koji su za PUSH na stackframe u obrnutom redosledu (mora -1 jer pocinje od 1)
			argument_pusher_array[argument_number - 1] = $1;
		}
	| arguments COMMA num_exp
		{
			// Za prvi argument u listi je vec uradio proveru gore, sad radi za ostale, redom
			argument_number++; // Za svaki argument povecavamo
			if(get_type(fcall_idx + argument_number) != get_type($3)){
        		err("Forwarded argument '%s' of wrong type.\n", get_name($3));
			}
			argument_pusher_array[argument_number - 1] = $3;
		}
	;

// Postavljen je prioritet na ELSE alternativu
if_statement
	: if_part %prec ONLY_IF
		{
			// Na kraju parsiranja celog if_statement-a mora da se napravi labela za izlazak iz if-a, zbog skoka iz druge labele na tu labelu - moramo da stavimo broj labele, a to cemo dobiti iz semanticke vrednosti if_part-a, sto je ustvari broj labele za taj nivo if-a (u ugnjezdenim if-ovima)
			code("\n@exit%d:", $1);
		}
	| if_part ELSE statement // Ovaj statement ce generisati asemblerski kod za ELSE alternativu if-a, odnosno za telo false grane if-a, i to ce pisati u vec napravljenoj labeli za false granu (vidi dole)
		{
			code("\n@exit%d:", $1);
		}
	;

if_part
	: IF LPAREN 
		{
			// Prva labela je za uslov u zagradama, pravimo labelu uz lab_num
			$<i>$ = ++lab_num; // Bio je na -1 da bi "stablo ugnjezdenih if-ova" pocelo od nulte labele
        	code("\n@if%d:", lab_num);
		}
	rel_exp // rel_exp generise CMP instrukciju za prvu labelu (vidi dole)
		{
			// $<i>3 je trenutni lab_num, za taj nivo if-a, odnosno semanticka vrednost prve akcije
			// Koristimo ga ovako a ne preko lab_num jer ce se lab_num menjati kako pravimo if-ove u if-u
			// Znaci ovako ce sigurno ta semanticka vrednost da ostane na istom nivou ($<i>$ je lokalno samo za trenutni pojam, a lab_num je globalna vrednost)
			// lab_num se nigde ne resetuje, tako da ako imamo jednom neke if u if-u u if-u itd, ako izadjemo iz svega toga i ponovo imamo neki if, on nece biti prvi, nego npr sesti (kao sto i treba, ako se resetuje lab_num, onda ce se simulator vracati na pogresan if gore cak, a treba da ide dole)
			// opp_jumps je opposite jumps, i mi koristimo tu enumeraciju jer sa CMP-om hocemo da idemo na false granu if-a, znaci gledamo suprotan uslov
			code("\n\t\t%s\t@false%d", opp_jumps[$4], $<i>3); // Uslovni skok na false labelu
			// Zna se koji ce se tip skoka koristiti na osnovu rel_exp-a i njegove semanticke vrednosti, a semanticka vrednost rel_exp-a je indeks odgovarajuceg uskovnog skoka u enumeraciji, vidi dole
			code("\n@true%d:", $<i>3);
		}
	RPAREN statement // Ovaj statement ce generisati svoj asemblerski kod za telo true grane if-a, cak iako je to ponovo neki if_statement
		{
			code("\n\t\tJMP \t@exit%d", $<i>3); // Bezuslovni skok na kraj na kraju true grane if-a
			code("\n@false%d:", $<i>3); // Ova labela ce za ONLY_IF alternativu postojati, ali ce biti prazna, pa je napravljena za drugu alternativu, da bi ona mogla samo tu da nastavi sa onim njenim statement-om
			$$ = $<i>3; // Da bi napravili exit labelu treba nam broj labele za trenutni nivo if-a, pa koristimo semanticku vrednost if_part-a za to (a to se koristi u alternativama if_statement-a)
		}
	;

rel_exp
	: num_exp RELOP num_exp
		{
			if(get_type($1) != get_type($3))
				err("Invalid operands in relational operator.\n");
       		// $2 daje jednu od onih 6 standardnih relop-a
			// Moramo da gledamo tip operanda da bi znali koji tacno skok da uradimo, da li S ili U
			// Pa ce ova zagrada desno biti ili 0 (za S) ili 6 (za U) (jer get_type vraca ili 1 ili 2)
			// Pa ce semanticka vrednost rel_exp-a biti indeks odgovarajuceg uslovnog skoka u enumeraciji
			$$ = $2 + ((get_type($1) - 1) * RELOP_NUMBER);
        	gen_cmp($1, $3); // Na primer CMPS %3, %4 (gen_cmp gleda da li su int ili uint pa ce biti ili CMPS ili CMPU)
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
			gen_mov($2, FUN_REG); // Prebaca u %13 za povratnu vrednost
			code("\n\t\tJMP \t@%s_exit", get_name(fun_idx)); // JMP na exit labelu za funkciju za "brisanje" stackframe-a
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
			int idx = NO_INDEX;
			// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
			// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $1) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
			}
			if(idx == NO_INDEX)
				idx = lookup_symbol($1, GVAR);
			if(idx == NO_INDEX)
				err("'%s' undeclared.\n", $1);
			// increment_statement-u se ne postavlja semanticka vrednost (za sad)

			if(get_type(idx) == INT){
				code("\n\t\tADDS\t");
			}else{
				code("\n\t\tADDU\t");
			}
			gen_sym_name(idx);
			code(",$1,");
			gen_sym_name(idx);
		}
	;

// loop sam odvojio u 2 dela da bih prvo ID ubacio u tabelu simbola, pa tek onda literale, zbog kasnijeg oslobadjanja tabele simbola,
// jer je mnogo lakse kada znam tacno od kog indeksa pocinje loop, da bih kasnije sa stekom indeksa tih ID-eva lakse oslobodio
loop
	: loop_first_part loop_second_part 
		{
			// Kraj loop-a, bilo da je ugnjezden ili ne

			// Semanticka vrednost prvog dela je labela
			gen_cmp(loop_transferring_id, loop_transferring_second_literal); // Poredi trenutan i i kraj
			if(get_type(loop_transferring_id) == INT){
				code("\n\t\tJGES \t@loop_exit%d", $1); // TODO: Da li ovde moze lab_num? Mozda ovo sve mora u ceo loop?
				code("\n\t\tADDS \t"); 
				gen_sym_name(loop_transferring_id);
				code(",$1,"); // TODO: Ovde u drugom slucaju umesto $1 biti step
				gen_sym_name(loop_transferring_id);
			}
			else if(get_type(loop_transferring_id) == UINT){
				code("\n\t\tJGEU \t@loop_exit%d", $1);
				code("\n\t\tADDU \t"); 
				gen_sym_name(loop_transferring_id);
				code(",$1,"); // TODO: Ovde u drugom slucaju umesto $1 biti step
				gen_sym_name(loop_transferring_id);
			}
			code("\n\t\tJMP \t@loop_start%d", $1); // Skocice ako ne prodje CMP
			code("\n@loop_exit%d:", $1);

			// Reset
			loop_transferring_type = 0; 
			//loop_transferring_id = 0;
			loop_transferring_first_literal = 0; // Mozda nepotrebno
			
			loop_counter--;

			loop_transferring_id = transferring_id_array[loop_counter]; // Bez obzira na dubinu mora se vratiti 1 unazad (resetovace se kada je samo jedan for, jer je array[0] = 0)
			
			// Ovaj if moze samo ovo u else da se stavi i bice isto
			if(transferring_second_literal_array[loop_counter] == 0){ // array[0] = 0 uvek
				loop_transferring_second_literal = 0; // Reset
			}else{
				loop_transferring_second_literal = transferring_second_literal_array[loop_counter];
			}
			// Brisanje simbola za loop iz tabele preko steka
			clear_symbols(stack_of_loop_starts_indexes[stack_indexer]);
			stack_indexer--;
		}
	;

loop_first_part
	: FOR LPAREN TYPE ID ASSIGN literal // Prvi literal mora ovde zbog gen_mov-a
		{
			// TYPE ID mora da napravi lokalnu promenljivu, i to samo u scope-u iteracije, i ne moze da se koristi ako vec postoji na tom scope-u (nivou) definisana (definisanje -> == block_level, znaci slicno kao variables_only)
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), $4) == 0 && get_atr2(i) == block_level){ // Mora == (GVAR ne ubrajamo u proveru za gresku jer moze da ga redefinise)
					err("Variable or parameter by the name '%s' already exists on this level.\n", $4);
				}
			}
			var_num++;
			stack_indexer++; // Za prvi loop sa -1 na 0
			// TODO: Treba neki loop_counter za labele u asm koji se nece resetovati, znaci isto kao kod if-a, mozda da se stavi u novoj akciji izmedju LPAREN i TYPE
			int idx = insert_symbol($4, VAR, $3, var_num, stack_indexer);
			stack_of_loop_starts_indexes[stack_indexer] = idx; // Punimo stek, za block_level se stavlja stack_indexer, jer je svaki for novi blok 

			loop_transferring_type = $3;
			loop_transferring_id = idx;
			loop_transferring_first_literal = $6;
			loop_counter++; // Cim se napravi novi loop
			transferring_id_array[loop_counter] = idx;

			gen_mov(loop_transferring_first_literal, loop_transferring_id); // int i = 1
			// Pocinju naredbe u loop-u, pa moramo da pravimo labelu za skok
			lab_num++;
			$$ = lab_num;
			code("\n@loop_start%d:", lab_num);
		}
	;

loop_second_part
	: TO literal RPAREN  // Mora ovde akcija, ako je pre javlja se konflikt sa donjom alternativom
		{
			// Razlog zasto razdavajamo ovde je da bi se iz tabele simbola (u sledecoj akciji) brisali i literali iz inicijalizacije iteracije
			if(loop_transferring_type != get_type(loop_transferring_first_literal)
				|| loop_transferring_type != get_type($2)) 
				err("Types of literals in the iteration definition aren't the same.\n");
			
			int lit1 = atoi(get_name(loop_transferring_first_literal));
			int lit2 = atoi(get_name($2));

			// get_name($n) je vrednost literala (njegovo ime), ali string, mora atoi()
			if(lit1 >= lit2)
				err("Start of the loop isn't smaller than the end.\n");

			loop_transferring_second_literal = $2;
			transferring_second_literal_array[loop_counter] = loop_transferring_second_literal;

			// TODO: Mozda provera treba ovde, odmah na pocetku for-a da slucajno ne izvrsi naredbe iako je i vece od kraja
			// Ali onda ne bi prosao ovu proveru gore HA!
		} 
	statement
	| TO literal STEP literal RPAREN 
		{
			if(loop_transferring_type != get_type(loop_transferring_first_literal)
				|| loop_transferring_type != get_type($2)
				|| loop_transferring_type != get_type($4)) 
				err("Types of literals in the iteration definition aren't the same.\n");

			int lit1 = atoi(get_name(loop_transferring_first_literal));
			int lit2 = atoi(get_name($2));
			int step = atoi(get_name($4));

			if(lit1 >= lit2)
				err("Start of the loop isn't smaller than the end.\n");

			// Dodatni uslovi
			if(step <= 0)
				err("Step needs to be a positive integer.\n"); 
			else if(step > (lit2 - lit1))
				err("Step needs to be lesser or equal to the difference in literals.\n");

			loop_transferring_second_literal = $2;
			// TODO: Dodaj za treci lit
		}
	statement
	;
//////////////////////////////////////////////////////////////////////////////////////////////
// Ovakvim switch-om ne onemogucujemo switch u switch-u, mada se to nece ni pregledati
// Moze da se napise switch[a] pa opet switch[a], to je podrzano
// TODO: Isto treba labele koje se ne resetuju, ali nema switch u switch-u
switch_statement
	: SWITCH LSQUAREBRACKET ID 
		{
			// Postavljanje svakog elementa na INT_MIN da case 0 ne baci gresku
			// Ovo ce i resetovati niz i indekser sa svaki switch, ne mora da se radi u poslednjoj akciji
			for(int i = 0; i < ARRAY_LIMIT; i++)
				switch_array[i] = INT_MIN;
			switch_array_indexer = 0;

			// Provera da li je ID po kojem se radi switch vec definisana promenljiva, ako jeste ok je
			// Takodje, pamtimo tip te promenljive za proveru u svakom case-u, da li je literal dobrog tipa
			int idx = NO_INDEX;
			// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
			// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $3) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
					switch_type = get_type(j);
			}
			if(idx == NO_INDEX)
				idx = lookup_symbol($3, GVAR);
			if(idx == NO_INDEX)
				err("Variable or parameter '%s' in switch statement not defined.\n", $3);
		}
		RSQUAREBRACKET LCURLYBRACKET case_list otherwise_optional RCURLYBRACKET
	;

case_list
	: CASETOKEN literal {
		if(get_type($2) != switch_type)
			err("Type of literal not the same as type of switcher.\n");

		for(int i = 0; i < ARRAY_LIMIT; i++){
			if (switch_array[i] == atoi(get_name($2)))
				err("Literal already in use in switch statement.\n");
		}
		// Provere su ok, literal moze da se ubaci
		switch_array[switch_array_indexer] = atoi(get_name($2));
		switch_array_indexer++;
	} ARROW statement finish_optional // finish; ne moze po zadatku da se stavi unutar statement-a, tako da mora van viticastih
	| case_list CASETOKEN literal {
		if(get_type($3) != switch_type)
			err("Type of literal not the same as type of switcher.\n");

		for(int i = 0; i < ARRAY_LIMIT; i++){
			if (switch_array[i] == atoi(get_name($3)))
				err("Literal already in use in switch statement.\n");
		}
		switch_array[switch_array_indexer] = atoi(get_name($3));
		switch_array_indexer++;
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
	output = fopen("output.asm", "w+");

	synerr = yyparse();

	clear_symtab();
	fclose(output);
	
	if(warning_count)
		printf("\n%d warning(s).\n", warning_count);

	if(error_count) {
		remove("output.asm");
		printf("\n%d error(s).\n", error_count);
	}

	if(synerr)
    	return -1;  //syntax error
  	else if(error_count)
		return error_count & 127; //semantic errors
	else if(warning_count)
		return (warning_count & 127) + 127; //warnings
	else
		return 0; //OK
}