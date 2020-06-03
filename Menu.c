#include "Menu.h"

void Menu_Case1(INV* this, char* code, char* nombre, int cantidad, char* name){

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
}

void Menu_Case2(INV* this, char* code, char* nommbre, int cantidad){

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
}

void Menu_Case3(INV* this, char* code, char* nommbre, int cantidad){

}

void Menu_Case4( INV* this, char* code, int cantidad, char* name ){

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
}

void Menu_Case5(){

    printf("---SALISTE---\n\n");

    Stock_clear_screen();
}