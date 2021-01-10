// Djordje Stankovic IN13/2018

/*
Default atributi u Tabeli Simbola :
Atribut 1 :
- Za lokalnu promenljivu (varijablu) - redni broj promenljive po definisanju u funkciji,
- Za parametar - redni broj parametra (mora da bude zbog GK-a),
- Za funkciju – broj parametara (0 ili 1),
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
codegen.c i codegen.h su izmenjeni, dodata funkcija print_sym_name() koja vraca string za switch.
Nacin na koji "menjamo" atribute u tabeli simbola je samo menjanjem unosa pri pozivanju insert_symbol ili set_atr.

Iz tabele mi se ne brisu parametri funkcija, jer iz tabele simbola proveravam argumente pri pozivu funkcije

ASM parsing error znaci da se HipSim-u ne prosledjuje .asm fajl
Ako nema //RETURN:, to ce biti PASSED
Samo ok testovi treba da imaju //RETURN:
Postoje i warn testovi

Za test-ok-kt2-v7-3-1.mc (koji je sa vezbi) sam morao da promenim return na 54 umesto 53 zbog implementacije post-inkrement-a, ja sam koristio objasnjenje na pdf-u sa vezbi, ali je trazeni rezultat dobijen preko standardnog gcc nacina inkrementiranja.
Kod mene se y++ inkrementira nakon dodele, ali u gcc-u assign to override-uje, i inkrement se nece desiti.
Na primer, za a == 1, a = a++ + a++, gcc nacin (koji ovde nije implementiran) ce raditi ovako :
- Prvo a++ ce biti 1, jer se ++ radi tek posle
- Kada dodje do + izmedju, uradio se taj ++, i sada je a postalo 2, ali je leva strana jos uvek 1
- Onda ce biti 1 + 2 sve to, a ovo drugo a++ nema uticaja jer ce ga override-ovati celokupna dodela
Da smo imali jos nesto da saberemo posle toga, onda bi se a ponovo uvecalo.
Tako da je rezultat 3, a ne 4.
Dakle ++ ce menjati sledece a, a ne to na kojem je zakaceno, osim poslednjeg a++ koji ne menja nista.
y = x++ + y++ ce po gcc-u inkrementovati x posle, ali y nece - po mojoj implementaciji ce inkrementovati i y.
Takodje, a = a++; nece da inkrementuje po gcc-u, ali ovde hoce.
Ostale testove nisam morao da menjam, jer su izgleda rezultati dobijeni ovim nacinom.
Znaci pretpostavljamo da je svaki ID maksimalno jednom inkrementiran u assign_statement-u, jer je tako na pdf-u prikazan asembler, zapravo po gcc-u treba da se uveca za 1 ako se ID inkrementovao dvaput u izrazu, ili da se uveza za 3 ako se pojavio triput, etc.
Za a == 1, a = ++a + ++a ce biti 6, jer prvo inkrementuje a pa opet ink a, pa sabira a i a, koje je 3 + 3.

Sanity test sam promenio da ima return, jer sanity testovi ne prolaze ako baca warning.
*/

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "defs.h"
	#include "symtab.h"
	#include <string.h> // Za strcmp
	#include "codegen.h" // KT2

	#define ARRAY_LIMIT 100
	#define INT_MIN -2147483648 // Ili -32766? Jer je ovo mozda long min? Ne menja stvari.

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
	int loop_depth = -1; // Ovo je indekser za gornji stek
	int loop_transferring_type = 0; // (NO_TYPE)
	int loop_transferring_id = 0;
	int loop_transferring_first_literal = 0; // Ovo su indeksi literala, a ne tacne vrednosti 
	int loop_transferring_second_literal = 0;
	int loop_transferring_third_literal = 0;
	unsigned switch_type = 0; // unsigned je jer get_type vraca unsigned
	int switch_array[ARRAY_LIMIT]; // Niz literala trenutnog switch-a za proveru koriscenih, na pocetku switch-a se sve inicijalizuje na INT_MIN
	int switch_array_indexer = 0;

	// KT2
	int out_lin = 0;
	int lab_num_if = -1; // Prvobitno bio samo loop_num
	FILE *output; // Vidi main() skroz dole, tu se inicijalizuje

	int argument_pusher_array[ARRAY_LIMIT]; // Niz indeksa registra koji imaju vrednosti num_exp-ova koji se prosledjuju u pozivu funkcije, da bi mogao da argumente push-ujem na stackframe u obrnutom redosledu
	int increment_todo_array[ARRAY_LIMIT] = {0}; // Niz indeksa ID-eva koji trebaju da se inkrementuju
	int increment_array_indexer = 0;
	int transferring_id_array[ARRAY_LIMIT] = {0}; // Niz ID-eva za prenos u ugnjezdene for-ove, nulti element uvek nula
	int transferring_second_literal_array[ARRAY_LIMIT] = {0}; // Niz drugih literala za prenos u ugnjezdene for-ove, nulti element uvek nula
	int transferring_third_literal_array[ARRAY_LIMIT] = {0}; // Niz trecih literala za prenos u ugnjezdene for-ove, nulti element uvek nula
	int loop_depth_plus_one = 0; // Indekser za gornje nizove, veci je od loop_depth-a za 1 jer zelimo da preskocimo nulti element
	int switch_transferring_id = 0;
	int in_case_flag_register = 0;
	// lab_num-ovi moraju da se razdvoje za razlicite pojmove da bi moglo da funkcionise ugnjezdavanje (if u switch-u, switch u for-u, etc)
	int lab_num_ternary = 0; // Samo je ovaj na 0 
	int lab_num_switch = -1;
	int lab_num_loop = -1;
	int in_loop = 0; // Flag za skip i terminate
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
%token QUESTIONMARK
%token COLON
%token SKIP
%token TERMINATE

