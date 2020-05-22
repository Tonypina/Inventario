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
	printf("Sistema de Inventario.\n\n");
	printf("Opciones:\n\n");
	printf("1. Agregar al inventario.\n");
	printf("2. Eliminar del inventario.\n");
	printf("3. Reportes.\n");
	printf("4. Salir.\n");

	int answer = 0;
	char code[TAM_CODE];
	char nombre[TAM_NOMBRE];
	int cantidad;
	do {
		printf("Seleccione una opción:\n");
		scanf("%d", answer);
		switch(answer){
			case '1':
				printf("Inserte el codigo del producto: ");
				gets(code);
				printf("\nInserte el nombre del producto: ");
				gets(nombre);
				printf("\nInserte la cantidad de producto: ");
				scanf("%d", &cantidad);
				INV_Add(this, code, nombre, cantidad);
				break;
			case '2':
				printf("Inserte el codigo del producto:");
				gets(code);
				printf("\nInserte la cantidad que sale:");
				scanf("%d", &cantidad);
				INV_Out(this, code, cantidad);
				break;
			case '3':

			case '4':

				break;
			default:
			
		}
	} while (answer != 4);
}


int main(){

	INV inv = INV_New();
	Menu(inv);
	INV_Delete(&inv);
}