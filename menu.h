#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<iostream>
#include"juego.h"
#include"sonido.h"
#include"ventana.h"
using namespace sf;
using namespace std;
#define NUMERO_DE_OPCIONES 2
class Menu:public Sonido, public Ventana{
	private:
		RenderWindow ventana1;        
		Font         fuente;
		Text         menu[NUMERO_DE_OPCIONES];
		Event        evento1;
		Texture      txt_fondo;
		Sprite       spr_fondo;
		int          select_item;
		Juego        juego;	
	public:
		Menu() {}
		~Menu() {}
		void iniciar(int ancho,int alto,string titulo);
		void cargar_graficos();
		void dibujar();
		void run();		
};