%type <i> num_exp exp literal function_call arguments rel_exp argument_list if_part increment_optional loop_first_part loop_second_part switch_statement finish_optional ternary_operator assign_optional

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
			code("\n%s:\n\t\tWORD\t1", $2); // Generisanje koda za GVAR
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
				// Ako ne postoji dodaje se uz inicijalizovanje broja parametara na 0 (tek treba da se puni) (atr2 vise nije nista za funkcije)
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
			// Kada se funkcija zavrsi moramo da izbrisemo sve njene lokalne varijable 
			// Ne diramo parametre, jer ih koristimo za pozive funkcija
			// clear_symbols brise od ovog indeksa pa na dole, pa ce nam ostati samo parametri
			int var_start_index = fun_idx + parameter_number + 1;
			clear_symbols(var_start_index);
			// Resetujemo var_num za sledece funkcije
			var_num = 0;
			// Non-void funkcije moraju imati povratnu vrednost, pa koristimo flag da proverimo da li smo ga iskoristili
			if(return_flag == 0)
				warn("Function '%s' needs to have the 'return' keyword.\n", $2);
			// Resetujemo return flag i broj parametara za nove funkcije
			return_flag = 0;
			parameter_number = 0;

			// Izlaz iz funkcije - exit labela, "brisanje" stackframe-a i ret
			code("\n@%s_exit:", $2);
			code("\n\t\tMOV \t%%14,%%15"); // Podizemo %esp
			code("\n\t\tPOP \t%%14"); // Resetujemo %ebp
			code("\n\t\tRET"); // Povratnu adresu stavljamo u PC i pomeramo %esp na gore
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
		a ovako kazemo da ova alternativa mora imati bar 1 parametar. */
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
			parameter_number++;
			// Pri ubacivanju parametra, postavlja mu se redni broj (sluzi za generisanje koda), kao i nivo, koji je uvek 0 (sluzi za kasniju proveru u operacijama)
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
				// Lokalne promenljive ce ostati na stackframe-u dok se ne overwrite-uju, pa zato nema ADDS za ovaj SUBS, nema potrebe, jer ce odmah u exit labeli funkcije da se radi MOV %14, %15, sto pomera %esp na gore (ADDS ce biti za argumente posle CALL-a)
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

