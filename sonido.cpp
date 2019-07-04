#include <iostream>
#include <SFML/Graphics.hpp>
#include "sonido.h"
using namespace std;
using namespace sf;
void Sonido::cargar_sonido(){
	bff_cam.loadFromFile("sonido/cambio.wav");
	sound_cam.setBuffer(bff_cam);
	bff_select.loadFromFile("sonido/select.wav");
	sound_select.setBuffer(bff_select);
	bff_glow.loadFromFile("sonido/glow.wav");
	sound_glow.setBuffer(bff_glow);
}
