#ifndef CODEGEN_H
#define CODEGEN_H

#include "defs.h"

// funkcije za zauzimanje, oslobadjanje registra
int take_reg(void);
void free_reg(void);
// oslobadja ako jeste indeks registra
void free_if_reg(int reg_index);

// ispisuje simbol (u odgovarajucem obliku)
// koji se nalazi na datom indeksu u tabeli simbola
char *gen_sym_name(int index); // Promenjeno sa void na char*

// generise CMP naredbu, parametri su indeksi operanada u TS-a
void gen_cmp(int operand1_index, int operand2_index);

// generise MOV naredbu, parametri su indeksi operanada u TS-a
void gen_mov(int input_index, int output_index);

#endif