/* variables_only
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
			// Ne radi se provera za GVAR jer promenljiva moze da ima isto ime, samo ce se vrednost overwrite-ovati u tom scope-u
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
	; */

variables_only
	: ID assign_optional
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
			// Ne radi se provera za GVAR jer promenljiva moze da ima isto ime, samo ce se vrednost overwrite-ovati u tom scope-u
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), $1) == 0 && get_atr2(i) == block_level){ // Mora == kada definisemo varijablu
					err("Variable or parameter by the name '%s' already exists on this level.\n", $1);
				}
			}
			if($2 != -1 && vartype != get_type($2)) // Ako je bilo assignment-a
				err("Types in variable declaration do not match!\n");
			var_num++;
			int idx = insert_symbol($1, VAR, vartype, var_num, block_level);
			if($2 != -1)
				gen_mov($2, idx);
		}
	| variables_only COMMA ID assign_optional
		{
			// Ista provera i za ovu alternativu
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), $3) == 0 && get_atr2(i) == block_level){
					err("Variable or parameter by the name '%s' already exists on this level.\n", $3);
				}
			}
			if($4 != -1 && vartype != get_type($4)) // Ako je bilo assignment-a
				err("Types in variable declaration do not match!\n");
			var_num++;
			int idx = insert_symbol($3, VAR, vartype, var_num, block_level);
			if($4 != -1)
				gen_mov($4, idx);
		}
	;

