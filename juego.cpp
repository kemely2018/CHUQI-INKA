#include <iostream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "juego.h"
using namespace std;

void Juego::iniciar(int ancho,int alto,string titulo){
		ventana2.create(VideoMode(ancho,alto),titulo);
		ventana2.setFramerateLimit(60);
		cargar_graficos();
		// esto es solo para mantener la puntuación del texto en su lugar.
		view_pantalla.reset(FloatRect(0, 0,ancho, alto));
		view_pantalla.setViewport(FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
		double borde = (64.0f*8)+(4*7);
		view_gema.reset(FloatRect(0, 0, borde, borde));
		view_gema.setViewport(FloatRect(0.028125f, 0.05f, 0.50625f, 0.9f));
		ventana2.setView(view_gema);
		// Es importante ya que con esto vamos a cargar nuestro Sprite y la aleatoriedad(CLASE GESTOR)
		gestor_gema.iniciar();
}
	

void Juego::cargar_graficos(){
		if (!fuente.loadFromFile("fuentes/aaa.ttf")) {
		}
		txt_juego.loadFromFile("imagenes/juego.jpg");
		spr_juego.setTexture(txt_juego);
		Sonido::cargar_sonido();
}

void Juego::run()
	{
		while(ventana2.isOpen()) {
			Event e;
			while(ventana2.pollEvent(e)) {
				switch(e.type) {
					case Event::Closed:
						ventana2.close();
						break;
					case Event::KeyReleased:
						if (e.key.code == Keyboard::Escape) ventana2.close();
						if (e.key.code == Keyboard::W) gestor_gema.generar_premio();
						sound_glow.play();
						break;
					case Event::MouseButtonPressed:
						sound_cam.play();
						if (e.mouseButton.button == Mouse::Left) {
							gestor_gema.click(ventana2.mapPixelToCoords(Mouse::getPosition(ventana2)));
						}
						break;
					default:
						break;
				}
			}
	
			gestor_gema.update();
			dibujar();
	}
}



void Juego::dibujar()
	{
		ventana2.setView(view_pantalla);
		ventana2.draw(spr_juego);

        //setw() -> tabulado
		ostringstream string_puntaje;
		string_puntaje << "PUNTOS: " << setw(6) << setfill('0') <<gestor_gema.getScore();
		text_puntaje.setString(string_puntaje.str());
		text_puntaje.setPosition(ventana2.getSize().x-450,120);
		text_final.setPosition(ventana2.getSize().x / 2, ventana2.getSize().y / 2);
        text_puntaje.setCharacterSize(40);
		ventana2.draw(text_puntaje);

		if (gestor_gema.pierde()) {
			ventana2.draw(text_final);
		}

		ventana2.setView(view_gema);
		gestor_gema.draw(ventana2);
		
		ventana2.display();
}

