#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<iostream>
using namespace sf;
using namespace std;
//En esta clase Sonido va a utilizar la HERENCIA para que solo se ejecuten los sonidos que queramos
class Sonido{
	public:
		SoundBuffer  bff_cam;
		Sound        sound_cam;
		SoundBuffer  bff_select;
		Sound        sound_select;
		SoundBuffer  bff_glow;
		Sound        sound_glow;
		virtual void cargar_sonido();
	Sonido() = default;
	~Sonido() = default;
};