assign_optional
	: 
		{
			$$ = -1;
		}
	| ASSIGN num_exp
		{
			$$ = $2;
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
	| skip
	| terminate
	;

// Svaki compound_statement se razlikuje po svom nivou, koji je atr2 kod njegovih lokalnih varijabli
// GVAR ovo nece imati, samo VAR, a nivo 0 je nivo main-a, odnosno nulti blok (svim PAR-ovima je nivo 0)
// Sve novodefinisane varijable u bloku se brisu na kraju bloka iz tabele simbola preko clear_symbols()
// Ako je na prvom nivou x definisano, moze i na drugom nivou opet da se definise, ali ce se vrednost overwrite-ovati (kao sa GVAR-ovima)
// Ako se ne redefinise, nego se samo vrednost promeni, vrednost ce se promeniti i u prethodnom bloku (kao sa GVAR-ovima) (tako je u C-u)
compound_statement
	: LCURLYBRACKET
		{
			// Na pocetku svakog bloka se povecava nivo, prvi novi blok ce biti nivoa 1
			block_level++;
		}
	variable_list statement_list RCURLYBRACKET // Ovo je zapravo body, razdvojen zbog semantike, ali ne dolazi do konflikta verovatno zbog ove akcije gore
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
			if($2 + (type - 1) * AROP_NUMBER >= 0){ // Da bi izbegli segfault kod semerr nas 43, moramo da proverimo da li ar_instructions izlazi iz opsega i ulazi u nepristupacnu memoriju, to ce se desiti kada je type == 0, odnosno kada je $1 neki indeks koji nije u tabeli simbola (f++ ne nalazi f kao promenljivu, pa $1 vraca -1)
				// num_exp ce biti npr ADDS %1, %3, %4
				// biramo aritmeticku operaciju na osnovu parsiranog AROP-a i tipa num_exp-a - $2 je vrsta operacije (ADD ili SUB), a ovaj proizvod je ili 0 ili 4 (AROP_NUMBER je makro za 4) i bira signed ili unsigned verziju operacije (ima 4 zbog MUL i DIV)
				code("\n\t\t%s\t", ar_instructions[$2 + (type - 1) * AROP_NUMBER]);
				// Operandi
				gen_sym_name($1); // Ovo je valjda uvek registar
				code(",");
				gen_sym_name($3); // Ovo ne mora da bude registar
				code(",");
				// Oslobadjamo odmah zauzete registre (ako ih ima) u obrnutom redosledu (jer smo rezultat dobili i stavljamo ga u novi registar ($$ dole))
				free_if_reg($3);
				free_if_reg($1);
				$$ = take_reg(); // Semanticka vrednost je indeks registra sa rezultatom
				gen_sym_name($$); // Generise asm kod za taj registar kao rezultat operacije
				set_type($$, type); // Postavljamo tip registra koji sadrzi vrednost num_exp-a na tip samog num_exp-a
			}
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
	| ternary_operator
	;

ternary_operator
	: LPAREN rel_exp RPAREN QUESTIONMARK ID COLON ID // Ne mora @ternary_start0, bacace konflikt ako se doda ovde
		{
			int idx = NO_INDEX;
			int idy = NO_INDEX;
			// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
			// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $5) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
				if(strcmp(get_name(j), $7) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idy = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
			}
			if(idx == NO_INDEX)
				idx = lookup_symbol($5, GVAR);
			if(idy == NO_INDEX)
				idy = lookup_symbol($7, GVAR);
			if(idx == NO_INDEX)
				err("'%s' undeclared.\n", $5);
			if(idy == NO_INDEX)
				err("'%s' undeclared.\n", $7);

			if(get_type(idx) != get_type(idy))
				err("Different types of ID's in expression!\n");

			$$ = take_reg();
			// Zauzima se registar opste namene u koji ce da se stavlja rezultat operatora
			// Oslobodice se u num-exp-u preko free_if_reg() tamo, isto kao kod function_call 
			// $$ mora da se postavi jer exp mora da ima semanticku vrednost koja je indeks u tabeli simbola

			// Zamisli ovde code() iz rel_exp-a koji ispisuje CMP, onda posle toga treba uslovni skok na osnovu operacije koja je bila, a to dobijamo iz semanticke vrednosti rel_exp-a
			// Ako je bilo >=, indeks $2 bi bio za JGES, a nama za skok na labelu za povracaj drugog id-a treba oppjumps, pa bi bilo JLTS
			// Ako ne skoci, vraca prvi ID za u num_exp, ako skoci vraca drugi
			code("\n\t\t%s\t@ternary_second_id%d", opp_jumps[$2], lab_num_ternary); 
			gen_mov(idx, $$); // Prvi ID se postavlja kao povratna vrednost
			code("\n\t\tJMP \t@ternary_exit%d", lab_num_ternary); // Da ne udje u labelu za drugi ID

			code("\n@ternary_second_id%d:", lab_num_ternary);
			gen_mov(idy, $$); // Drugi ID se postavlja kao povratna vrednost
			
			code("\n@ternary_exit%d:", lab_num_ternary++); // Inkrementiramo lab_num_ternary za sledece ternarne
			// Nastavlja sa naredbama za num_exp
		}
	| LPAREN rel_exp RPAREN QUESTIONMARK ID COLON literal
		{
			int idx = NO_INDEX;
			// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
			// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $5) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
			}
			if(idx == NO_INDEX)
				idx = lookup_symbol($5, GVAR);
			if(idx == NO_INDEX)
				err("'%s' undeclared.\n", $5);

			if(get_type(idx) != get_type($7))
				err("Different types of operands in expression!\n");

			$$ = take_reg();
			code("\n\t\t%s\t@ternary_second_lit%d", opp_jumps[$2], lab_num_ternary); 
			gen_mov(idx, $$);
			code("\n\t\tJMP \t@ternary_exit%d", lab_num_ternary);
			code("\n@ternary_second_lit%d:", lab_num_ternary);
			gen_mov($7, $$);
			code("\n@ternary_exit%d:", lab_num_ternary++);
		}
	| LPAREN rel_exp RPAREN QUESTIONMARK literal COLON ID
		{
			int idy = NO_INDEX;
			// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
			// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), $7) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idy = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
			}
			if(idy == NO_INDEX)
				idy = lookup_symbol($7, GVAR);
			if(idy == NO_INDEX)
				err("'%s' undeclared.\n", $7);

			if(get_type($5) != get_type(idy))
				err("Different types of operands in expression!\n");

			$$ = take_reg();
			code("\n\t\t%s\t@ternary_second_lit%d", opp_jumps[$2], lab_num_ternary); 
			gen_mov($5, $$);
			code("\n\t\tJMP \t@ternary_exit%d", lab_num_ternary);
			code("\n@ternary_second_lit%d:", lab_num_ternary);
			gen_mov(idy, $$);
			code("\n@ternary_exit%d:", lab_num_ternary++);
		}
	| LPAREN rel_exp RPAREN QUESTIONMARK literal COLON literal
		{
			if(get_type($5) != get_type($7))
				err("Different types of literals in expression!\n");

			$$ = take_reg();
			code("\n\t\t%s\t@ternary_second_lit%d", opp_jumps[$2], lab_num_ternary); 
			gen_mov($5, $$);
			code("\n\t\tJMP \t@ternary_exit%d", lab_num_ternary);
			code("\n@ternary_second_lit%d:", lab_num_ternary);
			gen_mov($7, $$);
			code("\n@ternary_exit%d:", lab_num_ternary++);
		}
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
			// Nakon poziva, kada funkcija zavrsi sa radom, moramo da "izbrisemo" mesta za argumente koji su joj prosledjeni (ovaj if nije ni potreban)
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

