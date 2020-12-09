#include "Menu.h"



Menu::Menu()
{		
	op = TELAINICIAL;		   	
}			

Menu::~Menu()
{
}

void Menu::telaCentral()
{
	//set Pos
	
	txtmenu.setEscala(1, 1);
	txtmenu.setString("Bem-vindo, " + conta->username);
	txtmenu.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 250);

	botaoNovoJogo.setX(gJanela.getLargura() / 2);
	botaoNovoJogo.setY(gJanela.getAltura() / 2 - 100);
	botaoCarregarJogo.setX(botaoNovoJogo.getX());
	botaoCarregarJogo.setY(botaoNovoJogo.getY() + 60);
	botaoRanking.setX(botaoCarregarJogo.getX());
	botaoRanking.setY(botaoCarregarJogo.getY() + 60);
	botaoCreditos.setX(botaoRanking.getX());
	botaoCreditos.setY(botaoRanking.getY() + 60);

	botaoSair.setX(botaoCreditos.getX());
	botaoSair.setY(botaoCreditos.getY() + 60);

	botaoNovoJogo.desenhar();
	botaoNovoJogo.atualizar();

	botaoCarregarJogo.desenhar();
	botaoCarregarJogo.atualizar();

	botaoRanking.desenhar();
	botaoRanking.atualizar();

	botaoCreditos.desenhar();
	botaoCreditos.atualizar();
	
	botaoSair.desenhar();
	botaoSair.atualizar();

	botaoVoltar.desenhar();
	botaoVoltar.atualizar();

	if (botaoVoltar.estaClicado())
	{
		op = TELAINICIAL;
	}

	if (botaoNovoJogo.estaClicado())
	{
		botaoNovoJogo.setAnimacaoDoEstadoAbaixado(1);
		op = NOVOJOGO;
	}
	else if (botaoCarregarJogo.estaClicado())
	{
		botaoCarregarJogo.setAnimacaoDoEstadoAbaixado(1);
		op = CARREGARJOGO;
	}
	else if (botaoRanking.estaClicado())
	{
		botaoRanking.setAnimacaoDoEstadoAbaixado(1);
		op = RANKING;
	}
	else if (botaoCreditos.estaClicado())
	{
		botaoCreditos.setAnimacaoDoEstadoAbaixado(1);
		op = CREDITOS;
	}
	else if (botaoSair.estaClicado())
	{
		botaoSair.setAnimacaoDoEstadoAbaixado(1);
		op = SAIR;
	}

}

void Menu::telaInicial()
{
	botaoLogin.setX(gJanela.getLargura() / 2);
	botaoLogin.setY(gJanela.getAltura() / 2);

	botaoCadastrar.setX(gJanela.getLargura() - 100);
	botaoCadastrar.setY(gJanela.getAltura() - 100);

	
	botaoSair.setX(botaoLogin.getX());
	botaoSair.setY(botaoLogin.getY() + 60);		
	
	botaoLogin.desenhar();
	botaoLogin.atualizar();

	botaoCadastrar.desenhar();
	botaoCadastrar.atualizar();

	botaoSair.desenhar();
	botaoSair.atualizar();


	if (botaoCadastrar.estaClicado())
	{
		botaoCadastrar.setAnimacaoDoEstadoAbaixado(1);
		op = CADASTRAR;	   
	}
	else if (botaoLogin.estaClicado())
	{
		//botaoLogin.setAnimacaoDoEstadoAbaixado(1);
		op = LOGIN;
	}

}

