//Comando de compilación
// gcc -Wall -std=c99 -o main main.c INV.c Stock.c Menu.c

#include "Stock.h"

int main()
{	
	INV* inv = INV_New();
	
	system("cls");
	
	Stock_Menu(inv);
	
	INV_Delete(&inv);
}