TODO: Ne moze poziv u pozivu zbog toga sto je argument_number globalna promenljiva, pa se izmesa kada se radi poziv u pozivu, za to bi morao da pravim niz dubina poziva funkcija, gde svaka dubina ima svoj argument number
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
			// Prva labela je za uslov u zagradama, pravimo labelu uz lab_num_if
			$<i>$ = ++lab_num_if; // Bio je na -1 da bi "stablo ugnjezdenih if-ova" pocelo od nulte labele
        	code("\n@if%d:", lab_num_if);
		}
	rel_exp // rel_exp generise CMP instrukciju za prvu labelu (vidi dole)
		{
			// $<i>3 je trenutni lab_num_if, za taj nivo if-a, odnosno semanticka vrednost prve akcije
			// Koristimo ga ovako a ne preko lab_num_if jer ce se lab_num_if menjati kako pravimo if-ove u if-u
			// Znaci ovako ce sigurno ta semanticka vrednost da ostane na istom nivou ($<i>$ je lokalno samo za trenutni pojam, a lab_num_if je globalna vrednost)
			// lab_num_if se nigde ne resetuje, tako da ako imamo jednom neke if u if-u u if-u itd, ako izadjemo iz svega toga i ponovo imamo neki if, on nece biti prvi, nego npr sesti (kao sto i treba, ako se resetuje lab_num_if, onda ce se simulator vracati na pogresan if gore cak, a treba da ide dole)
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
			// Pa ce semanticka vrednost rel_exp-a biti indeks odgovarajuceg uslovnog skoka u enumeraciji jumps
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

// loop sam odvojio u 2 dela da bih prvo ID ubacio u tabelu simbola, pa tek onda literale, zbog kasnijeg oslobadjanja tabele simbola, jer je mnogo lakse kada znam tacno od kog indeksa pocinje loop, da bih kasnije sa stekom indeksa tih ID-eva lakse oslobodio
// Za gen_cmp indeks, za code atoi
loop
	: loop_first_part loop_second_part 
		{
			// Kraj loop-a, bilo da je ugnjezden ili ne - provera uslova i izlazak iz fora ili vracanje na pocetak
			// labela za taj deo zbog skip-a
			// ADDS 1 ili step    1
			// CMP limit          2
			// JGES start         3
			// JMP exit           4
			code("\n@loop_cmp%d:", $1); // Zbog JMP u skip
			if(get_type(loop_transferring_id) == INT){
				code("\n\t\tADDS \t");
			}else if(get_type(loop_transferring_id) == UINT){
				code("\n\t\tADDU \t");
			}
			gen_sym_name(loop_transferring_id);
			if($2 == 0)
				code(",$1,"); // Nema step
			else if($2 == 1)
				code(",$%d,", atoi(get_name(loop_transferring_third_literal))); // Ima step
			gen_sym_name(loop_transferring_id);

			gen_cmp(loop_transferring_id, loop_transferring_second_literal); // Poredi trenutan i i kraj 
			
			if(get_type(loop_transferring_id) == INT){
				code("\n\t\tJGES \t@loop_exit%d", $1); // Semanticka vrednost prvog dela je labela (lab_num_loop)
			}
			else if(get_type(loop_transferring_id) == UINT){
				code("\n\t\tJGEU \t@loop_exit%d", $1);
			}
			
			code("\n\t\tJMP \t@loop_start%d", $1); // Skocice ako ne prodje CMP
			code("\n@loop_exit%d:", $1);

			// Brisanje simbola za loop iz tabele preko steka
			clear_symbols(stack_of_loop_starts_indexes[loop_depth]);
			loop_depth--; // Vracamo se na manji nivo

			// Resetovanje za sledeci for, ili za prethodni for ako se vracamo iz ugnjezdenog
			// Bez obzira na dubinu for-ova, vracamo loop_depth_plus_one na nivo manje da bi pravilno resetovali
			// Imaj na umu da je nulti element ovih nizova dole tacno nula
			// Ako je bio samo jedan for, uzece taj nulti element i resetovace id i drugi literal na nulu (vise nismo u for-ovima, pa resetujemo za neki tamo sledeci for)
			// Ako je bio ugnjezden for, uzece nazad id i drugi literal tog prethodnog for-a, da bi pravilno nastavio njegovo izvrsavanje
			loop_depth_plus_one--;
			loop_transferring_id = transferring_id_array[loop_depth_plus_one]; // Ako je ldpo 0, lti ce biti 0
			loop_transferring_second_literal = transferring_second_literal_array[loop_depth_plus_one]; // Ako je ldpo 0, ltsl ce biti 0
			loop_transferring_third_literal = transferring_third_literal_array[loop_depth_plus_one]; // Ako je ldpo 0, lttl ce biti 0
			// loop_transferring_type i loop_transferring_first_literal ne moramo da postavljamo na 0 jer ce se overwrite-ovati u novom for-u
			in_loop--; // Za skip i terminate (mora dekrement umesto = 0 zbog ugnjezdavanja)
		}
	;

loop_first_part
	: FOR LPAREN TYPE ID ASSIGN literal // Prvi literal mora ovde zbog gen_mov-a
		{
			// TYPE ID mora da napravi lokalnu promenljivu, i to samo u scope-u iteracije, ne moze da se koristi ako vec postoji definisana na tom scope-u (nivou) (definisanje -> == block_level, znaci slicno kao variables_only)
			// Zapravo ce se praviti novi nivo zbog compound_statement-a
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), $4) == 0 && get_atr2(i) == block_level){ // Mora == (GVAR ne ubrajamo u proveru za gresku jer moze da ga redefinise)
					err("Variable or parameter by the name '%s' already exists on this level.\n", $4);
				}
			}
			var_num++;
			loop_depth++; // Za prvi for ce preci sa -1 -> 0 (ovo je dubina ugnjezdenih for-ova)
			int idx = insert_symbol($4, VAR, $3, var_num, loop_depth); // Pravimo int i, za block_level se stavlja loop_depth, jer je svaki for novi blok 
			stack_of_loop_starts_indexes[loop_depth] = idx; // Punimo stek indeksom ID-a za kasniji clear_symbols()

			// Postavljamo promenljive za prenos u druge pojmove i za ugnjezdene for-ove
			loop_transferring_type = $3;
			loop_transferring_id = idx;
			loop_transferring_first_literal = $6; // Postavlja indeks, ne stvarnu vrednost literala
			loop_depth_plus_one++; // Za prvi for ce preci sa 0 -> 1, da bi ostavili nulti kao nula
			transferring_id_array[loop_depth_plus_one] = idx; // Pocinje da se puni od drugog elementa, da bi ostavili nulti kao nula

			gen_mov(loop_transferring_first_literal, loop_transferring_id); // int i = 1
			// Pocinju naredbe u loop-u, pa moramo da pravimo labelu za povratni skok na pocetak
			lab_num_loop++; // Svaki for ima svoju labelu, koristi se promenljiva bas za loop zbog ugnjezdenosti, ne resetuje se
			$$ = lab_num_loop; // Potrebno za semanticku analizu za kraj loop-a (kao kod if-a)
			code("\n@loop_start%d:", lab_num_loop);
			in_loop++; // Za skip i terminate (mora inkrement umesto = 1 zbog ugnjezdavanja)
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
			// Zbog ove provere moze CMP da stoji na kraju loop-a
			if(lit1 >= lit2)
				err("Start of the loop isn't smaller than the end.\n");

			// Postavljamo promenljive za prenos u druge pojmove i za ugnjezdene for-ove
			loop_transferring_second_literal = $2;
			transferring_second_literal_array[loop_depth_plus_one] = loop_transferring_second_literal; // Pocinje da se puni od drugog elementa, da bi ostavili nulti kao nula
		} 
	statement
		{
			$$ = 0; // Semanticka vrednost oznacava da for nema step (mora u poslednjoj akciji)
		}
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
			transferring_second_literal_array[loop_depth_plus_one] = loop_transferring_second_literal;
			loop_transferring_third_literal = $4;
			transferring_third_literal_array[loop_depth_plus_one] = loop_transferring_third_literal;
		}
	statement
		{
			$$ = 1; // Semanticka vrednost oznacava da for ima step (mora u poslednjoj akciji)
		}
	;