bool Menu::cadastrar()
{	
	
	//TXT TOPO
	txtmenu.setString("CADASTRO");
	txtmenu.desenhar(gJanela.getLargura() / 2, 100);

	if (botaoVoltar.estaClicado())
	{
		botaoVoltar.setAnimacaoDoEstadoAbaixado(1);
		op = TELAINICIAL;

		inserir.finalizar();
	}

	botaoVoltar.desenhar();
	botaoVoltar.atualizar();	 
	
	if (!gTeclado.inputTexto.estaHabilitado())
	{
		//Set fonte, inicializa a string e habilita a digitação.
		inserir.inicializar();
	}
	if (gTeclado.inputTexto.estaHabilitado() && !csenha.empty())
	{
		//Apagar texto e desabilitar.
		inserir.finalizar();
	}


	//Desenhar e atualizar texto.
	if (login.empty() || senha.empty() || csenha.empty())
	{
		inserir.atualizar();
		inserir.desenhar();
	}
	//CADASTRANDO
	if (!gTeclado.soltou[TECLA_ENTER])
	{
		if (gTeclado.inputTexto.estaHabilitado() && login.empty())
		{
			gGraficos.desenharTexto("DIGITE UM NOVO USUÁRIO", gJanela.getLargura() / 2, gJanela.getAltura() / 3, 255, 255, 255, 100);

		}
		else if (gTeclado.inputTexto.estaHabilitado() && senha.empty())
		{
			gGraficos.desenharTexto("DIGITE UMA NOVA SENHA", gJanela.getLargura() / 2, gJanela.getAltura() / 3, 255, 255, 255, 100);
		}
		else if (gTeclado.inputTexto.estaHabilitado() && csenha.empty())
		{
			gGraficos.desenharTexto("CONFIRME A NOVA SENHA", gJanela.getLargura() / 2, gJanela.getAltura() / 3, 255, 255, 255, 100);
		}							
	}
	
	//novouser:

	if (gTeclado.soltou[TECLA_ENTER])
	{	 		
					
		if (login.empty()) //Se variável string vazia.
		{	   
			login = gTeclado.inputTexto.getString(); //Recebe texto digitado.
			conta->username = login;
			gTeclado.inputTexto.apagarTudo(); 
		}
		else
		{		 
			if (senha.empty())
			{
				senha = gTeclado.inputTexto.getString();
				gTeclado.inputTexto.apagarTudo();
			}
			else if (csenha.empty())// && !senha.empty())
			{
				csenha = gTeclado.inputTexto.getString();
				gTeclado.inputTexto.apagarTudo();			  
				
			}					 			
			
		}

		gDebug.depurar("criando usuário: ", login);
		gDebug.depurar("criando senha: ", senha);
		gDebug.depurar("confirmação da senha: ", csenha);
		
	}

	//Finalização do cadastro.
	if (!senha.empty() && !csenha.empty() && csenha != senha)
	{

		//Se a senha secundária é diferente da primária.

		gGraficos.desenharTexto("APERTE [DELETE] PARA DIGITAR NOVAMENTE A SENHA", gJanela.getLargura() / 2, gJanela.getAltura() / 4, 255, 255, 255, 255);

		gGraficos.desenharTexto("SENHAS DIFERENTES, DIGITE NOVAMENTE!", gJanela.getLargura() / 2, gJanela.getAltura() / 2, 255, 255, 255, 250);
		
		if (gTeclado.soltou[TECLA_DELETE])
		{
			senha.clear();
			csenha.clear();
		}

	}
	else
	{
		if (csenha == senha && !csenha.empty())
		{
			conta->senha = csenha;
			
			conta->score = 0;
			
			//o_archivos.open("../Registro.bin", std::ios::binary | std::ios::app);
			

			i_archivos.open("../Registro.txt", std::ios::in);

			accs.clear();//Limpar vetor de contas.
						

			if (!i_archivos.fail())
			{
				while (!i_archivos.eof())
				{
					Account* accConfirm = new Account();

					i_archivos >> accConfirm->username >> accConfirm->senha;


					accs.push_back(accConfirm);
				}

				i_archivos.close();//Fechar arquivo.
								
			}		
			if (accs.size() > 0)
			{
				for (int i = 0; i < accs.size(); i++)
				{
					if (conta->username == accs.at(i)->username)
					{
						gGraficos.desenharTexto("APERTE [ENTER] PARA CRIAR NOVAMENTE!", gJanela.getLargura() / 2, gJanela.getAltura() / 4, 255, 255, 255, 255);
						texto.setString("USUARIO JÁ EXISTE!");
						texto.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

						if (gTeclado.soltou[TECLA_ENTER])
						{
							login.clear();
							conta->username.clear();
							senha.clear();
							conta->senha.clear();
							csenha.clear();
						}
																	
						
					}
				}
			}			
			if (!conta->username.empty() && !conta->senha.empty())
			{
				archivos.open("../Score.txt", std::ios::out | std::ios::app);

				texto.setString("REGISTRADO COM SUCESSO!");

				texto.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

				o_archivos.open("../Registro.txt", std::ios::app);

				//Score
				if (!archivos.is_open())
				{
					gDebug.depurar("Erro ao abrir score", archivos.fail());
				}
				else
				{
					archivos << conta->username << " " << conta->score;
					archivos << std::endl;

				}
				//Fecha arquivo.
				archivos.close();

				//Registro
				if (!o_archivos.is_open())
				{

					gDebug.depurar("Erro ao abrir registro(Cadastro)", o_archivos.fail());
				}
				else
				{
					//o_archivos.write(reinterpret_cast<const char *>(conta), sizeof(Account));

					o_archivos << conta->username << " " << conta->senha;

					o_archivos << std::endl;

					op = TELAPRINCIPAL;

					//conta->username.clear();
					//conta->senha.clear();

					o_archivos.close();//Fecha arquivo.

					return true;
				}
			}
					
			
		}
	}
	
	return false;	

}

