#pragma once
#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include "gestor.h"
#include "sonido.h"
#include "ventana.h"
using namespace sf;
using namespace std;

class Juego:public Sonido, public Ventana{
	private:
		RenderWindow ventana2;
	    View         view_gema;
	    View         view_pantalla;
	    Texture      txt_juego;
	    Sprite       spr_juego;
	    Font         fuente;
	    Text         text_puntaje;
	    Text         text_final;
	    Gestor       gestor_gema;
	public:
		// inicializador común para un miembro
		Juego() :fuente(), text_puntaje("PUNTOS: 000000", fuente, 20), text_final("Game Over!", fuente, 80)
	    {
		text_puntaje.setFillColor(Color::Black);
		text_final.setFillColor(Color::Black);
	    }
	    ~Juego() {}
	    void iniciar(int ancho,int alto,string titulo);
	    void cargar_graficos();
	    void dibujar();
	    void run();
	    
};
