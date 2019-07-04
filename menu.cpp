#include<iostream>
#include"menu.h"
using namespace std;
using namespace sf;

void Menu::iniciar(int ancho,int alto,string titulo){
	ventana1.create(VideoMode(ancho,alto),titulo);
	ventana1.setFramerateLimit(60);
	cargar_graficos();	
}

void Menu::cargar_graficos(){
	if(!fuente.loadFromFile("fuentes/pixelart.ttf")){
		//Sale error
	}
	
	for(int i=0;i<NUMERO_DE_OPCIONES;i++){
		menu[i].setFont(fuente);
		menu[i].setCharacterSize(50);
	}
	menu[0].setFillColor(Color::Red);
	menu[1].setFillColor(Color::Black);
	menu[0].setPosition(120,600);
	menu[1].setPosition(840,600);
	menu[0].setString("[Jugar]");
	menu[1].setString("[Salir]");
	
    txt_fondo.loadFromFile("imagenes/portada.jpg");
	spr_fondo.setTexture(txt_fondo);
	
	Sonido::cargar_sonido();
	select_item=0;
}

void Menu::dibujar(){
	ventana1.draw(spr_fondo);
	for(int i=0;i<NUMERO_DE_OPCIONES;i++){
		ventana1.draw(menu[i]);
	}
	ventana1.display();
}

void Menu::run(){
while(ventana1.isOpen()){
	while(ventana1.pollEvent(evento1)){
		switch(evento1.type){
			case Event::Closed:
				ventana1.close();
				exit(1);
			break;
			case Event::KeyReleased:
				switch(evento1.key.code){
					case Keyboard::Left:
						sound_cam.play();
						if(select_item -1>=0){
		                menu[select_item].setFillColor(Color::Black);
		                select_item--;
		                menu[select_item].setFillColor(Color::Red);
	                }
					break;
					case Keyboard::Right:
						sound_cam.play();
						if(select_item +1<NUMERO_DE_OPCIONES){
		                menu[select_item].setFillColor(Color::Black);
		                select_item++;
		                menu[select_item].setFillColor(Color::Red);
	                }
					break;
					case Keyboard::Return:
						sound_select.play();
						switch(select_item){
						case 0:
						   ventana1.close();
						   juego.iniciar(1200,800,"JUEGO");
						   juego.run();
						   break;
						case 1:
						   ventana1.close();
						   break;
					break;	
				    }
			    break;
		    } 
	    }
     }
    dibujar();
   }
}