bool Menu::logIn()
{	
	//TXT TOPO
	txtmenu.setString("LOGIN");
	txtmenu.desenhar(gJanela.getLargura() / 2, 100);
	
	if (botaoVoltar.estaClicado())
	{
		botaoVoltar.setAnimacaoDoEstadoAbaixado(1);
		op = TELAINICIAL;

		inserir.finalizar();
	}
	
	botaoVoltar.atualizar();
	botaoVoltar.desenhar();

	//i_archivos.open("../Registro.bin", std::ios::in | std::ios::binary);
	
	i_archivos.open("../Registro.txt", std::ios::in);

	accs.clear();

	while (!i_archivos.eof())
	{		
		//i_archivos.read(reinterpret_cast<char *>(conta), sizeof(Account));		
		Account* accConfirm = new Account();

		i_archivos >> accConfirm->username >> accConfirm->senha;
		
		accs.push_back(accConfirm);	

		archivos << std::endl;
	}
	i_archivos.close();
		

	if (!gTeclado.inputTexto.estaHabilitado())
	{
		//Set fonte, inicializa a string e habilita a digitação.
		inserir.inicializar();
	}
	if (gTeclado.inputTexto.estaHabilitado() && !senha.empty() && !login.empty())
	{
		//Apagar texto e desabilitar.
		inserir.finalizar();
	}		 
		//Desenhar e atualizar texto.
	if (login.empty() || senha.empty())
	{
		inserir.atualizar();
		inserir.desenhar();
	}

	if (!gTeclado.soltou[TECLA_ENTER] && login.empty() || !gTeclado.soltou[TECLA_ENTER] && senha.empty())
	{
		if (gTeclado.inputTexto.estaHabilitado() && login.empty())
		{
			gGraficos.desenharTexto("DIGITE SEU USUÁRIO", gJanela.getLargura() / 2, gJanela.getAltura() / 3, 255, 255, 255, 100);

		}
		else if (gTeclado.inputTexto.estaHabilitado() && senha.empty())
		{
			gGraficos.desenharTexto("DIGITE SUA SENHA", gJanela.getLargura() / 2, gJanela.getAltura() / 3, 255, 255, 255, 100);
		}

	}

	if (gTeclado.soltou[TECLA_ENTER])
	{					

		if (login.empty()) //Se variável string vaz	ia.
		{

			login = gTeclado.inputTexto.getString(); //Recebe texto digitado.
			conta->username = login;
			gTeclado.inputTexto.apagarTudo();

			senha.clear(); //Limpar campos subsequentes.

		}
		else
		{

			if (senha.empty() && !login.empty())
			{
				senha = gTeclado.inputTexto.getString();
				conta->senha = senha;
				gTeclado.inputTexto.apagarTudo();
			}

			gDebug.depurar("login: ", login);
			gDebug.depurar("senha: ", senha);

			for (int i = 0; i < accs.size(); i++)
			{
				if (login == accs.at(i)->username)
				{
					conta->username = login;
					conta->senha = accs.at(i)->senha;

					continue;
				}				
			}

			gDebug.depurar("usuário cadastrado: ", conta->username);
			gDebug.depurar("senha correta cadastrada: ", conta->senha);

		} 		

	}
	
	if (!login.empty() && !senha.empty())
	{
		for (int i = 0; i < accs.size(); i++)
		{
			if (login != accs.at(i)->username && i == accs.size() - 1)
			{
				gGraficos.desenharTexto("APERTE [DELETE] PARA DIGITAR O LOGIN", gJanela.getLargura() / 2, gJanela.getAltura() / 4, 255, 255, 255, 255);

				texto.setString("CONTA NÃO EXISTE!");

				texto.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

				if (gTeclado.soltou[TECLA_DELETE])
				{
					login.clear();		
					conta->username.clear();
					
				}
				
			}
			else
			{ 
				if (senha != accs.at(i)->senha && i == accs.size() - 1)
				{
					gGraficos.desenharTexto("APERTE [DELETE] PARA DIGITAR NOVAMENTE A SENHA", gJanela.getLargura() / 2, gJanela.getAltura() / 4, 255, 255, 255, 255);

					texto.setString("SENHA INCORRETA!");

					texto.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

					if (gTeclado.soltou[TECLA_DELETE])
					{
						conta->senha.clear();
						senha.clear();
					}

				}

				if (login == accs.at(i)->username && senha == accs.at(i)->senha)
				{
					op = TELAPRINCIPAL;

					login.clear();
					senha.clear();					

					return true;
				}
			}
	
	

			
		}
		
	}  	
	
	return false;
}