skip
	: SKIP SEMICOLON
		{
			if(in_loop == 0) // Ako je in_loop veci od 0, u nekom loop-u smo sigurno
				err("Skip statement called outside of loop!\n");
			code("\n\t\tJMP \t@loop_cmp%d", lab_num_loop); // Ne moze da skace na start, nego na kraj, jer je tu CMP iteratora
		}
	;

terminate
	: TERMINATE SEMICOLON
		{
			if(in_loop == 0)
				err("Terminate statement called outside of loop!\n");
			code("\n\t\tJMP \t@loop_exit%d", lab_num_loop);
		}
	;

// Ovakvim switch-om ne onemogucujemo switch u switch-u, mada se to nece ni pregledati
// Moze da se napise switch[a] pa opet switch[a], to je podrzano
// in_case_flag_register oznacava da je nadjen case u koji ulazimo (od kog zapocinjemo), ali kada udjemo u taj case, vise ne radimo proveru case-eva, nego samo nastavljamo izvrsavanje kroz ceo switch dok ne nadjemo finish - tako je u C-u, jer ako nema finish-a (break-a), samo ce uci u sledeci case (ili otherwise)
// Jedan od nacina provere case-ova je da se pre svega proveri ceo niz literala pa da se na odredjeni skoci, ali to ne moze ovde jer se taj niz puni kako se dodje do odredjenog case-a
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

			lab_num_switch++; // Svaki switch ima svoju labelu, koristi se promenljiva bas za switch, ne resetuje se
			// Posto ne moze da se napravi switch u switch-u, mozemo direktno da koristimo lab_num_switch za indeksiranje labela, ne treba nam $$ = lab_num_switch;
			code("\n@switch_start%d:", lab_num_switch); // Nebitna labela, ali dobra za debug
			switch_transferring_id = idx; // Ne $3
			in_case_flag_register = take_reg();
			code("\n\t\tMOV\t$0,%s", print_sym_name(in_case_flag_register)); // Skarabudzen gen_mov, print_sym_name()-u ne moze da se prosledi $0 nego samo indeks iz tabele simbola
		}
	RSQUAREBRACKET LCURLYBRACKET case_list otherwise_optional RCURLYBRACKET
		{
			code("\n@switch_exit%d:", lab_num_switch);
			free_if_reg(in_case_flag_register); // Reset za sledeci switch
			in_case_flag_register = 0; // Ovo je mozda nepotrebno
		}
	;

