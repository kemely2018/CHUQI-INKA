#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

//clase abstracta para hacer uso del polimorfismo para la clase MENU Y JUEGO que generan las ventanas
class Ventana{
	public:
	    virtual void iniciar(int ancho,int alto,string titulo)=0;
		virtual void cargar_graficos()=0;
		virtual void dibujar()=0;
		virtual void run()=0;
	
};
