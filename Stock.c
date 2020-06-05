#include "Stock.h"

void Stock_Toupper(char* array){
  for(size_t i = 0; array[i] != '\0'; ++i){
    array[i] = toupper(array[i]);
  }
}

void Stock_clear_screen(){
  system("PAUSE");
  system("cls");
}

void Stock_PrintNode(INV* this, char* code, char* name, int* quantity){
  INV_Peek(this, code, name, quantity);
  printf("\t%s\t\t\t\t%s\t\t\t\t%d\n", code, name, *quantity);
}

bool Stock_Out(INV* this, char* code, int quantity ){

  if(INV_Search(this, code)){
    if(this->cursor->data.quantity > 0){
      if(this->cursor->data.quantity >= quantity){
        this->cursor->data.quantity -= quantity;
        return true;
      }
      return false;
    }
    return false;
  }
  return false;
}

bool Stock_Add(INV* this, char* code, char* name, int quantity ){

  if(INV_Search(this, code))
  {
    this->cursor->data.quantity += quantity;
    return true;
  }

  if (INV_Len(this) == 0)
  {
    INV_InsertBack(this, code, name, quantity);
  }
  else
  {
    ord_insercion(this, code, name, quantity);
    //algoritmo de ordenamiento
  }
  
  return true;
}

void Stock_Archive(INV* this){

  FILE* file;
  file = fopen("inventario.dat", "ab");

  for (Node* it = this->first; it != NULL; it = it->next){
    
    fwrite(&it->data, sizeof(it->data), 1, file);
  }
  fclose(file);
}

void Stock_ReadArchive(INV* this){

  FILE* file = fopen("inventario.dat", "a+b");
  Product test;

  fread(&test,sizeof(test),1,file);
  while (!feof(file)){
    
    if(!INV_Len(this)){
      INV_InsertBack(this, test.code, test.name, test.quantity);
    } else {
      ord_insercion(this, test.code, test.name, test.quantity);
    }
    
    fread(&test, sizeof(test), 1, file);
  }
  fclose(file);
  remove("inventario.dat");
}

void Stock_Menu(INV* this){
  
  int answer = 0;
  char code[TAM_CODE];
  char nombre[TAM_NAME];
  int cantidad = 0;
  do {
    
    printf("\n\n\t\t\t\t*\t*\t*\t*\t*\t*\t*\n\n");
    printf("\t\t\t\t*\t\tSistema de Inventario.\t\t*\n\n");
    printf("\t\t\t\t*\t\tOpciones:\t\t\t*\n\n");
    printf("\t\t\t\t*\t1. Agregar al inventario.\t\t*\n\n");
    printf("\t\t\t\t*\t2. Eliminar del inventario.\t\t*\n\n");
    printf("\t\t\t\t*\t3. Reportes.\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t4. Mostrar todos los productos.\t\t*\n\n");
    printf("\t\t\t\t*\t5. Salir.\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t*\t*\t*\t*\t*\t*\n");

    scanf("%d", &answer);
    switch(answer){
      case 1:

        system("cls");
        printf("------------------------------------Inventario------------------------------------------\n\n");
        printf("\t\t\t\t*\tInserte el codigo del producto: ");
        setbuf(stdin, NULL); //limpia el buffer
        gets(code);
        Stock_Toupper(code);
      
        if(!INV_Search(this, code)){
          
          printf("Codigo inexistente.\n");
          printf("\t\t\t*\tDesea agregarlo? (1/0)\n");
          int resp;
          scanf("%d", &resp);
          
          if (resp == 1){
              
            printf("\nInserte el nombre del producto: ");
            setbuf(stdin, NULL);
            gets(nombre);
            Stock_Toupper(nombre);
        
            printf("\nInserte la cantidad de producto: ");
            scanf("%d", &cantidad);
        
            Stock_Add(this, code, nombre, cantidad);
            printf("Agregado con exito.\n");

            system("PAUSE");
            system("cls");
            break;
          }
          printf("No se agrego el producto\n");
          Stock_clear_screen();
          break;
        }
        printf("\n\tCódigo\t\t\t\tNombre\t\t\t\tCantidad\n");
        printf("----------------------------------------------------------------------------------------\n");
        Stock_PrintNode(this, code, nombre, &cantidad);

        printf("\nInserte la cantidad de producto: ");
        scanf("%d", &cantidad);
      
        Stock_Add(this, code, nombre, cantidad);
        printf("Se agregó correctamente.\n");
        Stock_clear_screen();
        break;
      case 2:
        
        system("cls");
        
        if(INV_IsEmpty(this)){
        
          printf("El inventario esta vacio\n");
          Stock_clear_screen();
          break;
        }

        printf("\t\t\t\tInserte el codigo del producto:");
        setbuf(stdin, NULL);
        gets(code);
                
        if(INV_Search(this, code)){

          printf("\tCódigo\t\t\t\tNombre\t\t\t\tCantidad\n");
          printf("----------------------------------------------------------------------------------------\n");
          Stock_PrintNode(this, code, nombre, &cantidad);

          printf("\nInserte la cantidad a retirar.\n");
          scanf("%d", &cantidad);

          if(!Stock_Out(this, code, cantidad)){

            printf("No se pudo retirar porque no hay suficiente producto.\n");
            Stock_clear_screen();
            break;
          }
          
          printf("Se retiró exitosamente.\n");
          cantidad = cantidad*(-1);
          Stock_clear_screen();
          break;
        }
        printf("No se pudo retirar porque no existe el producto\n");
        Stock_clear_screen();
        break;
      case 3:
        system("cls");

        printf("Ultimo movimiento realizado.\n\n");

        printf("\tCódigo\t\t\t\tNombre\t\t\t\tCantidad\n");
        printf("----------------------------------------------------------------------------------------\n");
        printf("\n\t%s\t\t\t\t%s\t\t\t\t%d\n", code, nombre, cantidad);
        Stock_clear_screen();
        break;
      case 4:
        
        system("cls");
        printf("------------------------------------Inventario------------------------------------------\n\n");
        
        printf("Productos existentes:\n\n");

        printf("\tCódigo\t\t\t\tNombre\t\t\t\tCantidad\n");
        printf("----------------------------------------------------------------------------------------\n");

        if(INV_IsEmpty(this)){

          printf("El inventario esta vacio.\n\n");
          Stock_clear_screen();
          break;
        }
        
        INV_CursorFirst(this);

        for(size_t i = 0; i < INV_Len(this); ++i){

          Stock_PrintNode(this, code, nombre, &cantidad);
          INV_CursorNext(this);
        }
        
        printf("\nActualmente hay %d productos en el inventario.\n\n", INV_Len(this));
        Stock_clear_screen();
        break;
      case 5:
        Stock_Archive(this);

        printf("-----------------------------------------SALISTE-------------------------------------\n\n");

        Stock_clear_screen();
        break;
      default:
        
        printf("Ingresa una opcion valida.\n\n");
        Stock_clear_screen();     
    }
  } while (answer != 5);
}
