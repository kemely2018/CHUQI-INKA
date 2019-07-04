#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "gema.h"
using namespace sf;
using namespace std;
class Gestor{
public:
	Gestor() = default;
	~Gestor() = default;
	
	bool iniciar();
	void click(const Vector2f& spos);
	void cargar_graficos();
	void reiniciar();
	void update();
	void draw(RenderWindow& window);
	bool generar_premio();
	bool pierde();

	static constexpr int filas = 8;
	static constexpr int cols = 8;
	static constexpr int puntosPremio = 10;

	int getScore() const { return score; }

private:
	enum class State : int
	{
		WAITING, SELECTED, SWAPPING, MOVING, ARRANGING, LOSING
	};

	void setState(State newState);
	int match();
	int match3(Gema* gem1, Gema* gem2, Gema* gem3);
	bool organizar();
	void reemplazar_eliminado();
	void explotar(Gema* gem);

	vector<Gema> gems;
	Texture      texture;
	int          sel1;
	int          sel2;
	State        state = State::WAITING;
	int          score = 0;
	int          cantidad_premio;
};