void Menu::novoJogo()
{
	//TXT TOPO
	txtmenu.setEscala(1, 1);
	txtmenu.setString("New Game\n\nSelect a slot to save game.");
	txtmenu.desenhar(gJanela.getLargura() / 2, 100);

	if (botaoVoltar.estaClicado())
	{
		botaoVoltar.setAnimacaoDoEstadoAbaixado(1);
		op = TELAPRINCIPAL;
	}
	botaoVoltar.desenhar();
	botaoVoltar.atualizar();
	
	for (int i = 0; i < 3; i++)
	{
		slot[i].desenhar();
		slot[i].atualizar();

		/*if (slot[i].estaComMouseEmCima())
		{
			slot[i].setEstado(BOTAOSPRITE_ABAIXADO);
		}*/
	}
	
	if (slot[0].estaClicado() || slot[1].estaClicado() || slot[2].estaClicado())
	{
		newgame = true;
	}
	else
	{
		newgame = false;
	}
		
	
}

void Menu::carregarJogo()
{
	//TXT TOPO
	txtmenu.setEscala(1, 1);
	txtmenu.setString("Load Game\n\nSelect a slot to load game.");
	txtmenu.desenhar(gJanela.getLargura() / 2, 100);

	if (botaoVoltar.estaClicado())
	{
		botaoVoltar.setAnimacaoDoEstadoAbaixado(1);
		op = TELAPRINCIPAL;
	}
	botaoVoltar.desenhar();
	botaoVoltar.atualizar();
	
	for (int i = 0; i < 3; i++)
	{
		slot[i].desenhar();
		slot[i].atualizar();
/*
		if (slot[i].estaComMouseEmCima())
		{				
			slot[i].setEstado(BOTAOSPRITE_ABAIXADO);
		}*/
	}

	if (slot[0].estaClicado() || slot[0].estaClicado() || slot[0].estaClicado())
	{
		loadgame = true;
	}
	else
	{
		loadgame = false;
	}
}

bool Menu::novoJogoIsClicado()
{
	return newgame;
}

bool Menu::carregarJogoIsClicado()
{
	return loadgame;
}

