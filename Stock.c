#include "Stock.h"

/**
 * @brief Convierte todas las letras de un arreglo a mayusculas
 * @param array El arreglo a modificar
 */
void Stock_Toupper(char* array){
  for(size_t i = 0; array[i] != '\0'; ++i){
    array[i] = toupper(array[i]);
  }
}

/**
 * @brief Pausa y limpia la pantalla
 */
void Stock_clear_screen(){
  system("PAUSE");
  system("cls");
}

/**
 * @brief Imprime en pantalla los datos dentro de un nodo
 * @param this La lista
 * @param code El codigo del producto
 * @param name El nombre del producto
 * @param quantity La cantidad de producto
 */
void Stock_PrintNode(INV* this, char* code, char* name, int* quantity){
  INV_Peek(this, code, name, quantity);
  printf("\t%s\t\t\t\t%s\t\t\t\t%d\n", code, name, *quantity);
}

/**
 * @brief Reduce el elemento cantidad de un producto
 * @param this La lista
 * @param code El codigo del producto a reducir su cantidad
 * @param quantity La cantidad a reducir del producto
 * @return Un valor booleano
 */
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

/**
 * @brief Agrega un producto al inventario
 * @param this La lista
 * @param code El codigo del producto
 * @param name El nombre del producto
 * @param quantity La cantidad de producto
 * @return Un valor booleano
 */
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

/**
 * @brief Guarda en un archivo los datos del inventario
 * @this La lista
 */
void Stock_Archive(INV* this){

  FILE* file;
  file = fopen("inventario.dat", "ab");

  for (Node* it = this->first; it != NULL; it = it->next){
    
    fwrite(&it->data, sizeof(it->data), 1, file);
  }
  fclose(file);
}

/**
 * @brief Lee los datos del archivo al reabrir el programa
 * @param this La lista
 */
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

/**
 * @brief El menu del programa
 * @param this La lista
 */
