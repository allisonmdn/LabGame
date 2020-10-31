#include <iostream>
#include "libUnicornio.h"

#pragma once
class Personagem
	:public ObjetoTileMap
{
public:
	Personagem();
	~Personagem();

	//Set.

	void setSpriteSheet(std::string spr, ObjetoTileMap * obj);
	void setVelocidade(float vel);
	float getVelocidade();
	
	//Desenhar

	//void desenhar();
	void atualizar(TileMap * mapa);

	//Mover	 	
	bool movendo();	   

	//Retorno

	Sprite getSprite();
	float getX();
	float getY();
	//int getPos(); 	

private:
	Sprite sprite;
	Vetor2D mover;
	//int pos; //Posição em que o personagem está virado.
	float velocidade;
	ObjetoTileMap * objeto1;
	bool ismovendo;
					
};

