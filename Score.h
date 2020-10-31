#include "libUnicornio.h"
#include <iostream>
#include <ctime>
#pragma once
class Score
{
public:
	Score();
	~Score();
		
	//Var
	int score; //Valor

	void scoreManager(float x1, float y1, ObjetoTileMap * objscore, Sprite sprscore);
	void scoreDraw();

	float getX();
	float getY();

	Sprite getSprite();

private:
	float x, y;
	ObjetoTileMap * obj;
	Score * pscore;
};

