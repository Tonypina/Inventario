#include "INV.h"

void Archivo(INV* this){

	FILE* file;
	file = fopen("inventario.txt", "ab");

	for (Node* it = this->first; it != NULL; it = it->next){
		
		fwrite(&it->data, sizeof(it->data), 1, file);
	}
	fclose(file);
}

void Menu(INV* this){
	
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
		printf("4. Salir.\n");

		scanf("%d", &answer);
		switch(answer){
			case 1:
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
				
						INV_Add(this, code, nombre, cantidad);
						break;
    					}
    					break;
  				}
  				INV_PrintNode(this, name);

  				printf("\nInserte la cantidad de producto: ");
				scanf("%d", &cantidad);
				
				INV_Add(this, code, nombre, cantidad);
				break;
				
			case 2:
				printf("Inserte el codigo del producto:");
				setbuf(stdin, NULL);
				gets(code);
				
				printf("\nInserte la cantidad que sale:");
				scanf("%d", &cantidad);
				
				INV_Out(this, code, cantidad);
				break;

			case 3:
				
				system("cls");
				break;
			case 4:
				printf("---SALISTE---\n");

				system("PAUSE");
				break;
			default:
				
				printf("Ingresa una opcion valida.\n");
				system("PAUSE");
				system("cls");
			
		}
	} while (answer != 4);
}


int main()
{	
	INV* inv = INV_New();
	Menu(inv);
	INV_Delete(&inv);
}