#include "Colisao.h"



Colisao::Colisao()
{
	cportal = false;
	cscore = false;
	cmapa = false;
	citem = false;
	carmadilha = false;
	calavanca = false;
}


Colisao::~Colisao()
{
}

//void Colisao::colisoes(float char_x, float char_y, Sprite spr_char)
//{
//	bool colPortal = colisaoPortal(char_x, char_y, spr_char);
//	bool colSprScore = colisaoSpriteScore(char_x, char_y, spr_char);
//	bool colMapa = colisaoMapa(char_x, char_y, spr_char);
//	bool colItem = colisaoItem(char_x, char_y, spr_char);
//	bool colInimigo = colisaoInimigo(char_x, char_y, spr_char);
//}

void Colisao::colisaoPortal(float char_x, float char_y, float rot, Sprite spr_char, TileMap * mapa)
{		
	if (mapa->existeObjetoDoTipoNaPos("Levelmap", char_x, char_y) && mapa->getCamadaDeObjetos("Portal")->getObjeto("Portal1")->getSprite())
	{
		cportal = true;
	}
	else
	{
		cportal = false;
	}
}

void Colisao::colisaoSpriteScore(float char_x, float char_y, float rot, Sprite spr_char,  TileMap * mapa, ObjetoTileMap * score)
{		
	if (mapa->existeObjetoDoTipoNaPos("Score", char_x, char_y) && /*score->getSprite() ==*/ mapa->getCamadaDeObjetos("Objetos")->getObjetoDoTipoNaPos("Score", char_x, char_y)->getSprite())
	{			
		cscore = true; 
		////Deletando objeto score.
		//mapa->getObjetoDoTipoNaPos("Score", score->getX(), score->getY())->getCamada()->destruirObjeto(mapa->getObjetoDoTipoNaPos("Score", char_x, char_y));
	}
	else
	{
		cscore = false;
	}
}

void Colisao::colisaoMapa(float char_x, float char_y, float rot, TileMap * mapa)
{		
	
	/*if (mapa->getCamadaDeTiles("Colisor")->getIDdoTile(char_x - 0.2, char_y)) 	
	{  	 
		cmapa = true;
	}
	else if (mapa->getCamadaDeTiles("Colisor")->getIDdoTile(char_x + 0.2, char_y)) 	
	{
		cmapa = true;
	}
	else if (mapa->getCamadaDeTiles("Colisor")->getIDdoTile(char_x, char_y - 0.2))	
	{
		cmapa = true;
	}
	else if (mapa->getCamadaDeTiles("Colisor")->getIDdoTile(char_x, char_y + 0.2))	
	{
		cmapa = true;
	}
	else
	{
		cmapa = false;
	}*/
	
}

