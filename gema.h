#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Gema{
	public:
	//Mejora la legitividad del codigo asignandole valores de 0,...,n(cantidad de variables del enum)
    enum class Color : int
    {
    	ROJO , NARANJA , AMARILLO , VERDE , AZUL , MORADO , BLANCO , PREMIO 
	};
	enum class Estado : int
	{
		NUEVO, NINGUNO, SELECCIONAR, IGUAL, MOVER, BORRAR, ELIMINAR
	};
		Gema(int col, int fila, Color color, Texture& txt_gema, Estado estado);
	    ~Gema() = default;
		void dibujar(RenderWindow& window);
	    bool comprobar(const Vector2f& spos);
	    void intercambiar_obj(Gema& otra);
	    Estado actualizar();

	    int getCol() const { return col; }
	    int getFila() const { return fila; }
	    void setColor(Color color) { this->color = color; }
	    Color getColor() const { return color; }
	    void setEstado(Estado estado);
	    Estado getEstado() const { return estado; }
	    
	    //conservará su valor hasta la ejecución del programa y, además, no aceptará ningún cambio en su valor
	    static const Vector2f size;
	    static constexpr int padding = 4;
	    static constexpr int gemSize = 64;
	private:
		int          col, fila;
	    Vector2f     pos;
	    Vector2f     objetivo;
	    Sprite       spr_gema;
	    Texture      txt_gema;
	    Color        color;
	    Estado       estado;
	    int          alpha = 255;
};
