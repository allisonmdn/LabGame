#include "libUnicornio.h"
#include <iostream>
#include <vector>
#pragma once
class Colisao
{
public:
	Colisao();
	~Colisao();

	//Sets

	//void colisoes(float char_x, float char_y, Sprite spr_char);//Recebe todas as colisões.
	void colisaoPortal(float char_x, float char_y, float rot, Sprite spr_char, TileMap * mapa);//Colisão com objeto portal.
	void colisaoSpriteScore(float char_x, float char_y, float rot, Sprite spr_char, TileMap * mapa, ObjetoTileMap * score);//Colisão com sprite score.
	void colisaoMapa(float char_x, float char_y, float rot, TileMap * mapa);//Colisão com o cenário tilemap.
	void colisaoItem(float char_x, float char_y, float rot, Sprite spr_char, TileMap * mapa, ObjetoTileMap * tesouro);//Sprite item);//Colisão com sprite dos powerups.
	void colisaoArmadilha(float char_x, float char_y, float rot, Sprite spr_char, TileMap * mapa, ObjetoTileMap * trap);//Sprite spr_inimigo);//Colisão com sprite inimigo.
	void colisaoAlavanca(float char_x, float char_y, float rot, Sprite spr_char, TileMap * mapa, ObjetoTileMap * alavanca);
	
	//Returns

	bool estaColidindoAlavanca();
	bool estaColidindoArmadilha();
	bool estaColidindoItem();
	bool estaColidindoMapa();
	bool estaColidindoSpriteScore();
	bool estaColidindoPortal();

private:
	bool carmadilha, citem, cmapa, cscore, cportal, calavanca;
	int i = 300;
	
};