void Colisao::colisaoItem(float char_x, float char_y, float rot, Sprite spr_char, TileMap * mapa, ObjetoTileMap * tesouro)
{		
	//pos vida (+30, 50);
	

	if (mapa->existeObjetoDoTipoNaPos("Treasure", char_x, char_y - 0.2) && mapa->getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", char_x, char_y - 0.2)->getSprite())
	{

		//CIMA
		citem = true;
				
		//if (gTeclado.soltou[TECLA_F])
		//{
		//	 						
		//	//Deletando objeto tesouro.
		//	mapa->getObjetoDoTipoNaPos("Treasure", tesouro->getXCentro(), tesouro->getYCentro())->getCamada()->destruirObjeto(mapa->getObjetoDoTipoNaPos("Treasure", char_x, char_y - 1));
		//							
		//}  
	}
	else if (mapa->existeObjetoDoTipoNaPos("Treasure", char_x + 0.2, char_y) && mapa->getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", char_x + 0.2, char_y)->getSprite())
	{
		//DIREITA
		citem = true;	
		
		//tesouro->getSprite()->avancarAnimacao();  		
		
		//if (gTeclado.soltou[TECLA_F])
		//{
		//	
		//	//Deletando objeto tesouro.
		//	mapa->getObjetoDoTipoNaPos("Treasure", tesouro->getXCentro(), tesouro->getYCentro())->getCamada()->destruirObjeto(mapa->getObjetoDoTipoNaPos("Treasure", char_x + 1, char_y));

		//}
		
	}
	else if (mapa->existeObjetoDoTipoNaPos("Treasure", char_x, char_y + 0.2) && mapa->getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", char_x, char_y + 0.2)->getSprite())
	{
		//BAIXO
		citem = true;	 
		
		//tesouro->getSprite()->avancarAnimacao(); 		

		//if (gTeclado.soltou[TECLA_F])
		//{
		//	
		//	//Deletando objeto tesouro.
		//	mapa->getObjetoDoTipoNaPos("Treasure", tesouro->getXCentro(), tesouro->getYCentro())->getCamada()->destruirObjeto(mapa->getObjetoDoTipoNaPos("Treasure", char_x, char_y + 0.2));
		//}
	
	}
	else if (mapa->existeObjetoDoTipoNaPos("Treasure", char_x - 0.2, char_y) && mapa->getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", char_x - 0.2, char_y)->getSprite())
	{
		 //ESQUERDA
		citem = true;			
		//
		////tesouro->getSprite()->avancarAnimacao();		
		//
		//if (gTeclado.soltou[TECLA_F])
		//{
		//	
		//	//Deletando objeto tesouro.
		//	mapa->getObjetoDoTipoNaPos("Treasure", tesouro->getXCentro(), tesouro->getYCentro())->getCamada()->destruirObjeto(mapa->getObjetoDoTipoNaPos("Treasure", char_x - 1, char_y));
		//				
		//} 		
	} 	
	else
	{			
		citem = false;			 		
	}
	
	//Deletando objeto tesouro.
	//mapa->getObjetoDoTipoNaPos("Treasure", tesouro->getXCentro(), tesouro->getYCentro())->getCamada()->destruirObjeto(mapa->getObjetoDoTipoNaPos("Treasure", char_x, char_y));
		   	
}

void Colisao::colisaoArmadilha(float char_x, float char_y, float rot, Sprite spr_char, TileMap * mapa, ObjetoTileMap * trap)
{	
	if (mapa->existeObjetoDoTipoNaPos("Trap", char_x, char_y) && mapa->getCamadaDeObjetos("Armadilhas")->getObjetoDoTipoNaPos("Trap", char_x, char_y)->getSprite())
	{			
		
		trap->getSprite()->avancarAnimacao();
		if (trap->getSprite()->terminouAnimacao())
		{
			////Destruir objeto trap.
			//mapa->getObjetoDoTipoNaPos("Trap", trap->getXCentro(), trap->getYCentro())->getCamada()->destruirObjeto(mapa->getObjetoDoTipoNaPos("Trap", char_x, char_y));
			carmadilha = true;	 
			
		} 		
	}
	else
	{
		carmadilha = false;
		
	}
}

void Colisao::colisaoAlavanca(float char_x, float char_y, float rot, Sprite spr_char, TileMap * mapa, ObjetoTileMap * alavanca)
{
	if (mapa->existeObjetoDoTipoNaPos("Alavanca", char_x, char_y) && mapa->getCamadaDeObjetos("Alavancas")->getObjetoDoTipoNaPos("Alavanca", char_x, char_y)->getSprite())
	{
		calavanca = true;			
	}
	else
	{
		calavanca = false;
	}
}

bool Colisao::estaColidindoAlavanca()
{
	return calavanca;
}

bool Colisao::estaColidindoArmadilha()
{
	return carmadilha;
}

bool Colisao::estaColidindoItem()
{
	return citem;
}

bool Colisao::estaColidindoMapa()
{
	return cmapa;
}

bool Colisao::estaColidindoSpriteScore()
{
	return cscore;
}

bool Colisao::estaColidindoPortal()
{
	return cportal;
}
