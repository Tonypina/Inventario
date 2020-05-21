#ifndef  INV_INC
#define  INV_INC

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Product{
	int code;
	char name;
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
bool INV_InsertBack( 	INV* this, int data 			);
bool INV_InsertFront( 	INV* this, int data 			);
bool INV_InsertAfter( 	INV* this, int data 			);
bool INV_InsertBefore(	INV* this, int data 			);
bool INV_Remove( 		INV* this, int* data_back 		);
bool INV_RemoveFront( 	INV* this, int* data_back 		);
bool INV_RemoveBack( 	INV* this, int* data_back 		);
bool INV_RemoveAfter( 	INV* this, int* data_back 		);
bool INV_RemoveBefore(	INV* this, int* data_back 		);
size_t INV_Len( 		INV* this 						);
bool INV_IsEmpty( 		INV* this 						);
void INV_MakeEmpty( 	INV* this 						);
bool INV_Peek( 			INV* this, int* data_back 		);
void INV_CursorFirst( 	INV* this 						);
void INV_CursorLast( 	INV* this 						);
void INV_CursorNext( 	INV* this 						);
void INV_CursorPrev( 	INV* this 						);
bool INV_FindIf( 		INV* this, int key 				);
bool INV_Search( 		INV* this, int key 				);
void INV_Traverse( 		INV* this, void (*pfun)(int) 	);

#endif   /* ----- #ifndef INV_INC  ----- */