case_list
	: CASETOKEN literal
		{
			if(get_type($2) != switch_type)
				err("Type of literal not the same as type of switcher.\n");

			for(int i = 0; i < ARRAY_LIMIT; i++){
				if (switch_array[i] == atoi(get_name($2)))
					err("Literal already in use in switch statement.\n");
			}
			// Provere su ok, literal moze da se koristi

			code("\n@case%d_no%d:", lab_num_switch, switch_array_indexer);
			code("\n\t\tCMPS\t%s,$1", print_sym_name(in_case_flag_register)); // Skarabudzen gen_cmp jer ne prihvata $1 nego samo indekse iz tabele simbola. Proveravamo da li je registar postavljen na flag, odnosno da li smo usli u dobar case.
			code("\n\t\tJEQ\t@case%d_no%d_aftercmp", lab_num_switch, switch_array_indexer); // Nece skociti na aftercmp labelu ispod ovog CMP dole ako flag nije postavljen
			gen_cmp(switch_transferring_id, $2); // $2 jer uzima indeks, a ne tacnu vrednost

			switch_array[switch_array_indexer] = atoi(get_name($2));
			switch_array_indexer++; // Za sledeci
			
			code("\n\t\tJNE\t@case%d_no%d", lab_num_switch, switch_array_indexer); // Ide na sledeci case ako nije taj, ako jeste samo nastavlja izvrsavanje (code treba da bude ovde zbog inkrementiranja switch_array_indexer-a)
			code("\n\t\tMOV\t$1,%s", print_sym_name(in_case_flag_register)); // Usao u case, postavljamo flag, isto ne moze $1 u gen_mov
			code("\n@case%d_no%d_aftercmp:", lab_num_switch, switch_array_indexer - 1);
		} 
	ARROW statement finish_optional // finish; ne moze po zadatku da se stavi unutar statement-a, tako da mora van viticastih
		{
			if($6 == 1){ // Ako je bilo finish-a
				code("\n\t\tJMP \t@switch_exit%d", lab_num_switch);
			}
		}
	| case_list CASETOKEN literal 
		{
			if(get_type($3) != switch_type)
				err("Type of literal not the same as type of switcher.\n");

			for(int i = 0; i < ARRAY_LIMIT; i++){
				if (switch_array[i] == atoi(get_name($3)))
					err("Literal already in use in switch statement.\n");
			}
			code("\n@case%d_no%d:", lab_num_switch, switch_array_indexer);
			code("\n\t\tCMPS\t%s,$1", print_sym_name(in_case_flag_register));
			code("\n\t\tJEQ\t@case%d_no%d_aftercmp", lab_num_switch, switch_array_indexer);
			gen_cmp(switch_transferring_id, $3);
			switch_array[switch_array_indexer] = atoi(get_name($3));
			switch_array_indexer++;
			code("\n\t\tJNE\t@case%d_no%d", lab_num_switch, switch_array_indexer);
			code("\n\t\tMOV\t$1,%s", print_sym_name(in_case_flag_register)); // Usao u case
			code("\n@case%d_no%d_aftercmp:", lab_num_switch, switch_array_indexer - 1);
		} 
	ARROW statement finish_optional
		{
			if($7 == 1){ // Ako je bilo finish-a
				code("\n\t\tJMP \t@switch_exit%d", lab_num_switch);
			}
		}
	;

finish_optional
	: /* empty */
		{
			$$ = 0; // Nema finish-a
		}
	| FINISH SEMICOLON
		{
			$$ = 1; // Ima finish-a
		}
	;

otherwise_optional
	: /* empty */
	| OTHERWISE 
		{
			code("\n@case%d_no%d:", lab_num_switch, switch_array_indexer); // otherwise je poslednji case_no
		}
	ARROW statement
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