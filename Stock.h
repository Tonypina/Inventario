#ifndef Stock_INC
#define Stock_INC

#include "INV.h"

void Stock_clear_screen(                                              );
void Stock_PrintNode( INV* this, char* name                           );
bool Stock_Out(       INV* this, char* code, int quantity             );
bool Stock_Add(       INV* this, char* code, char* name, int quantity );
void Stock_Archive(   INV* this                                       );
void Stock_Menu(      INV* this                                       );

#endif    /* ----- #ifndef Stock_INC -----*/
