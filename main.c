//Comando de compilación
// gcc -Wall -std=c99 -o main main.c INV.c Stock.c

#include "Stock.h"

int main(){

	INV* inv = INV_New();

	Stock_ReadArchive(inv);

	system("clear");

	Stock_Menu(inv);

	INV_Delete(&inv);
}
