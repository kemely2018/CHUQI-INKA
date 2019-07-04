#include <iostream>
#include <SFML/Graphics.hpp>
#include "gema.h"
using namespace std;
using namespace sf;
const Vector2f Gema::size {(float)gemSize, (float)gemSize};

Gema::Gema(int col, int fila, Color color, Texture& txt_gema, Estado estado)
	: col(col), fila(fila), pos(float((Gema::size.x+padding)*col), float((Gema::size.y+padding)*fila)),
	color(color), estado(estado), spr_gema(txt_gema)
{
	objetivo = pos;
	// sub-rectángulo de la textura que mostrará el sprite ,construye el rectángulo a partir de sus coordenadas.
	spr_gema.setTextureRect(IntRect(static_cast<int>(color)*gemSize, 0, gemSize, gemSize));
	spr_gema.setColor(sf::Color(255, 255, 255, alpha));
	//obtener la posición del objeto
	spr_gema.setPosition(pos);
}

void Gema::dibujar(RenderWindow& window)
{
	if (estado != Gema::Estado::NUEVO) {
		spr_gema.setPosition(pos);
		//El sprite generara un rectangulo de acuerdo al valor del Color y el gemSize definido(64)
        spr_gema.setTextureRect(IntRect(static_cast<int>(color)*gemSize, (estado==Estado::SELECCIONAR)?gemSize:0, gemSize, gemSize));
        //Cuando se eliminan las gemas disminuyen su opacidad lo cual representa el alpha para generar un Efecto de DESVANECER
        spr_gema.setColor(sf::Color(255, 255, 255, alpha));
		window.draw(spr_gema);
	}
}

bool Gema::comprobar(const Vector2f& spos)
{
	if (estado==Estado::ELIMINAR) return false;
	//Compruebe si un punto está dentro del área del rectángulo.
	//Si el punto se encuentra en el borde del rectángulo, esta función devolverá el valor falso.
	return Rect<float>(pos, size).contains(spos);
}

void Gema::intercambiar_obj(Gema& otra)
{
	//Intercambia los contenidos de este buffer de vértice con los de otro.
	swap(col, otra.col);
	swap(fila, otra.fila);
	//Ya que el objetivo==posicion ( tambien se modifican las posiciones )
	objetivo = Vector2f(float((Gema::size.x+padding)*col), float((Gema::size.y+padding)*fila));
	otra.objetivo = Vector2f(float((Gema::size.x+padding)*otra.col), float((Gema::size.y+padding)*otra.fila));
	//El estado de las dos gemas se vuelve a MOVER
	setEstado(Estado::MOVER);
	otra.setEstado(Estado::MOVER);
}

Gema::Estado Gema::actualizar()
{
	switch(estado)
	{
		case Estado::IGUAL:
		{
			setEstado(Estado::BORRAR);
			break;
		}
		case Estado::BORRAR:
		{
			//disminuye la opacidad(alpha)
			alpha -= 10;
			if (alpha <= 50) {
				setEstado(Estado::ELIMINAR);
			}
			break;
		}
		/*https://www.youtube.com/watch?v=oQqnJTAmfPE*/
		case Estado::MOVER:
		case Estado::ELIMINAR:
		{
			auto move = [=](float& p, float t) -> bool
			{
				// mostrar la apariencia del movimiento
				if (p == t) return false;
				if (p < t) p += min(5.0f, t-p);
				else       p -= min(5.0f, p-t);
				return true;
			};
			if (!move(pos.x,objetivo.x) && !move(pos.y, objetivo.y) && estado == Estado::MOVER)
				setEstado(Estado::NINGUNO);
			break;
		}
		default:
			break;
	}
	return estado;
}

void Gema::setEstado(Estado estado)
{
	if (this->estado != Estado::ELIMINAR) this->estado = estado;
}
