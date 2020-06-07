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
    
    printf("\n\n\t\t\t\t*\t*\t*\t*\t*\t*\t*\t*\t*\n\n");
    printf("\t\t\t\t*\t\tSistema de Inventario.\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t\tOpciones:\t\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t1. Agregar al inventario/Aumentar cantidad.\t\t*\n\n");
    printf("\t\t\t\t*\t2. Eliminar del inventario.\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t3. Reportes.\t\t\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t4. Mostrar todos los productos.\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t5. Salir.\t\t\t\t\t\t*\n\n");
    printf("\t\t\t\t*\t*\t*\t*\t*\t*\t*\t*\t*\n");

    scanf("%d", &answer);
    switch(answer){
      case 1:

        system("cls");
        printf("------------------------------------Inventario------------------------------------------\n\n");
	printf("Para agregar un producto nuevo escriba un codigo nuevo.\n");
	printf("Para aumentar la cantidad de un producto escriba un codigo existente.\n\n\n");
        printf("\t\t\t\t*\tInserte el codigo del producto: ");
        setbuf(stdin, NULL); //limpia el buffer
        gets(entrada.code);
        Stock_Toupper(entrada.code);
      
        if(!INV_Search(this, entrada.code)){
          
          printf("Codigo inexistente.\n");
          printf("\t\t\t*\tDesea agregarlo? (1/0)\n");
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
        printf("\n\tCodigo\t\t\t\tNombre\t\t\t\tCantidad\n");
        printf("----------------------------------------------------------------------------------------\n");
        Stock_PrintNode(this, entrada.code, entrada.name, &entrada.quantity);

        printf("\nInserte la cantidad a agregar del producto: ");
        scanf("%d", &entrada.quantity);
      
        Stock_Add(this, entrada.code, entrada.name, entrada.quantity);
        printf("Se agrego correctamente.\n");
        Stock_clear_screen();

        file = fopen("reportes.dat", "ab");

        fwrite(&entrada, sizeof(entrada), 1, file);

        fclose(file);
        break;
      case 2:
        
        system("cls");
        
        if(INV_IsEmpty(this)){
        
          printf("El inventario esta vacio\n");
          Stock_clear_screen();
          break;
        }

        printf("\n\t\t\t*\tInserte el codigo del producto:");
        setbuf(stdin, NULL);
        gets(entrada.code);
                
        if(INV_Search(this, entrada.code)){

          printf("\tCodigo\t\t\t\tNombre\t\t\t\tCantidad\n");
          printf("----------------------------------------------------------------------------------------\n");
          Stock_PrintNode(this, entrada.code, entrada.name, &entrada.quantity);

          printf("\nInserte la cantidad a retirar: ");
          scanf("%d", &entrada.quantity);

          if(!Stock_Out(this, entrada.code, entrada.quantity)){

            printf("No se pudo retirar porque no hay suficiente producto.\n");
            Stock_clear_screen();
            break;
          }
          
          printf("Se retiro exitosamente.\n");
          entrada.quantity = entrada.quantity*(-1);

          file = fopen("reportes.dat", "a+b");

          fwrite(&entrada, sizeof(entrada), 1, file);

          fclose(file);

          Stock_clear_screen();
          break;
        }
        printf("No se pudo retirar porque no existe el producto\n");
        Stock_clear_screen();
        break;
      case 3:
        system("cls");

        printf("Reporte de movimientos.\n\n");

        printf("\tCodigo\t\t\t\tNombre\t\t\t\tCantidad\n\n");
        printf("----------------------------------------------------------------------------------------\n");
        //printf("\n\t%s\t\t\t\t%s\t\t\t\t%d\n", code, nombre, cantidad);
        
        file = fopen("reportes.dat", "a+b");
        Product test;

        fread(&test,sizeof(test),1,file);
        while (!feof(file)){
          
          printf("\t%s\t\t\t\t%s\t\t\t\t%d\n", test.code, test.name, test.quantity);  

          fread(&test, sizeof(test), 1, file);
        }
        fclose(file);

        Stock_clear_screen();
        break;
      case 4:
        
        system("cls");
        printf("------------------------------------Inventario------------------------------------------\n\n");
        
        printf("Productos existentes:\n\n");

        printf("\tCodigo\t\t\t\tNombre\t\t\t\tCantidad\n");
        printf("----------------------------------------------------------------------------------------\n");

        if(INV_IsEmpty(this)){

          printf("El inventario esta vacio.\n\n");
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
