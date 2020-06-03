
#include "Stock.h"

void Stock_clear_screen(){
  system("PAUSE");
  system("cls");
}

void Stock_PrintNode(INV* this, char* name){
  INV_Peek(this, name);
  printf("%s\n", name);
}

bool Stock_Out(INV* this, char* code, int quantity ){

  if(INV_Search(this, code)){
    if(this->cursor->data.quantity > 0){
      this->cursor->data.quantity -= quantity;
      return true;
    }
    return false;
  }
  return false;
}

bool Stock_Add(INV* this, char* code, char* name, int quantity ){

  if(INV_Search(this, code)){
    this->cursor->data.quantity += quantity;
    return true;
  }

  INV_InsertBack(this, code, name, quantity);
  return true;
}

void Stock_Archive(INV* this){

  FILE* file;
  file = fopen("inventario.txt", "ab");

  for (Node* it = this->first; it != NULL; it = it->next){
    
    fwrite(&it->data, sizeof(it->data), 1, file);
  }
  fclose(file);
}

void Stock_Menu(INV* this){
  
  int answer = 0;
  char code[TAM_CODE];
  char nombre[TAM_NAME];
  int cantidad;
  char name[TAM_NAME];
  do {
    printf("--- Sistema de Inventario. ---\n\n");
    printf("Opciones:\n\n");
    printf("1. Agregar al inventario.\n");
    printf("2. Eliminar del inventario.\n");
    printf("3. Reportes.\n");
    printf("4. Mostrar todos los productos.\n");
    printf("5. Salir.\n");

    scanf("%d", &answer);
    switch(answer){
      case 1:
        Menu_Case1(this, code, nombre, cantidad, name);  
        break;
      case 2:
        Menu_Case2(this, code, nombre, cantidad);
        break;

      case 3:
        Menu_Case3(this, code, nombre, cantidad);
        break;

      case 4:
        Menu_Case4(this, code, cantidad, name);
        break;

      case 5:
        Menu_Case5();
        break;
      default:
        
        printf("Ingresa una opcion valida.\n\n");
        Stock_clear_screen();     
    }
  } while (answer != 5);
}