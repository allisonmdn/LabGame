#pragma once
#include "libUnicornio.h"  
#include "Personagem.h"
#include "CarregadorAssets.h"
#include <fstream>
#include "Colisao.h"
#include <stack>//Mapa
#include <ctime>//Score e treasure
#include <vector>//Score
#include "EstadoJogo.h"	//Save - Load
#include "Menu.h"
#include "Account.h"

enum
{
	NIVEL1, NIVEL2, NIVEL3, BONUS_STAGE
};

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();
	void visao();

	//Mapa
	void setMapa(std::string nomemapa);
	void nivelMapa(int nivelx);
	int getNivelMapa();

	void powerUps();

	void inicializarObjetos();

	////Save e Load
	//bool save(std::ostream & os);
	//bool load(std::istream & is);

private:	
	Personagem * personagem = new Personagem;
	EstadoJogo estado_jogo;
	Account * accout;

	//Var. quantidade de objeto score no mapa e rand das posições do objeto no mapa tile.	
	int q_score = 5; //Muda conforme mapa.		
	int rand_posScore;
	int n = 1;
	int qnt_score_get = 0;
	
	//Sprite item personagem

	Sprite sscore, smovup;	   	
	Sprite svida;
	Sprite lanterna, pilhaspr;
	//Sprite item mapa

	Sprite tvisao, portal;
	Sprite treasurebox;
	Sprite trap;
	Sprite alavanca;
	Sprite minotaurospr;

	//Sprite gameover
	Sprite gameover;

	//Streams
	std::fstream arquivos;
	//std::ifstream i_arquivo;
	//std::ofstream o_arquivo;

	Menu * menu = new Menu();	 	 	
	Colisao * colisao = new Colisao; 	

	//Mapa
	TileMap mapa;
	std::stack<std::string>pilhamapanome;

	//Score vetor objetos
	std::vector<ObjetoTileMap*>vetor_rand;
	//std::vector<ObjetoTileMap*>scoresrestantes;

	//Treasure vetor objetos
	std::vector<ObjetoTileMap*>alltreasures;
	//std::vector<ObjetoTileMap*>treasurerestantes;

	//Traps vetor objetos
	std::vector<ObjetoTileMap*>traps;
	//std::vector<ObjetoTileMap*>trapsrestantes;

	//Lavancas vetor objetos
	std::vector<ObjetoTileMap*>alavancas;
	//std::vector<ObjetoTileMap*>alavancasrestantes;
	 
	//Var. Objeto Tilemap
	ObjetoTileMap * objportal;
	ObjetoTileMap * objscore = new ObjetoTileMap;
	ObjetoTileMap * objtreasure = new ObjetoTileMap;
	ObjetoTileMap * objtrap = new ObjetoTileMap;
	ObjetoTileMap * objalavanca = new ObjetoTileMap;
	ObjetoTileMap * bonusstage = new ObjetoTileMap;
	ObjetoTileMap * minotauro = new ObjetoTileMap;
	
	//Tempo
	int /*Nível*/temponv = 600, /*Portal*/tempoportal = 800, /*Trap*/ttime = 600, pilhatempo = 3600/*1 minuto*/, pilhatempototal = 3600;

	//Texto
	Texto txtnivel, txtbonus, txtportal, txtscore, txtchat, txtvida, txtenergiapilha;

	//Score
	int vscore;
	//Vida
	int vida; 			
	//Nível
	int nivel = 1;
	//Movimentação
	int mv = 0; //15 segundos/vez.
};

