#ifndef FILE_INTERPRETE_H
#define FILE_INTERPRETE_H

#define MAX_LENGTH (10000)

#include "translate.h"

int interprete_fetch_register(Address*, int);
void interprete_store_register(char*, int);
void interprete_global();
void interprete_local();
void phase_4_interprete();

#endif
