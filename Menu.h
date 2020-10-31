#include <iostream>
#include "libUnicornio.h"
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include "InputTexto.h"
#include "Account.h"	

#pragma once

enum {
	TELAINICIAL, TELAPRINCIPAL, LOGIN, CADASTRAR, NOVOJOGO, CARREGARJOGO, RANKING, CREDITOS, SAIR  //Utilizado para switch case.  
};

class Menu
{
public:
	Menu();
	~Menu();

	//Menu central.

	void telaCentral();
	void telaInicial();

	//Tela inicial.

	bool cadastrar();
	bool logIn();

	//Menu Central.
	
	void novoJogo();
	void carregarJogo();
	bool novoJogoIsClicado();
	bool carregarJogoIsClicado();
	void ranking();
	void creditos();
	bool sair();

	//Set sprites.
	void inicializarMenu();

	//Desenhar

	void executar();
	
private:
		
	char op; //Switch case menu.
	int opacidade = 255;
	bool newgame = false, loadgame = false;
	//fstream

	std::fstream archivos; //Para arquivos do tipo entrada e saída.
	std::ifstream i_archivos;
	std::ofstream o_archivos;
	//Conta

	std::string senha, csenha;//Adicionar e confirmar senha.
	std::string login, clogin;//Adicionar e confirmar login.

	//Sprites

	BotaoSprite botaoLogin, botaoCadastrar, botaoNovoJogo, botaoCarregarJogo, botaoRanking;
	BotaoSprite botaoCreditos, botaoSair, botaoVoltar;
	BotaoSprite * slot = new BotaoSprite[3];	
;
	std::stack<int> menu; //Empilhar menu.
	std::vector<Account*> accs;
	//std::vector<Account*> scores;
	//std::vector<Account*>::iterator it;
	Account * conta = new Account;
	//Account * contacomp = new Account;
	InputTexto inserir;
	Texto texto, txtmenu;
	

	

};

