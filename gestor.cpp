#include <iostream>
#include <sstream>
#include <algorithm>
#include "gestor.h"
using namespace std;
using namespace sf;

bool Gestor::iniciar(){
	cargar_graficos();
	srand(time(0));
	reiniciar();
	return true;
}

void Gestor::cargar_graficos(){
	texture.loadFromFile("imagenes/gemas.png");
}

// VAMOS A tener un vector de objetos de la class GEMA llamado ---> vector<Gema> gems;
void Gestor::reiniciar(){    
	gems.clear();//elimina todos los elementos del vector
	for (int r = 0; r < filas; ++r) {
		for (int c = 0; c < cols; ++c) {
			//EL ESTADO DE todas las gemas es NINGUNO (0)
			/*Se utiliza para insertar un nuevo elemento en el contenedor de vectores, el nuevo elemento se agrega al final del vector C++11
			 emplace_back a diferencia de push_back permite construir sobre la marcha, por lo tanto, solo se llama constructor, no hay movimiento.
			esta funcion pertenece al la libreria <algorithm> como ven inserta los valores en orden deacuerso a nuestro constuctor de la clase 
			Gema(int col, int fila, Color color, Texture& txt_gema, Estado estado)*/
			gems.emplace_back(c, r, static_cast<Gema::Color>(rand()%7), texture, Gema::Estado::NINGUNO);
		}
	}
	score = 0;
	cantidad_premio = 0;
	//el ESTATE DE todas las gemas es WAITING (0)
	setState(State::WAITING);
}

void Gestor::draw(RenderWindow& window)
{
	// vamos a dibujar las gemas 
	for (auto& g : gems) {
		// Vamos a la clase Gema::dibujar
		g.dibujar(window);
	}
}

void Gestor::click(const Vector2f& spos)
{
	if (state != State::WAITING && state != State::SELECTED) return;
	for (auto& gem : gems) {
		// bool Gema::comprobar(const Vector2f& spos)
		if (gem.comprobar(spos)) {
			if (gem.getColor() == Gema::Color::PREMIO) {
				// premio explota
				return explotar(&gem);
			}
			if (state == State::SELECTED) {
				sel2 = gem.getFila() * cols + gem.getCol();
				auto& other = gems[sel1];
				if ((abs(gem.getCol()-other.getCol()) + abs(gem.getFila()-other.getFila())) != 1) break;
				iter_swap(&gem, &other); 
				other.intercambiar_obj(gem);
				setState(State::SWAPPING);
			} else {
				sel1 = gem.getFila() * cols + gem.getCol();
				gem.setEstado(Gema::Estado::SELECCIONAR);
				setState(State::SELECTED);
			}
			break;
		}
	}
}

void Gestor::update()
{
	if (state == State::WAITING) {
		for (auto& gem : gems) {
			if (gem.getEstado() == Gema::Estado::NUEVO) gem.setEstado(Gema::Estado::NINGUNO);
		}

		int m = match();
		if (m > 0) {
			setState(State::MOVING);
			score += m;
		} else if (organizar()) {
			setState(State::MOVING);
		} 

	}
	if (state == State::MOVING || state == State::SWAPPING) {
		bool moving = false;
		for (auto& gem : gems) {
			Gema::Estado estado = gem.actualizar();
			if (estado == Gema::Estado::MOVER || estado == Gema::Estado::BORRAR) moving = true;
		}
		if (!moving) {
			if (state == State::SWAPPING) {
				int m = match();
				score += m;
				if (m == 0) {
					auto& gem = gems[sel1];
					auto& otra = gems[sel2];
					iter_swap(&gem, &otra);
					otra.intercambiar_obj(gem);
				}
				setState(State::MOVING);
			} else {
				setState(State::WAITING);
			}
		}
	}

	if (state == State::LOSING) {
		for (auto& gem : gems) {
			gem.setEstado(Gema::Estado::BORRAR);
			gem.actualizar();
			
		}
	}
}

int Gestor::match()
{
	int match = 0;
	auto gem = gems.begin();
	for (int r = 0; r < filas; ++r) {
		for (int c = 0; c < cols; ++c, ++gem) {
			if (c > 0 && c < (cols-1)) {
				match += match3(&*gem , &*(gem+1), &*(gem-1));
			}
			if (r > 0 && r < filas-1) {
				match += match3(&*gem , &*(gem+cols), &*(gem-cols));
			}
		}
	}
	return match;
}

int Gestor::match3(Gema* gem1, Gema* gem2, Gema* gem3)
{
	if (gem1->getEstado() != Gema::Estado::NINGUNO && gem1->getEstado() != Gema::Estado::IGUAL
			&& gem2->getEstado() != Gema::Estado::NINGUNO && gem2->getEstado() != Gema::Estado::IGUAL
			&& gem3->getEstado() != Gema::Estado::NINGUNO && gem3->getEstado() != Gema::Estado::IGUAL) {
		return 0;
	}
	int match = 0;
	if (gem1->getColor() == gem2->getColor() && gem1->getColor() == gem3->getColor()) {
		if (gem1->getEstado() != Gema::Estado::IGUAL) {
			++match;
			gem1->setEstado(Gema::Estado::IGUAL);
		}
		if (gem2->getEstado() != Gema::Estado::IGUAL) {
			++match;
			gem2->setEstado(Gema::Estado::IGUAL);
		}
		if (gem3->getEstado() != Gema::Estado::IGUAL) {
			++match;
			gem3->setEstado(Gema::Estado::IGUAL);
		}
	}
	return match;
}

bool Gestor::organizar()
{
	bool organizado = false;
	//ITERATOR
	//devuelve un iterador inverso que apunta al último elemento del vector
	for(auto gem = gems.rbegin(); gem != gems.rend(); ++gem) {
		if (gem->getEstado() != Gema::Estado::ELIMINAR) continue;
		if (gem->getFila() == 0) break;
		organizado = true;
		for (int fila = 1; fila <= gem->getFila(); ++fila) {
			if ((gem+(cols*fila))->getEstado() != Gema::Estado::ELIMINAR) {
				iter_swap(gem, (gem+(cols*fila)));
				gem->intercambiar_obj(*(gem+(cols*fila)));
				break;
			}
		}
	}
	reemplazar_eliminado();
	return organizado;
}

void Gestor::reemplazar_eliminado()
{
	for(auto gem = gems.begin(); gem != gems.end(); ++gem) {
		if (gem->getEstado() == Gema::Estado::ELIMINAR) {
			*gem = Gema(gem->getCol(), gem->getFila(), static_cast<Gema::Color>(rand()%7), texture, Gema::Estado::NUEVO);
		}
	}
}

void Gestor::setState(State newState)
{
	state = newState;
}

void Gestor::explotar(Gema* gem)
{
	for(int r = gem->getFila()-1; r < gem->getFila()+2; ++r) {
		for(int c = gem->getCol()-1; c < gem->getCol()+2; ++c) {
			if (c >= 0 && c < cols && r >=0 && r < filas) {
				gems[r * cols + c].setEstado(Gema::Estado::IGUAL);
			}
		}
	}
	setState(State::MOVING);
	
}

bool Gestor::generar_premio()
{
	if (score >= puntosPremio) {
		cantidad_premio++;
		gems[(rand()%filas)*cols + (rand()%cols)].setColor(Gema::Color::PREMIO);
		score -=puntosPremio;

		return true;
	}

	return false;
}

bool Gestor::pierde()
{
	if (state == State::LOSING)
		return true;
	else
		return false;
}