void Menu::ranking()
{
	//TXT TOPO
	txtmenu.setEscala(1, 1);
	txtmenu.setString("Ranking\n\nTop 5 scores.");
	txtmenu.desenhar(gJanela.getLargura() / 2, 100);
	if (botaoVoltar.estaClicado())
	{
		botaoVoltar.setAnimacaoDoEstadoAbaixado(1);
		op = TELAPRINCIPAL;
	}
	botaoVoltar.desenhar();
	botaoVoltar.atualizar();
/*
	i_archivos.open("Ranking.txt", std::ios::in);

	while (!archivos.eof())
	{
		archivos >> contacomp->username >> " " >> contacomp->score;
		scores.push_back(conta);
	}
	i_archivos.close();*/


}

void Menu::creditos()
{	
	//TXT TOPO
	txtmenu.setEscala(1, 1);
	txtmenu.setString("Créditos\n\n\nDESENVOLVEDORES\n\n\nAllison M.\n\n\nVinicius G.\n\n\nARTE\n\n Allison M.");
	txtmenu.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
	if (botaoVoltar.estaClicado())
	{
		botaoVoltar.setAnimacaoDoEstadoAbaixado(1);
		op = TELAPRINCIPAL;
	}

	botaoVoltar.desenhar();				
	botaoVoltar.atualizar();

	gGraficos.desenharRetangulo(400, 300, 0, 200, 400, 255, 255, 255, 100, true);
	
	
}

bool Menu::sair()
{
	bool ext = false;
	
	if (botaoSair.estaClicado()) //Se botão for clicado.
	{
		ext = true;
	}

	return ext;
}

void Menu::inicializarMenu()
{		
	//Texto preenchimento	  
	  	
	texto.setFonte("fonte");
	texto.setAlinhamento(TEXTO_ALINHADO_A_ESQUERDA);
	texto.setCor(255, 255, 255, true);

	
	//Texto menu
	txtmenu.setFonte("fonte");
	txtmenu.setEscala(2, 2);
	txtmenu.setAlinhamento(TEXTO_CENTRALIZADO);
	txtmenu.setCor(255, 255, 255, true);

	//SLOTS

	slot[0].setSpriteSheet("slot");
	slot[1].setSpriteSheet("slot");
	slot[2].setSpriteSheet("slot");

	slot[0].setX(gJanela.getLargura() / 2);
	slot[0].setY(gJanela.getAltura() / 2 - 50);

	slot[1].setX(gJanela.getLargura() / 2);
	slot[1].setY(gJanela.getAltura() / 2); 

	slot[2].setX(gJanela.getLargura() / 2);
	slot[2].setY(gJanela.getAltura() / 2 + 50);


	//Botao
	botaoLogin.setSpriteSheet("Login");
	botaoCadastrar.setSpriteSheet("Cadastrar");

	botaoNovoJogo.setSpriteSheet("NovoJogo");
	botaoCarregarJogo.setSpriteSheet("CarregarJogo");
	botaoRanking.setSpriteSheet("Ranking");
	botaoCreditos.setSpriteSheet("Creditos");
	botaoSair.setSpriteSheet("Sair");

	botaoVoltar.setSpriteSheet("Voltar");	
	
	botaoVoltar.setX(gJanela.getLargura() - 70);
	botaoVoltar.setY(gJanela.getAltura() - 70);  	
}

void Menu::executar()
{

	//LOGIN, CADASTRAR, NOVOJOGO, CARREGARJOGO, RANKING, CREDITOS, SAIR

	//Limpando variáveis.
	if (op == TELAINICIAL)
	{
		login.clear();
		senha.clear();
		csenha.clear();
	}

	switch (op)
	{
	case TELAINICIAL:
		telaInicial();
		break;
	case TELAPRINCIPAL:
		telaCentral();
		break;
	case LOGIN:
		logIn();
		break;
	case CADASTRAR:
		cadastrar(); 
		break;
	case NOVOJOGO:
		novoJogo();
		break;
	case CARREGARJOGO:
		carregarJogo();
		break;
	case RANKING:
		ranking();
		break;
	case CREDITOS:
		creditos();
		break;
	case SAIR:
		sair();
		break;

	}
}
