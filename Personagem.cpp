#include "Personagem.h"



Personagem::Personagem()
{		
	velocidade = 0.5; //powerup = 1 normal = 0.5.
	//pos = 0;
	objeto1 = NULL;
	ismovendo = false;
	
}				   

Personagem::~Personagem()
{
}

void Personagem::setSpriteSheet(std::string spr, ObjetoTileMap * obj)
{	
	//Aumentar tamanho da sprite.
	sprite.setEscala(1, 1);
	//Seta tipo sprite para receber spritesheet.
	sprite.setSpriteSheet(spr);
	//Recebe sprite no objeto tile criado no mapa. 
	obj->setSprite(&sprite);

	//define posição inicial como posição centralizada do objeto tile.
	mover.x = obj->getXCentro();
	mover.y = obj->getYCentro();

	//Define o atributo objeto.
	objeto1 = obj;
}

void Personagem::setVelocidade(float vel)
{		  
	velocidade = vel;
	
	sprite.setVelocidadeAnimacao(velocidade * 4); //Animação mais  		
}

float Personagem::getVelocidade()
{
	return velocidade;
}

//
//void Personagem::desenhar()
//{			  	
//	sprite.desenhar(getX(), getY(), getRot()); 
//}

void Personagem::atualizar(TileMap * mapa)
{ 	
	
	if (gTeclado.segurando[TECLA_CIMA] && !mapa->getCamadaDeTiles("Colisor")->getIDdoTile(getX(), getY() - 0.2) && !mapa->getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", getX(), getY() - 0.2))
	{
		ismovendo = true;

		//pos = 3;
		mover.set(mover.x, mover.y - 0.1 * velocidade);
		//mover.y -= 0.1 *velocidade;

		//Seta animação.
		sprite.setAnimacao(0);
		//Avança animação.
		sprite.avancarAnimacao();

		objeto1->setPosCentro(mover.x, mover.y);  
	}

	else if (gTeclado.segurando[TECLA_DIR] && !mapa->getCamadaDeTiles("Colisor")->getIDdoTile(getX() + 0.2, getY()) && !mapa->getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", getX() + 0.2, getY()))
	{
		ismovendo = true;
		//pos = 2;
		mover.set(mover.x + 0.1 * velocidade, mover.y);
		//mover.x += 0.1 *velocidade;

		sprite.setAnimacao(1);
		sprite.avancarAnimacao();

		objeto1->setPosCentro(mover.x, mover.y); 

	}
	else if (gTeclado.segurando[TECLA_BAIXO] && !mapa->getCamadaDeTiles("Colisor")->getIDdoTile(getX(), getY()+ 0.2) && !mapa->getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", getX(), getY() + 0.2))
	{
		
		ismovendo = true;

		//pos = 1;
		mover.set(mover.x, mover.y + 0.1 * velocidade);
		//mover.y += 0.1 * velocidade;		
		sprite.setAnimacao(2);
		sprite.avancarAnimacao();

		objeto1->setPosCentro(mover.x, mover.y);

	}		  
	else if (gTeclado.segurando[TECLA_ESQ] && !mapa->getCamadaDeTiles("Colisor")->getIDdoTile(getX() - 0.2, getY()) && !mapa->getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", getX() - 0.2, getY()))
	{
		ismovendo = true;

		//pos = 0;
		mover.set(mover.x - 0.1 * velocidade, mover.y);
		//mover.x -= 0.1 * velocidade;  		
		sprite.setAnimacao(3);
		sprite.avancarAnimacao();

		objeto1->setPosCentro(mover.x, mover.y); 
	} 		
	else
	{
		ismovendo = false;

		sprite.setFrame(0);
		sprite.recomecarAnimacao();
		mover.set(mover.x, mover.y);
		objeto1->setPosCentro(mover.x, mover.y);

		if (!movendo())
		{
			if (gTeclado.segurando[TECLA_CIMA])
			{					
				sprite.setAnimacao(0);
			}
			else if (gTeclado.segurando[TECLA_DIR])
			{
				sprite.setAnimacao(1);
			}
			else if (gTeclado.segurando[TECLA_BAIXO])
			{
				sprite.setAnimacao(2);
			}
			else if (gTeclado.segurando[TECLA_ESQ])
			{
				sprite.setAnimacao(3);
			}
		}
	}
		 
	
}

bool Personagem::movendo()
{		
	return	ismovendo;
}

Sprite Personagem::getSprite()
{
	return *objeto1->getSprite();
}

float Personagem::getX()
{
	return this->mover.x;
			
}

float Personagem::getY()
{
	return this->mover.y;
}

//int Personagem::getPos()
//{
//	return pos;
//}


