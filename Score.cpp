#include "Score.h"



Score::Score()
{
	this->score = 0;
	srand(time(0));
	
}


Score::~Score()
{
}

void Score::scoreManager(float x1, float y1, ObjetoTileMap * objscore, Sprite sprscore)
{
	
	obj = objscore;	 
	obj->setSprite(&sprscore);	 
	
	obj = new ObjetoTileMap[10];
	pscore = new Score[10];

	for (int i = 0; i < 10; i++)
	{			
		obj[i].getSprite();
		pscore[i].x = x1;
		pscore[i].y = y1;
	}
}

void Score::scoreDraw()
{
	for (int i = 0; i < 10; i++)
	{
		obj[i].desenhar(obj[i].getX(), obj[i].getY());
	}

}

float Score::getX()
{
	return x;
}

float Score::getY()
{
	return y;
}

Sprite Score::getSprite()
{
	return *obj->getSprite();
}