void Stock_Menu(INV* this){
  
  int answer = 0;

  FILE* file;
  Product entrada;

  /*
  char code[TAM_CODE];
  char nombre[TAM_NAME];
  int cantidad = 0;
  */

  do {
    
    printf("\n\n\t\t\t\t*\t*\t*\t*\t*\t*\t*\n\n");
    printf("\t\t\t\t*\t\tSistema de Inventario.\t\t*\n\n");
    printf("\t\t\t\t*\t\tOpciones:\t\t\t*\n\n");
    printf("\t\t\t\t*\t1. Agregar al inventario.\t\t*\n\n");
    printf("\t\t\t\t*\t2. Eliminar del inventario.\t\t*\n\n");
    printf("\t\t\t\t*\t3. Buscar un producto.\t\t\t*\n\n");
    printf("\t\t\t\t*\t4. Reportes.\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t5. Mostrar todos los productos.\t\t*\n\n");
    printf("\t\t\t\t*\t6. Salir.\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t*\t*\t*\t*\t*\t*\n");

    scanf("%d", &answer);
    switch(answer){
      case 1:

        system("cls");
        printf("\n-------------------------------AGREGAR AL INVENTARIO------------------------------------\n\n");
        printf("\t\t\t*  Inserte el codigo del producto: ");
        setbuf(stdin, NULL); //limpia el buffer
        gets(entrada.code);
        Stock_Toupper(entrada.code);
      
        if(!INV_Search(this, entrada.code)){
          
          printf("\t\t\t Codigo inexistente.\n");
          printf("\t\t\t*  Desea agregarlo? (1/0)\n");
          int resp;
          scanf("%d", &resp);
          
          if (resp == 1){
              
            printf("\nInserte el nombre del producto: ");
            setbuf(stdin, NULL);
            gets(entrada.name);
            Stock_Toupper(entrada.name);
        
            printf("\nInserte la cantidad de producto: ");
            scanf("%d", &entrada.quantity);
        
            Stock_Add(this, entrada.code, entrada.name, entrada.quantity);
            printf("Agregado con exito.\n");

            file = fopen("reportes.dat", "ab");

            fwrite(&entrada, sizeof(entrada), 1, file);

            fclose(file);

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
        Stock_PrintNode(this, entrada.code, entrada.name, &entrada.quantity);

        printf("\nInserte la cantidad de producto: ");
        scanf("%d", &entrada.quantity);
      
        Stock_Add(this, entrada.code, entrada.name, entrada.quantity);
        printf("Se agregó correctamente.\n");
        Stock_clear_screen();

        file = fopen("reportes.dat", "ab");

        fwrite(&entrada, sizeof(entrada), 1, file);

        fclose(file);
        break;
      case 2:
        
        system("cls");
      
        printf("\n------------------------------ELIMINAR DEL INVENTARIO-----------------------------------\n\n");

        if(INV_IsEmpty(this)){
        
          printf("\nEl inventario esta vacio\n");
          Stock_clear_screen();
          break;
        }

        printf("\t\t\t*  Inserte el codigo del producto: ");
        setbuf(stdin, NULL);
        gets(entrada.code);
        Stock_Toupper(entrada.code);
                
        if(INV_Search(this, entrada.code)){

          printf("\n\tCódigo\t\t\t\tNombre\t\t\t\tCantidad\n");
          printf("----------------------------------------------------------------------------------------\n");
          Stock_PrintNode(this, entrada.code, entrada.name, &entrada.quantity);

          printf("\nInserte la cantidad a retirar: ");
          scanf("%d", &entrada.quantity);

          if(!Stock_Out(this, entrada.code, entrada.quantity)){

            printf("\nNo se pudo retirar porque no hay suficiente producto.\n");
            Stock_clear_screen();
            break;
          }
          
          printf("\nSe retiró exitosamente.\n");
          entrada.quantity = entrada.quantity*(-1);

          file = fopen("reportes.dat", "a+b");

          fwrite(&entrada, sizeof(entrada), 1, file);

          fclose(file);

          Stock_clear_screen();
          break;
        }
        printf("\nNo se pudo retirar porque no existe el producto\n");
        Stock_clear_screen();
        break;
      
      case 3:
        system("cls");

        printf("\n------------------------------------MOSTRAR PRODUCTO------------------------------------\n\n");        
        printf("\t\t\t*  Inserte el codigo del producto: ");
        setbuf(stdin, NULL);
        gets(entrada.code);
        Stock_Toupper(entrada.code);

        if(INV_Search(this, entrada.code)){

          printf("\n\tCódigo\t\t\t\tNombre\t\t\t\tCantidad\n\n");
          printf("----------------------------------------------------------------------------------------\n");
          Stock_PrintNode(this, entrada.code, entrada.name, &entrada.quantity);
          printf("\n");
          Stock_clear_screen();
          break;
        }
        printf("\nNo existe el producto.\n");
        Stock_clear_screen();
        break;

      case 4:
        system("cls");

        printf("\n------------------------------REPORTE DE MOVIMIENTOS------------------------------------\n\n");

        printf("\tCódigo\t\t\t\tNombre\t\t\t\tCantidad\n\n");
        printf("----------------------------------------------------------------------------------------\n");
        
        file = fopen("reportes.dat", "a+b");
        Product test;

        fread(&test,sizeof(test),1,file);
        while (!feof(file)){
          
          printf("\t%s\t\t\t\t%s\t\t\t\t%d\n", test.code, test.name, test.quantity);  

          fread(&test, sizeof(test), 1, file);
        }
        fclose(file);
        printf("\n");
        Stock_clear_screen();
        break;
      case 5:
        
        system("cls");
        printf("------------------------------------INVENTARIO------------------------------------------\n\n");
        
        printf("Productos existentes:\n\n");

        printf("\tCódigo\t\t\t\tNombre\t\t\t\tCantidad\n");
        printf("----------------------------------------------------------------------------------------\n");

        if(INV_IsEmpty(this)){

          printf("\nEl inventario esta vacio.\n\n");
          Stock_clear_screen();
          break;
        }
        INV_CursorFirst(this);

        for(size_t i = 0; i < INV_Len(this); ++i){

          Stock_PrintNode(this, entrada.code, entrada.name, &entrada.quantity);
          INV_CursorNext(this);
        }
        
        printf("\nActualmente hay %d productos en el inventario.\n\n", INV_Len(this));
        Stock_clear_screen();
        break;
      case 6:
        Stock_Archive(this);

        printf("-----------------------------------------SALISTE-------------------------------------\n\n");

        Stock_clear_screen();
        break;
      default:
        
        printf("\nIngresa una opcion valida.\n\n");
        Stock_clear_screen();     
    }
  } while (answer != 6);
}
