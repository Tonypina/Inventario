#include "INV.h"

static Node* newNode( char* code, char* name, int quantity )
{
  Node* n = (Node*) malloc( sizeof( Node ) );
    if( n ){
      strcpy(n->data.code, code);
      strcpy(n->data.name, name);
      n->data.quantity = quantity;
      n->next = NULL;
      n->prev = NULL;
    }
  return n;
}

static void reset( INV* this )
{
    this->first = this->last = this->cursor = NULL;
    this->len = 0;
}

INV* INV_New(){
  INV* list = (INV*) malloc( sizeof( INV ) );
    if( list ){
      reset( list );
    }
    return list;
}

void INV_Delete( INV** this ){
  assert(this);
  INV* l = *this;
  if (l){
    while (l->len){
      Node* n = l->last->prev;
      l->last = n;
      free (l->last->next);
      --l->len;
    }
  }
  free(*this);
  *this = NULL;
}

void INV_PrintNode(INV* this, char* name){
  INV_Peek(this, name);
  printf("%s\n", name);
}

bool INV_Out(INV* this, char* code, int quantity ){

  if(INV_Search(this, code)){
    if(this->cursor->data.quantity > 0){
      this->cursor->data.quantity -= quantity;
      return true;
    }
    return false;
  }
  return false;
}

bool INV_Add(INV* this, char* code, char* name, int quantity ){

  if(INV_Search(this, code)){
    this->cursor->data.quantity += quantity;
    return true;
  }

  //printf("Antes del insert\n");
  INV_InsertBack(this, code, name, quantity);
  //printf("Depues del insert\n");
  return true;
}

bool INV_InsertBack( INV* this, char* code, char* name, int quantity ){
    assert( this );
    bool done = false;
    Node* n = newNode( code, name, quantity );
    if( n ){
      done = true;
      if(!INV_IsEmpty( this )){
        this->last->next = n;
        n->prev = this->last;
        this->last = n;
      } else {

        this->first = this->last = n;
      }
      ++this->len;
      return done;
    }
}

bool INV_InsertFront( INV* this, char* code, char* name, int quantity ){
  assert( this );
    bool done = false;
    Node* n = newNode( code, name, quantity );
    if( n ){
      done = true;
      if(!INV_IsEmpty( this )){
        this->first->prev = n;
        n->next = this->first;
        this->first = n;
      } else {
        this->first = this->last = n;
      }
      ++this->len;
    }
    return done;
}

size_t INV_Len( INV* this ){
  return this->len;
}

bool INV_IsEmpty( INV* this ){
  return (!this->len);
}

void INV_MakeEmpty( INV* this )
{
    assert( this );
    while( NULL != this->first){
      Node* tmp = this->first->next;
      free( this->first );
      this->first = tmp;
    }
    reset( this );
}

void INV_CursorFirst( INV* this ){
    assert( this );
    this->cursor = this->first;
}

void INV_CursorLast( INV* this ){
  assert(this);
  this->cursor = this->last;
}

void INV_CursorNext( INV* this ){
    assert( this );
    if( this->cursor ){
      this->cursor = this->cursor->next;
    }
}

void INV_CursorPrev( INV* this ){
  assert( this );
  if (this->cursor){
    this->cursor = this->cursor->prev;
  }
}

bool INV_Peek( INV* this, char* data_back ){
  assert(this);
  bool done = false;
  if (this){
    strcpy(data_back, this->cursor->data.name);
    done = true;
  }
  return done;
}

bool INV_Search( INV* this, char* code ){
  assert( this );
    bool found = false;
    for( Node* it = this->first; it != NULL && found == false; it = it->next ){
      if( !strcmp(code, it->data.code) ){
        found = true;
        this->cursor = it;
      }
    }
    return found;
}
