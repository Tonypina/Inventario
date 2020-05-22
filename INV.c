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

bool INV_Out(INV* this, char* code, int quantity ){

  if(INV_Search(this, code)){
    this->cursor->data.quantity -= quantity;
    return true;
  }
  return false;
}

bool INV_Add(INV* this, char* code, char* name, int quantity ){

  if(INV_Search(this, code)){
    this->cursor->data.quantity += quantity;
    return true;
  }
  INV_InsertBack(this, code, name, quantity);
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
/*
bool INV_InsertAfter( INV* this, int data ){
  assert( this );
    bool done = false;
    if( INV_IsEmpty( this ) || this->cursor == this->last ){
      done = INV_InsertBack( this, data );
    } else {
      Node* n = newNode( data );
      if( n ){
        done = true;
        n->next = this->cursor->next;
        this->cursor->next->prev = n;
        this->cursor->next = n;
        n->prev = this->cursor;
        ++this->len;
      } 
    }
    return done;
}
bool INV_InsertBefore( INV* this, int data ){
  assert( this );
    bool done = false;
    if( INV_IsEmpty( this ) || this->cursor == this->first ){
      done = INV_InsertBack( this, data );
    } else {
      Node* n = newNode( data );
      if( n ){
        done = true;
        n->prev = this->cursor->prev;
        this->cursor->prev->next = n;
        this->cursor->prev = n;
        n->next = this->cursor;
        ++this->len;
      } 
    }
    return done;
}
*/
/**
 * @brief Remueve de la lista el elemento al cual apunta el cursor.
 *
 * @param this Referencia a un objeto INV.
 * @param data_back El valor (data) leído del nodo. Si la función regresa false,
 * entonces el valor de data_back no tiene sentido y no debería ser usado.
 *
 * @return true si la lista NO estaba vacía, o el cursor NO apuntaba a Null, y
 * el valor se pudo extraer; false si la lista estaba vacía o si el cursor
 * apuntaba a Null.
 */
/*
bool INV_Remove( INV* this, int* data_back ){
    assert( this );
    bool done = false;
    if( !INV_IsEmpty( this ) && NULL != this->cursor ){
      done = true;
      *data_back = this->cursor->data;
      Node* left = this->cursor->prev;
      Node* right = this->cursor->next;
      free( this->cursor );
      if( left == NULL && right == NULL ){
        reset( this );
      } else {
        this->cursor = left;
        this->cursor->next = right;
        right->prev = this->cursor;
        --this->len;
      }
    }
    return done;
}
bool INV_RemoveFront( INV* this, int* data_back ){
    assert( this );
    bool done = false;
    if( !INV_IsEmpty( this ) ){
      done = true;
      *data_back = this->first->data;
      Node* tmp = this->first->next;
      free( this->first );
      this->first = tmp;
      if( NULL != this->first ){
        this->first->prev = NULL;
        --this->len;
      } else {
        reset( this );
      }
    }
    return done;
}
bool INV_RemoveBack( INV* this, int* data_back ){
  assert( this );
    bool done = false;
    if( !INV_IsEmpty( this ) ){
      done = true;
      *data_back = this->last->data;
      Node* tmp = this->last->prev;
      free( this->last );
      this->last = tmp;
      if(NULL != this->last ){
        this->last->next = NULL;
        --this->len;
      } else {
        reset( this );
      }
    }
    return done;
}
bool INV_RemoveAfter( INV* this, int* data_back ){
    assert( this );
    bool done = false;
    if(INV_IsEmpty( this ) == false && // lista no vacía Y
    this->cursor != this->last && // existe un nodo a la derecha Y
    this->cursor != NULL ) { // el cursor no es NULL
      done = true;
      Node* tmp1 = this->cursor->next;
      *data_back = tmp1->data;
      Node* tmp2 = tmp1->next;
      free( tmp1 );
      this->cursor->next = tmp2;
      if( tmp2 != NULL ) {
        tmp2->prev = this->cursor;
      }
    }
    return done;
}
bool INV_RemoveBefore( INV* this, int* data_back ){
  assert( this );
    bool done = false;
    if( !INV_IsEmpty( this ) && // lista no vacía Y
    this->cursor != this->first && // existe un nodo a la izquierda Y
    this->cursor ) { // el cursor no es NULL
      done = true;
      Node* tmp1 = this->cursor->prev;
      *data_back = tmp1->data;
      Node* tmp2 = tmp1->prev;
      free( tmp1 );
      this->cursor->prev = tmp2;
      if( tmp2 ) {
        tmp2->next = this->cursor;
      }
    }
    return done;
}
*/
size_t INV_Len( INV* this ){
  return this->len;
}

bool INV_IsEmpty( INV* this ){
  return (this->len);
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
/**
 * @brief Observa el valor apuntado por el cursor.
 *
 * @param this Referencia a un objeto INV.
 * @param data_back El valor (data) leído del nodo. Si la función regresa false,
 * entonces el valor de data_back no tiene sentido y no debería ser usado.
 *
 * @return true si la lista NO estaba vacía, o el cursor NO apuntaba a Null, y
 * el valor se pudo extraer; false si la lista estaba vacía o si el cursor
 * apuntaba a Null.
 *
 * @pre El cursor debe estar apuntando a algún nodo válido. Vea las diferentes
 * funciones del cursor.
 *
 * @post El estado interno de la lista no se ve afectado.
 */
/*
bool INV_Peek( INV* this, int* data_back ){
  assert(this);
  done = false;
  if (this){
    *data_back = this->cursor->data;
    done = true;
  }
  return done;
}
*/
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
/*
bool INV_FindIf( INV* this, int key ){
    assert( this );
    bool found = false;
    for( Node* it = this->first; it != NULL && found == false; it = it->next ){
      if( key == it->data ){
        found = true;
      }
    }
    return found;
}
*/
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

/**
 * @brief Recorre la lista ejecutando la acción dada por pfun.
 *
 * @param this Referencia a un objeto INV.
 * @param pfun Un apuntador a función. Esta función será llamada (callback) una
 * vez por cada elemento de la lista.
 */
/*
void INV_Traverse( INV* this, void (*pfun)(int) ){
  assert( this );
    for( Node* it = this->first; it != NULL; it = it->next ){
      pfun( it->data );
  }
}
*/
