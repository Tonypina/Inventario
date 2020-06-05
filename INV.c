#include "INV.h"

/**
 * @brief Crea un nuevo nodo
 * @param code Codigo del producto
 * @param name Nombre del producto
 * @param quantity Cantidad de producto
 * @return Un nodo
 */
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

/**
 * @brief Resetea la lista
 * @param La lista a resetear
 */
static void reset( INV* this )
{
    this->first = this->last = this->cursor = NULL;
    this->len = 0;
}

/**
 * @brief Crea una lista (Inventario)
 * @return Una lista
 */
INV* INV_New(){
  INV* list = (INV*) malloc( sizeof( INV ) );
    if( list ){
      reset( list );
    }
    return list;
}

/**
 * @brief Borra la lista
 * @param La lista a borrar
 */
void INV_Delete( INV** this ){
  assert(this);
  INV* l = *this;
  if (l){
    while (l->len){
      
      if(l->len == 1){

        free(l->last);
        break;
      }

      Node* n = l->last->prev;
      l->last = n;
      free (l->last->next);
      --l->len;
    }
  }
  free(*this);
  *this = NULL;
}

/**
 * @brief Inserta un nodo al final de la lista
 * @param this La lista
 * @param code El codigo del producto
 * @param name El nombre del producto
 * @param quantity La cantidad de producto
 * @return Un valor booleano
 */
bool INV_InsertBack( INV* this, char* code, char* name, int quantity ){
    assert( this );
    bool done = false;
    Node* n = newNode( code, name, quantity );
    if( n ){
      done = true;
      if(!INV_IsEmpty( this ))
      {
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

/**
 * @brief Inserta un nodo al principio de la lista
 * @param this La lista
 * @param code El codigo del producto
 * @param name El nombre del producto
 * @param quantity La cantidad de producto
 * @return Un valor booleano
 */
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

/**
 * @brief Recupera el numero de elementos en la lista
 * @param this La lista
 * @return Numero de elementos en la lista
 */
size_t INV_Len( INV* this ){
  return this->len;
}

/**
 * @brief Indica si la lista esta vacia
 * @param this La lista
 * @return Un valor booleano
 */
bool INV_IsEmpty( INV* this ){
  return (!this->len);
}

/**
 * @brief Vacia la lista
 * @param this La lista
 */
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
 * @brief Mueve el cursor al primer nodo
 * @param this La lista
 */
void INV_CursorFirst( INV* this ){
    assert( this );
    this->cursor = this->first;
}

/**
 * @brief Mueve el cursor al ultimo nodo
 * @param this La lista
 */
void INV_CursorLast( INV* this ){
  assert(this);
  this->cursor = this->last;
}

/**
 * @brief Mueve el cursor al nodo siguiente del que apunta
 * @param this La lista
 */
void INV_CursorNext( INV* this ){
    assert( this );
    if( this->cursor ){
      this->cursor = this->cursor->next;
    }
}

/**
 * @brief Mueve el cursor al nodo anterior del que apunta
 * @param this La lista
 */
void INV_CursorPrev( INV* this ){
  assert( this );
  if (this->cursor){
    this->cursor = this->cursor->prev;
  }
}

/**
 * @brief Recupera los datos de un nodo
 * @param this La lista
 * @param code Arreglo para guardar el codigo del producto
 * @param name Arreglo para guardar nombre del producto
 * @param quantity Variable para guardar el valor de la cantidad
 * @return Un valor booleano
 */
bool INV_Peek(INV* this, char* code, char* name, int* quantity){
  assert(this);
  bool done = false;
  if (this){
    strcpy(name, this->cursor->data.name);
    strcpy(code, this->cursor->data.code);
    *quantity = this->cursor->data.quantity;
    done = true;
  }
  return done;
}

/**
 * @brief Busca un producto en la lista
 * @param this La lista
 * @param code El codigo del producto a buscar
 * @return Un valor booleano
 * @post El cursor apunta al nodo buscado
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
 * @brief Algoritmo que ordena alfabeticamente los nodos al insertarlos
 * @param this La lista
 * @param code El codigo del producto
 * @param name El nombre del producto
 * @param quantity La cantidad de producto
 * @return Un valor booleano
 */
bool ord_insercion(INV* this, char* code, char* name, int quantity)
{
  Node* right = this->last;
  Node* left = this->first;
  if( strcmp(name, right->data.name) > 0 )
  {
    INV_InsertBack(this, code, name, quantity);
    return true;
  }

  if( strcmp(name, left->data.name) < 0 )
  {
    INV_InsertFront(this, code, name, quantity);
    return true;
  }

  if( strcmp(name, right->data.name) < 0 && strcmp(name, left->data.name) > 0 && INV_Len(this) == 2)
  {
    Node* n = newNode( code, name, quantity );
    if(n)
    {
      right->prev = n;
      left->next = n;
      n->next = right;
      n->prev = left;
      ++this->len;
      return true;
    }
  }

  if(INV_Len(this) > 2)
  {
    left = this->last->prev;
    for(size_t i = 0; i < INV_Len(this); ++i)
    {
      if( strcmp(name, right->data.name) < 0 && strcmp(name, left->data.name) > 0 )
      {
         Node* n = newNode( code, name, quantity );
         if( n )
         {
          left->next = n;
          right->prev = n;
          n->prev = left;
          n->next = right;
          ++this->len;
         }
        break;
      }
      left = left->prev;
      right = right->prev;
    }
    return true;
  }
}
