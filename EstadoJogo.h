#include <iostream>
#pragma once
class EstadoJogo
{
public:
	EstadoJogo();
	~EstadoJogo();

	//Set
	void setScore(int s);
	void setNivel(int n);
	void setVida(int v);
	void setPowerUp(float pwup);

	//Return

	int getScore();
	int getNivel();
	int getVida();
	float getPowerUp();

private:
	int scoredef, niveldef, vidadef;
	float powerupdef;


};

