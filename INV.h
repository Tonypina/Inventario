#ifndef  INV_INC
#define  INV_INC

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
//#include <stdio_ext.h>

#define TAM_CODE 7
#define TAM_NAME 31

typedef struct Product{

	char code[TAM_CODE];
	char name[TAM_NAME];
	int quantity;
} Product;

typedef struct Node
{
	struct Product data;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct INV
{
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;
} INV;

INV* INV_New();
void INV_Delete( 		INV** this 						);
bool INV_InsertBack( 	INV* this, char* code, char* name, int quantity );
bool INV_InsertFront( 	INV* this, char* code, char* name, int quantity );
bool INV_InsertAfter( 	INV* this, char* code, char* name, int quantity );
size_t INV_Len( 		INV* this 						);
bool INV_IsEmpty( 		INV* this 						);
void INV_MakeEmpty( 	INV* this 						);
bool INV_Peek(          INV* this, char* code, char* name, int* quantity);
bool INV_Search( 		INV* this, char* code 			);
void INV_CursorFirst(   INV* this                       );
void INV_CursorLast(    INV* this                       );
void INV_CursorNext(    INV* this                       );
void INV_CursorPrev(    INV* this                       );
bool ord_insercion( INV* this, char* code, char* name, int quantity );

#endif   /* ----- #ifndef INV_INC  ----- */
