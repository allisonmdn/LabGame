#include "EstadoJogo.h"



EstadoJogo::EstadoJogo()
{
}


EstadoJogo::~EstadoJogo()
{
}

void EstadoJogo::setScore(int s)
{
	scoredef = s;
}

void EstadoJogo::setNivel(int n)
{
	niveldef = n;
}

void EstadoJogo::setVida(int v)
{
	vidadef = v;
}

void EstadoJogo::setPowerUp(float pwup)
{
	powerupdef = pwup;
}

int EstadoJogo::getScore()
{
	return powerupdef;
}

int EstadoJogo::getNivel()
{
	return niveldef;
}

int EstadoJogo::getVida()
{
	return vidadef;
}

float EstadoJogo::getPowerUp()
{
	return powerupdef;
}
