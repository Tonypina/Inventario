
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

        system("cls");
        printf("Inserte el codigo del producto: ");
        setbuf(stdin, NULL); //limpia el buffer
        gets(code);
      
        if(!INV_Search(this, code)){
          
          printf("Codigo inexistente.\n");
          printf("Desea agregarlo? (1/0)\n");
          int resp;
          scanf("%d", &resp);
          
          if (resp == 1){
              
            printf("\nInserte el nombre del producto: ");
            setbuf(stdin, NULL);
            gets(nombre);
        
            printf("\nInserte la cantidad de producto: ");
            scanf("%d", &cantidad);
        
            Stock_Add(this, code, nombre, cantidad);
            printf("Agregado con exito.\n");

            system("PAUSE");
            system("cls");
            break;
          }
          printf("No se agrego el producto\n");
          break;
        }
        Stock_PrintNode(this, name);

        printf("\nInserte la cantidad de producto: ");
        scanf("%d", &cantidad);
      
        Stock_Add(this, code, nombre, cantidad);
        break;
      case 2:
        
        system("cls");
        
        if(INV_IsEmpty(this)){
        
          printf("El inventario esta vacio\n");
          Stock_clear_screen();
          break;
        }

        printf("Inserte el codigo del producto:");
        setbuf(stdin, NULL);
        gets(code);
        
        printf("\nInserte la cantidad que sale:");
        scanf("%d", &cantidad);
        
        if(!Stock_Out(this, code, cantidad)){
          
          printf("No se pudo sacar el artículo porque no existe o sus existencias son cero.\n");
          break;
        }

        printf("Se logró retirar con éxito.\n");
        break;
      case 3:
        
        break;
      case 4:
        
        system("cls");
        printf("----- Inventario -----\n\n");
        
        if(INV_IsEmpty(this)){

          printf("El inventario esta vacio.\n\n");
          Stock_clear_screen();
          break;
        }
        printf("Productos existentes:\n\n");
        
        INV_CursorFirst(this);

        for(size_t i = 0; i < INV_Len(this); ++i){

          Stock_PrintNode(this, name);
          INV_CursorNext(this);
        }
        
        printf("Actualmente hay %d productos en el inventario.\n\n", INV_Len(this));
        Stock_clear_screen();
        break;
      case 5:
        printf("---SALISTE---\n\n");

        Stock_clear_screen();
        break;
      default:
        
        printf("Ingresa una opcion valida.\n\n");
        Stock_clear_screen();     
    }
  } while (answer != 5);
}