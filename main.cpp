#include <iostream>
#include <SFML/Graphics.hpp>
#include "menu.h"
using namespace std;
int main()
{
	//Creamos un objeto de clase MENU que nos dara una ventana
	Menu partida;
	//Le damos los valores
	partida.iniciar(1200,800,"CHUQI INKA");
	partida.run();
	return 0;
}
