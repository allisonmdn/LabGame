#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);
	
	//Carregador assets

	arquivos.open("../mapa_assets.txt", std::ios::in);

	CarregadorAssets * cAssets = new CarregadorAssets;

	if (!arquivos.is_open())
	{
		gDebug.erro("Erro ao abrir .txt");
	}
	else
	{
		if (!cAssets->Carregador(arquivos))
		{
			gDebug.erro("Erro ao carregar assets", this);

		}
		
	}
	arquivos.close();
	
	menu->inicializarMenu();

	//Texto
	
	txtnivel.setFonte("fonte");
	txtnivel.setAlinhamento(TEXTO_CENTRALIZADO);

	txtbonus.setFonte(txtnivel.getFonte());//Padrão tipo fonte informativa.
	txtbonus.setAlinhamento(TEXTO_CENTRALIZADO);  

	txtportal.setFonte(txtnivel.getFonte());
	txtportal.setAlinhamento(TEXTO_CENTRALIZADO);
	txtportal.setEspacamentoLinhas(1.5);

	txtscore.setFonte("fonteminec");
	txtscore.setAlinhamento(TEXTO_ALINHADO_A_ESQUERDA);

	txtvida.setFonte(txtscore.getFonte()); //Padrão tipo fonte atributos personagem.
	txtvida.setAlinhamento(TEXTO_CENTRALIZADO);		
		
	txtenergiapilha.setFonte(txtscore.getFonte());
	txtenergiapilha.setAlinhamento(TEXTO_CENTRALIZADO);
	//txtenergiapilha.setEscala(0.5, 0.5);

	txtchat.setFonte("fontehello");
	txtchat.setAlinhamento(TEXTO_CENTRALIZADO);	 	
		
	//Empilhando mapa.
	pilhamapanome.push("bonus_stage");
	pilhamapanome.push("mapanv3");	//Mapa 3
	pilhamapanome.push("mapanv2");	//Mapa 2
	pilhamapanome.push("mapaintro");//Mapa 1				

	//Setando mapa.							

	setMapa(pilhamapanome.top()); //Busca mapa na posição de cima da pilha.
	
	//Inicializa sprites.
	
	sscore.setSpriteSheet("moeda");
	sscore.setVelocidadeAnimacao(5);
	svida.setSpriteSheet("Coracao"); 		
	smovup.setSpriteSheet("movup");
	portal.setSpriteSheet("portal");
	trap.setSpriteSheet("trap1");
	trap.setVelocidadeAnimacao(10);
	alavanca.setSpriteSheet("alavanca");
	lanterna.setSpriteSheet("lanterna");
	pilhaspr.setSpriteSheet("pilha");										  
	treasurebox.setSpriteSheet("tesouro");
	minotaurospr.setSpriteSheet("Minotauro");
	minotaurospr.setEscala(2, 2);

	//GAMEOVERSPRITE

	gameover.setSpriteSheet("gameover"); 

	//Personagem atributos
	vida = 3;
	vscore = 0;

	inicializarObjetos(); // Cria e inicializa os objetos no mapa do tipo tile carregado.
	

		//O resto da inicialização vem aqui!
		//...
}

void Jogo::finalizar()
{
		//O resto da finalização vem aqui (provavelmente, em ordem inversa a inicialização)!
		//...
	mapa.descarregar();
	gRecursos.descarregarTudo();
	uniFinalizar();
}

void Jogo::executar()
{
	while (!gTeclado.soltou[TECLA_ESC] && !gEventos.sair && menu->sair() != true)
	{
		uniIniciarFrame();

	menu_telaprincipal:

		menu->executar();

		if (menu->carregarJogoIsClicado() || menu->novoJogoIsClicado())
		{
			while (!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
			{
				uniIniciarFrame();

				/*if (gTeclado.soltou[TECLA_VOLTAR])
				{
					goto menu_telaprincipal;
				}*/

				//Define os valores das variáveis nos tipos de colisões.  

				if (vida > 0)
				{
					colisao->colisaoMapa(personagem->getX(), personagem->getY(), personagem->getRot(), &mapa);
					colisao->colisaoPortal(personagem->getX(), personagem->getY(), personagem->getRot(), personagem->getSprite(), &mapa);
					colisao->colisaoSpriteScore(personagem->getX(), personagem->getY(), personagem->getRot(), personagem->getSprite(), &mapa, objscore);
					colisao->colisaoItem(personagem->getX(), personagem->getY(), personagem->getRot(), personagem->getSprite(), &mapa, objtreasure);
					colisao->colisaoArmadilha(personagem->getX(), personagem->getY(), personagem->getRot(), personagem->getSprite(), &mapa, objtrap);
					colisao->colisaoAlavanca(personagem->getX(), personagem->getY(), personagem->getRot(), personagem->getSprite(), &mapa, objalavanca);
					//Atualiza posição do personagem.
					personagem->atualizar(&mapa);

					//Coloca a posição do objeto personagem como a posição central do mapa.

					mapa.setPosCentro(personagem->getX(), personagem->getY());

					//Método desenhar nesse caso, desenha o mapa e o objeto criado no mapa.
					mapa.desenhar();

					minotaurospr.avancarAnimacao();
					if (nivel != 4)//Diferente de bônus stage.
					{
						//Luz personagem.
						visao();

					}
					else
					{
						lanterna.setCorAlpha(100);//Indicando que foi desabilitada a lanterna.
					}
					if (mapa.estaCarregado())
					{
						if (temponv > 0) // 10 segundos == 60FPS x 10
						{
							if (nivel == 4)
							{
								txtbonus.setString("BÔNUS STAGE");
								txtbonus.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 250);
																
								if (temponv <= 255)
								{
									txtbonus.setCorAlpha(temponv - 255, true);//Transparência nome nível.
								}

							}
							else
							{
								if (nivel >= 1 && nivel <= 3)
								{
									txtnivel.setString("NÍVEL " + std::to_string(nivel));
									txtnivel.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 250);
									
									if (temponv <= 255)
									{
										txtnivel.setCorAlpha(temponv - 255, true);//Transparência nome nível.
									}

								}
							}
							--temponv;

						}
					} 
					//TXT AVISO!
					if (mapa.existeObjetoDoTipoNaPos("Trap", personagem->getX() - 1, personagem->getY()) || mapa.existeObjetoDoTipoNaPos("Trap", personagem->getX() + 1, personagem->getY()) || mapa.existeObjetoDoTipoNaPos("Trap", personagem->getX(), personagem->getY() + 1) || mapa.existeObjetoDoTipoNaPos("Trap", personagem->getX(), personagem->getY() - 1))
					{
						gGraficos.desenharTexto("Sinto cheiro de perigo!", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 30, 255, 255, 0, 255);
						gGraficos.desenharRetangulo(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 20, 0, 250, 20, 0.5, 1, 255, 255, 255, 10, true);//Caixa de texto.
					}	
					//Testa se a colisão for verdadeira.

					//BÔNUS STAGE
					if (mapa.existeObjetoDoTipoNaPos("Bonus", personagem->getX() - 0.5, personagem->getY()))
					{
						//TXT AVISO!
						gGraficos.desenharTexto("[ENTER] Para entrar", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 100, 255, 255, 255, 255);
						gGraficos.desenharTexto("Foi encontrada uma passagem.", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 30, 255, 255, 0, 255);
						gGraficos.desenharRetangulo(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 20, 0, 250, 20, 0.5, 1, 255, 255, 255, 10, true);//Caixa de texto.
						if (gTeclado.soltou[TECLA_ENTER])
						{
							txtbonus.setCorAlpha(255, true);
							pilhamapanome.pop();//Removendo nome do mapa carregado.
							mapa.descarregar();//Descarregando mapa anterior e preparando para novo mapa.
							if (!mapa.estaCarregado() && vida > 0)
							{
								nivel = 4;
								nivelMapa(nivel);
							}

						}
					}
					else if (mapa.existeObjetoDoTipoNaPos("Bonus", personagem->getX() + 0.5, personagem->getY()))
					{
						//TXT AVISO!
						gGraficos.desenharTexto("[ENTER] Para entrar", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 100, 255, 255, 255, 255);
						gGraficos.desenharTexto("Foi encontrada uma passagem.", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 30, 255, 255, 0, 255);
						gGraficos.desenharRetangulo(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 20, 0, 250, 20, 0.5, 1, 255, 255, 255, 10, true);//Caixa de texto.
						if (gTeclado.soltou[TECLA_ENTER])
						{
							txtbonus.setCorAlpha(255, true);
							pilhamapanome.pop();//Removendo nome do mapa carregado.
							mapa.descarregar();//Descarregando mapa anterior e preparando para novo mapa.
							if (!mapa.estaCarregado() && vida > 0)
							{
								nivel = 4;
								nivelMapa(nivel);
							}

						}
					}

					else if (mapa.existeObjetoDoTipoNaPos("Bonus", personagem->getX(), personagem->getY() - 0.5))
					{
						//TXT AVISO!
						gGraficos.desenharTexto("[ENTER] Para entrar", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 100, 255, 255, 255, 255);
						gGraficos.desenharTexto("Foi encontrada uma passagem.", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 30, 255, 255, 0, 255);
						gGraficos.desenharRetangulo(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 20, 0, 250, 20, 0.5, 1, 255, 255, 255, 10, true);//Caixa de texto.
						if (gTeclado.soltou[TECLA_ENTER])
						{
							txtbonus.setCorAlpha(255, true);
							pilhamapanome.pop();//Removendo nome do mapa carregado.
							mapa.descarregar();//Descarregando mapa anterior e preparando para novo mapa.
							if (!mapa.estaCarregado() && vida > 0)
							{
								nivel = 4;
								nivelMapa(nivel);
							}

						}
					}
					else if (mapa.existeObjetoDoTipoNaPos("Bonus", personagem->getX(), personagem->getY() + 0.5))
					{
						//TXT AVISO!
						gGraficos.desenharTexto("[ENTER] Para entrar", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 100, 255, 255, 255, 255);
						gGraficos.desenharTexto("Foi encontrada uma passagem.", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 30, 255, 255, 0, 255);
						gGraficos.desenharRetangulo(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 20, 0, 250, 20, 0.5, 1, 255, 255, 255, 10, true);//Caixa de texto.
						if (gTeclado.soltou[TECLA_ENTER])
						{
							txtbonus.setCorAlpha(255, true);
							pilhamapanome.pop();//Removendo nome do mapa carregado.
							mapa.descarregar();//Descarregando mapa anterior e preparando para novo mapa.
							if (!mapa.estaCarregado() && vida > 0)
							{
								nivel = 4;
								nivelMapa(nivel);
							}	
						}
					}

					//PORTAL 
					if (colisao->estaColidindoPortal() == true && mapa.getCamadaDeObjetos("Portal")->getObjeto("Portal1")->estaVisivel())
					{
						//Se atingir pontuação de score mínima, e colidir com portal, passa para o próximo nível do mapa.  
							 
						//PORTAL COLIDINDO
						gGraficos.desenharTexto("Próximo nível? [ENTER] Para entrar", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 100, 255, 255, 255, 255);
						txtnivel.setCorAlpha(255, true);

						if (gTeclado.soltou[TECLA_ENTER2] || gTeclado.soltou[TECLA_ENTER] && nivel != 3)
						{
							pilhamapanome.pop();//Removendo nome do mapa carregado.
							mapa.descarregar();//Descarregando mapa anterior e preparando para novo mapa.
							if (!mapa.estaCarregado() && vida > 0)
							{									
								if (nivel == 4)
								{
									temponv = 600;
									tempoportal = 800;
									nivel--;
									nivelMapa(nivel);
								}
								else
								{
									if (nivel == 1)
									{
										temponv = 600;
										tempoportal = 800;
										nivel++;
										nivelMapa(nivel);
									}
									else if (nivel == 2)
									{
										temponv = 600;
										tempoportal = 800;
										nivel++;
										nivelMapa(nivel);
									}
									else if (nivel == 3)
									{
										temponv = 600;
										tempoportal = 800;

									}
								}
							}
						}
						else
						{
							//if (gTeclado.soltou[TECLA_ENTER2] || gTeclado.soltou[TECLA_ENTER] && nivel == 3)
							//{
							//	pilhamapanome.pop();//Removendo nome do mapa carregado.
							//	mapa.descarregar();//Descarregando mapa e parabenizando jogador pela conquista.

							//	txtchat.setEscala(3, 3);
							//	txtchat.setString("PARABÉNS! VOCÊ CONSEGUIU SAIR DO LABIRINTO!");
							//	txtchat.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
							//	gGraficos.desenharTexto("Aperte [VOLTAR] para ir ao menu.", gJanela.getLargura() / 2, gJanela.getAltura() / 2 + 200, 255, 255, 0, 255);

							//	if (gTeclado.soltou[TECLA_VOLTAR])
							//	{
							//		break;
							//	}

							//}
						}
					}
					else
					{
						if (qnt_score_get >= q_score) //Metade do score total do mapa.
						{
							//PORTAL LIBERADO
							mapa.getCamadaDeObjetos("Portal")->getObjeto("Portal1")->setVisivel(true);
							
							if (tempoportal > 0)
							{
								txtportal.setString("PORTAL LIBERADO PARA PRÓXIMO NÍVEL!");
								txtportal.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 250);

								if (tempoportal <= 255)
								{
									txtportal.setCorAlpha(tempoportal - 255, true);
								}
								--tempoportal;
							}

						}
						else
						{
							//PORTAL NÃO LIBERADO
							mapa.getCamadaDeObjetos("Portal")->getObjeto("Portal1")->setVisivel(false);
						}
					}

					if (mapa.getCamadaDeObjetos("Portal")->getObjeto("Portal1")->estaVisivel())
					{
						objportal->getSprite()->avancarAnimacao();
					}  					

					//ITEM	

					if (colisao->estaColidindoItem() == true)
					{
						//Recebe powerups: 30% Vida = +1, 50% Velocidade de movimento = + 0.5 (durante 15 segundos), 20% Score = +50;

						gGraficos.desenharTexto("[F] Abrir baú", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 100, 255, 255, 255, 255);

						std::vector<ObjetoTileMap*>::iterator itbau;

						if (mapa.existeObjetoDoTipoNaPos("Treasure", personagem->getX(), personagem->getY() - 0.2) && mapa.getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", personagem->getX(), personagem->getY() - 0.2)->getSprite())
						{

							//CIMA 							

							if (gTeclado.soltou[TECLA_F])
							{			   
								itbau = std::find(alltreasures.begin(), alltreasures.end(), mapa.getObjetoDoTipoNaPos("Treasure", personagem->getX(), personagem->getY() - 1));

								if (itbau != alltreasures.end())
								{
									alltreasures.erase(itbau);

									//Deletando objeto tesouro.
									mapa.getObjetoDoTipoNaPos("Treasure", objtreasure->getXCentro(), objtreasure->getYCentro())->getCamada()->destruirObjeto(mapa.getObjetoDoTipoNaPos("Treasure", personagem->getX(), personagem->getY() - 1));
								}
							}
						}
						else if (mapa.existeObjetoDoTipoNaPos("Treasure", personagem->getX() + 0.2, personagem->getY()) && mapa.getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", personagem->getX() + 0.2, personagem->getY())->getSprite())
						{
							//DIREITA
							
							if (gTeclado.soltou[TECLA_F])
							{

								itbau = std::find(alltreasures.begin(), alltreasures.end(), mapa.getObjetoDoTipoNaPos("Treasure", personagem->getX() + 1, personagem->getY()));

								if (itbau != alltreasures.end())
								{
									alltreasures.erase(itbau);	 

									//Deletando objeto tesouro.
									mapa.getObjetoDoTipoNaPos("Treasure", objtreasure->getXCentro(), objtreasure->getYCentro())->getCamada()->destruirObjeto(mapa.getObjetoDoTipoNaPos("Treasure", personagem->getX() + 1, personagem->getY()));
								}							

							}

						}
						else if (mapa.existeObjetoDoTipoNaPos("Treasure", personagem->getX(), personagem->getY() + 0.2) && mapa.getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", personagem->getX(), personagem->getY() + 0.2)->getSprite())
						{
							//BAIXO
							
							if (gTeclado.soltou[TECLA_F])
							{
								itbau = std::find(alltreasures.begin(), alltreasures.end(), mapa.getObjetoDoTipoNaPos("Treasure", personagem->getX(), personagem->getY() + 1));
								
								if (itbau != alltreasures.end())
								{
									alltreasures.erase(itbau);

									//Deletando objeto tesouro.
									mapa.getObjetoDoTipoNaPos("Treasure", objtreasure->getXCentro(), objtreasure->getYCentro())->getCamada()->destruirObjeto(mapa.getObjetoDoTipoNaPos("Treasure", personagem->getX(), personagem->getY() + 1));
								}									
							}	
						}
						else if (mapa.existeObjetoDoTipoNaPos("Treasure", personagem->getX() - 0.2, personagem->getY()) && mapa.getCamadaDeObjetos("Treasure")->getObjetoDoTipoNaPos("Treasure", personagem->getX() - 0.2, personagem->getY())->getSprite())
						{
							//ESQUERDA
							
							if (gTeclado.soltou[TECLA_F])
							{

								itbau = std::find(alltreasures.begin(), alltreasures.end(), mapa.getObjetoDoTipoNaPos("Treasure", personagem->getX() - 1, personagem->getY()));

								if (itbau != alltreasures.end())
								{
									alltreasures.erase(itbau);

									//Deletando objeto tesouro.
									mapa.getObjetoDoTipoNaPos("Treasure", objtreasure->getXCentro(), objtreasure->getYCentro())->getCamada()->destruirObjeto(mapa.getObjetoDoTipoNaPos("Treasure", personagem->getX() - 1, personagem->getY()));
								}									

							}
						}

						treasurebox.avancarAnimacao();

						
						if (gTeclado.soltou[TECLA_F])
						{															
							int ti = rand() % 100; //0 ~ 2 							
							srand(time(0));

							//TREASURE ITEM
							enum {
								VIDAEXTRA, MOVIMENTACAO, BONUS_SCORE, PILHAENERGIA
							};
							//CHANCE ITEM
							//MOV = 40% VIDA = 30% SCORE = 10% ENERGIA PILHA = 20%
							if (ti >= 0 && ti <= 39)
							{
								ti = MOVIMENTACAO;
							}
							else if (ti > 39 && ti <= 69)
							{
								ti = VIDAEXTRA;
							}
							else if (ti > 69 && ti <= 89)
							{
								ti = PILHAENERGIA;
							}
							else if (ti > 89 && ti <= 99)
							{
								ti = BONUS_SCORE;
							}

							switch (ti)
							{
							case VIDAEXTRA:
								if (vida >= 1 && vida < 4)
								{
									vida += 1;
								} 								
								break;

							case MOVIMENTACAO:
								mv += 900;
								personagem->setVelocidade(1);
								break;
							case BONUS_SCORE: vscore += 50;
								break;
							case PILHAENERGIA:
								pilhatempo += 3600;	// + 1 minuto.(3600 == 60 FPS)
								pilhatempototal = pilhatempo;//Total > 100%
								break;

							}

						}
					}
					else
					{
						treasurebox.recomecarAnimacao();
					}

					//POWERUPS
					powerUps();

					//COLISAOMAPA
					if (colisao->estaColidindoMapa() == true)
					{
						//Personagem não muda de posição.			

					}
					//SCORE
					if (colisao->estaColidindoSpriteScore() == true)
					{
						std::vector<ObjetoTileMap*>::iterator itscore;

						itscore = std::find(vetor_rand.begin(), vetor_rand.end(), mapa.getObjetoDoTipoNaPos("Score", personagem->getX(), personagem->getY()));

						if (itscore != vetor_rand.end())
						{
							//Deletando objeto score do mapa.
							mapa.getObjetoDoTipoNaPos("Score", objscore->getX(), objscore->getY())->getCamada()->destruirObjeto(*itscore/*mapa.getObjetoDoTipoNaPos("Score", personagem->getX(), personagem->getY())*/);
							//Deletando objeto do vetor.
							vetor_rand.erase(itscore);

						}								
						//Aumenta pontuação do score 							
						vscore += 10;

						this->qnt_score_get += 1;				  						
					}
					//ALAVANCA
					if (colisao->estaColidindoAlavanca() == true)
					{
						gGraficos.desenharTexto("[A] Puxar alavanca", gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 100, 255, 255, 255, 255);

						if (gTeclado.soltou[TECLA_A])
						{
							std::vector<ObjetoTileMap*>::iterator it;

							if (nivel == 1)
							{
								//2 TRAPS
								//Destruir armadilhas em ordem crescente.
								if (mapa.existeObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()) && mapa.getObjeto("Alavanca1") && mapa.existeObjetoDoTipoNaPos("Trap", mapa.getObjeto("Trap1")->getXCentro(), mapa.getObjeto("Trap1")->getYCentro()))
								{
									it = std::find(traps.begin(), traps.end(), mapa.getObjeto("Trap1"));

									if (it != traps.end())
									{
										//Destruir objeto trap.(Desativar)
										mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*it);
										traps.erase(it);
										
									}									
									
								}
								else if (mapa.existeObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()) && mapa.getObjeto("Alavanca2") && mapa.existeObjetoDoTipoNaPos("Trap", mapa.getObjeto("Trap2")->getXCentro(), mapa.getObjeto("Trap2")->getYCentro()))
								{
									it = std::find(traps.begin(), traps.end(), mapa.getObjeto("Trap2"));

									if (it != traps.end())
									{
										mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*it);
										traps.erase(it);
										
									}																				
								}											
								//Procura objeto da posição no vetor.
								it = std::find(alavancas.begin(), alavancas.end(), mapa.getObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()));
								//Encontra objeto e deleta o objeto no vetor e do mapa.
								if (it != alavancas.end())
								{
									mapa.getObjetoDoTipoNaPos("Alavanca", objalavanca->getXCentro(), objalavanca->getYCentro())->getCamada()->destruirObjeto(*it);
									alavancas.erase(it);		  									 								
								}								  								
							} 							
							else if (nivel == 2)
							{
								//7 TRAPS

								if (mapa.existeObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()) && mapa.getObjeto("Alavanca1") && mapa.existeObjetoDoTipoNaPos("Trap", mapa.getObjeto("Trap1")->getXCentro(), mapa.getObjeto("Trap1")->getYCentro()))
								{
									//Procura objeto no vetor
									it = std::find(traps.begin(), traps.end(), mapa.getObjeto("Trap1"));

									//Encontra, deleta o objeto na posição específica do vetor e do mapa.
									if (it != traps.end())
									{
										mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*it);
										traps.erase(it); 										
									}
								}
								else if (mapa.existeObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()) && mapa.getObjeto("Alavanca2") && mapa.existeObjetoDoTipoNaPos("Trap", mapa.getObjeto("Trap2")->getXCentro(), mapa.getObjeto("Trap2")->getYCentro()))
								{
									it = std::find(traps.begin(), traps.end(), mapa.getObjeto("Trap2"));

									if (it != traps.end())
									{
										mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*it);										
										traps.erase(it);	   										
									}
								}
								else if (mapa.existeObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()) && mapa.getObjeto("Alavanca3") && mapa.existeObjetoDoTipoNaPos("Trap", mapa.getObjeto("Trap3")->getXCentro(), mapa.getObjeto("Trap3")->getYCentro()))
								{
									it = std::find(traps.begin(), traps.end(), mapa.getObjeto("Trap3"));

									if (it != traps.end())
									{	
										mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*it);
										traps.erase(it);  										
									}
								}
								else if (mapa.existeObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()) && mapa.getObjeto("Alavanca4") && mapa.existeObjetoDoTipoNaPos("Trap", mapa.getObjeto("Trap4")->getXCentro(), mapa.getObjeto("Trap4")->getYCentro()))
								{
									it = std::find(traps.begin(), traps.end(), mapa.getObjeto("Trap4"));

									if (it != traps.end())
									{
										mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*it);
										traps.erase(it); 										
									}

								}
								else if (mapa.existeObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()) && mapa.getObjeto("Alavanca5") && mapa.existeObjetoDoTipoNaPos("Trap", mapa.getObjeto("Trap5")->getXCentro(), mapa.getObjeto("Trap5")->getYCentro()))
								{
									it = std::find(traps.begin(), traps.end(), mapa.getObjeto("Trap5"));

									if (it != traps.end())
									{	
										mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*it);
										traps.erase(it);										
									}

								}
								else if (mapa.existeObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()) && mapa.getObjeto("Alavanca6") && mapa.existeObjetoDoTipoNaPos("Trap", mapa.getObjeto("Trap6")->getXCentro(), mapa.getObjeto("Trap6")->getYCentro()))
								{
									it = std::find(traps.begin(), traps.end(), mapa.getObjeto("Trap6"));

									if (it != traps.end())
									{
										mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*it);
										traps.erase(it); 										
									}
								}
								else if (mapa.existeObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()) && mapa.getObjeto("Alavanca7") && mapa.existeObjetoDoTipoNaPos("Trap", mapa.getObjeto("Trap7")->getXCentro(), mapa.getObjeto("Trap7")->getYCentro()))
								{
									it = std::find(traps.begin(), traps.end(), mapa.getObjeto("Trap7"));

									if (it != traps.end())
									{
										mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*it);
										traps.erase(it);										
									}
								}
									 								
								//Procura objeto da posição no vetor.
								it = std::find(alavancas.begin(), alavancas.end(), mapa.getObjetoDoTipoNaPos("Alavanca", personagem->getX(), personagem->getY()));
								//Encontra objeto e deleta o objeto no vetor e do mapa.
								if (it != alavancas.end())
								{
									mapa.getObjetoDoTipoNaPos("Alavanca", objalavanca->getXCentro(), objalavanca->getYCentro())->getCamada()->destruirObjeto(*it);
									alavancas.erase(it);
									
								}
								
							}
							
						}
					}

					//if (gTeclado.soltou[TECLA_A] && colisao->estaColidindoAlavanca())//Ajustar condição para desenhar texto na tela.
					//{
					//	if (ttime > 0)
					//	{
					//		txtchat.setString("Armadilha desarmada com sucesso!");
					//		txtchat.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2 - 200);
					//		ttime--;
					//	}
					//	else
					//	{
					//		ttime = 600;
					//	}
					//}

					//ARMADILHA
					if (colisao->estaColidindoArmadilha() == true)
					{
						std::vector<ObjetoTileMap*>::iterator ittrap;

						ittrap = std::find(traps.begin(), traps.end(), mapa.getObjetoDoTipoNaPos("Trap", personagem->getX(), personagem->getY()));

						if (ittrap != traps.end())
						{
							//Deletar objeto trap do mapa.
							mapa.getObjetoDoTipoNaPos("Trap", objtrap->getXCentro(), objtrap->getYCentro())->getCamada()->destruirObjeto(*ittrap);
							//Deletar objeto trap do vetor.
							traps.erase(ittrap);	  						
						}

						//Reduz vida do personagem.							

						if (vida >= 1)
						{
							vida -= 1;

						}


					}
					
					  //----INTERFACE JOGADOR BEGIN----//
					//Pontuação jogador score
					txtscore.setString(" X " + std::to_string(vscore));
					txtscore.desenhar(gJanela.getLarguraTotal() - 70, 45);	//Largura total da resolução.
					sscore.desenhar(gJanela.getLarguraTotal() - 100, 40);//Sprite score.
					sscore.avancarAnimacao();
					//TXTSCORE
					gGraficos.desenharTexto("SCORE", gJanela.getLarguraTotal() - 70,  20, 255, 255, 255, 255);
					//Vida Jogador
					//svida.desenhar(30, 50);
					//txtvida.setString(std::to_string(vida));  										
					//txtvida.desenhar(31, 52);
					int aux_x, aux_y;
					for (int i = 1; i <= vida; i++)
					{
						if (i == 1)
						{
							aux_x = 30;
							aux_y = 50;

							svida.desenhar(aux_x, aux_y);
						}
						else
						{
							if (i >= 2 && i <= vida)
							{
								aux_y += 32;
								svida.desenhar(aux_x, aux_y);
							}
						}
					}

					//TXTVIDA
					gGraficos.desenharTexto("LIFE", 30, 20, 255, 255, 255, 255);
					//LANTERNA
					lanterna.desenhar(170, 50);
					//TXTLANTERNA
					gGraficos.desenharTexto("LANTERN", 170, 20, 255, 255, 255, 255);
					//PILHAENERGIA
					pilhaspr.desenhar(100, 50);
					//TXTPILHA
					gGraficos.desenharTexto("LANTERN's\n ENERGY", 100, 20, 255, 255, 255, 255); 
					//TXTPORCENTAGEM
					txtenergiapilha.setString(std::to_string(pilhatempo / (pilhatempototal / 100)) + "%");
					txtenergiapilha.desenhar(100, 75);

					 //----INTERFACE JOGADOR END----//
				}
				else
				{
					mapa.descarregar();
					if (vida == 0)//GameOver
					{
						//accout->score = vscore;

						gameover.setAnimacaoAoContrario(true);

						gameover.avancarAnimacao();
						gameover.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

						gGraficos.desenharTexto("[VOLTAR] Para voltar ao menu", gJanela.getLargura() / 2, gJanela.getAltura() / 2 + 200, 255, 255, 0, 255);		

					}
				}

				//Seu código vem aqui!
				//...
				uniTerminarFrame();
			}					

		}
		uniTerminarFrame();
	}

		
			
}	


void Jogo::visao()
{
	
	if (gTeclado.segurando[TECLA_V] && pilhatempo > 0)
	{			
		tvisao.setSpriteSheet("visaog");
		lanterna.setAnimacao(1);
		pilhatempo--;
	}
	else
	{
		tvisao.setSpriteSheet("visaoc");
		lanterna.setAnimacao(0);			
	}

	if (pilhatempo > 0)
	{
		lanterna.setCorAlpha(255);
	}
	else
	{
		lanterna.setCorAlpha(100);
	}
	tvisao.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
}

void Jogo::setMapa(std::string nomemapa)
{		
	mapa.carregar("assets/mapa/" + nomemapa +".json");
	
}

void Jogo::nivelMapa(int nivelx)
{
	nivel = nivelx;
	switch (nivel - 1)
	{
	case NIVEL1:
		q_score = 5;
		qnt_score_get = 0;
		for (int i = 0; i < pilhamapanome.size(); i++)
		{
			pilhamapanome.pop();
		}
		pilhamapanome.push("mapaintro");
		setMapa(pilhamapanome.top());
		inicializarObjetos();
		
		//Treasure 1
		//Score 9
		break;
	case NIVEL2:
		q_score = 23;
		qnt_score_get -= qnt_score_get;
		
		for (int i = 0; i < pilhamapanome.size(); i++)
		{
			pilhamapanome.pop();
		}
		pilhamapanome.push("mapanv2");
		setMapa(pilhamapanome.top());
		inicializarObjetos();
		
		//Treasure 12
		//Score 46
		break;
	case NIVEL3:
		q_score = 11;
		qnt_score_get -= qnt_score_get;
		
		for (int i = 0; i < pilhamapanome.size(); i++)
		{
			pilhamapanome.pop();
		}
		pilhamapanome.push("mapanv3");
		setMapa(pilhamapanome.top());
		inicializarObjetos();
		break;
	case BONUS_STAGE:
		q_score = 13;
		qnt_score_get -= qnt_score_get;
		for (int i = 0; i < pilhamapanome.size(); i++)
		{
			pilhamapanome.pop();
		}
		pilhamapanome.push("bonus_stage");
		setMapa(pilhamapanome.top());
		inicializarObjetos();
		
		//Treasure 3
		//Score 24
		break;
	}
}

int Jogo::getNivelMapa()
{
	return nivel;
}

void Jogo::powerUps()
{
	//POWERUPS
	if (personagem->getVelocidade() == 1)
	{
		if (mv > 0)
		{				
			//Opacidade movimentação.
			if (mv > 275 && mv <= 300)
			{
				smovup.setCorAlpha(100);
			}
			else if (mv <= 275 && mv > 250)
			{
				smovup.setCorAlpha(255);
			}
			else if (mv > 225 && mv <= 250)
			{
				smovup.setCorAlpha(100);
			}
			else if (mv > 200 && mv <= 225)
			{
				smovup.setCorAlpha(255);
			}
			else if (mv > 175 && mv <= 200)
			{
				smovup.setCorAlpha(100);
			}
			else if (mv > 150 && mv <= 175)
			{
				smovup.setCorAlpha(255);
			}
			else if (mv > 125 && mv <= 150)
			{
				smovup.setCorAlpha(100);
			}
			else if (mv > 100 && mv <= 125)
			{
				smovup.setCorAlpha(255);
			}
			else if (mv > 75 && mv <= 100)
			{
				smovup.setCorAlpha(100);
			}
			else if (mv > 50 && mv <= 75)
			{
				smovup.setCorAlpha(255);
			}
			else if (mv > 25 && mv <= 50)
			{
				smovup.setCorAlpha(100);
			}
			else if (mv > 0 && mv <= 25)
			{
				smovup.setCorAlpha(255);
			}
			smovup.desenhar(30, 100);
			gGraficos.desenharTexto(std::to_string(mv / 60), 30, 120, 255, 255, 255, 255);
		}
		else
		{
			personagem->setVelocidade(0.5);
			
		}
		mv--;

	}
	
}

void Jogo::inicializarObjetos()
{		 	

	//PORTAL  

	objportal = mapa.getCamadaDeObjetos("Portal")->getObjeto("Portal1");
	objportal->setPosCentro(mapa.getCamadaDeObjetos("Portal")->getObjeto("Portal1")->getXCentro(), mapa.getCamadaDeObjetos("Portal")->getObjeto("Portal1")->getYCentro());
	objportal->setSprite(&portal);
			  
	//TREASURE
	//nv 1 = 1
	//nv 2 = 13
	//nv 3 = 1
	//nv 4 = 24

	if (nivel == 1)
	{
		while (!alltreasures.empty())
		{
			alltreasures.pop_back();
		}
		for (int i = 1; i <= 1; i++)
		{
			objtreasure = mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i));
			objtreasure->setPosCentro(mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i))->getYCentro());
			objtreasure->setSprite(&treasurebox);

			alltreasures.push_back(objtreasure);
		}
		
	}
	else if (nivel == 2)
	{	
		while (!alltreasures.empty())
		{
			alltreasures.pop_back();
		}

		for (int i = 1; i <= 13; i++)
		{	
			objtreasure = mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i));
			objtreasure->setPosCentro(mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i))->getYCentro());
			objtreasure->setSprite(&treasurebox);
			
			alltreasures.push_back(objtreasure);
		}
	}
	else if (nivel == 3)
	{
		while (!alltreasures.empty())
		{
			alltreasures.pop_back();
		}

		for (int i = 1; i <= 1; i++)
		{
			objtreasure = mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i));
			objtreasure->setPosCentro(mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i))->getYCentro());
			objtreasure->setSprite(&treasurebox);

			alltreasures.push_back(objtreasure);
		}
	}
	else if (nivel == 4)
	{
		//BÔNUS STAGE
		while (!alltreasures.empty())
		{
			alltreasures.pop_back();
		}

		for (int i = 1; i <= 3; i++)
		{
			objtreasure = mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i));
			objtreasure->setPosCentro(mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Treasure")->getObjeto("Treasure" + std::to_string(i))->getYCentro());
			objtreasure->setSprite(&treasurebox);

			alltreasures.push_back(objtreasure);
		}

	}
	//TREASURE SETPOS
	//Rotacionando a imagem baseado na colisão.
	if (nivel >= 3 && nivel <= 4)
	{
		if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() + 1))
		{
			treasurebox.setAnimacao(0);
		}
		else if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() - 1, objtreasure->getYCentro()))
		{
			treasurebox.setAnimacao(1);
		}
		else if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() - 1))
		{
			treasurebox.setAnimacao(2);
		}
		else
		{
			if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() + 1, objtreasure->getYCentro()))
			{
				treasurebox.setAnimacao(3);
			}
		}
	}
	else
	{				
		if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() - 1, objtreasure->getYCentro()) && mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() + 1, objtreasure->getYCentro()) && mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() + 1) && !mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() - 1))
		{
			//Sem saída pra baixo.
			treasurebox.setAnimacao(0);
		}
		else if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() - 1) && mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() + 1) && mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() - 1, objtreasure->getYCentro()) && !mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() + 1, objtreasure->getYCentro()))
		{
			//Sem saída pra esquerda.
			treasurebox.setAnimacao(1);
		}
		else if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() - 1, objtreasure->getYCentro()) && mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() + 1, objtreasure->getYCentro()) && mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() - 1) && !mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() + 1))
		{
			//Sem saída pra cima.
			treasurebox.setAnimacao(2);
		}
		else if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() - 1) && mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro(), objtreasure->getYCentro() + 1) && mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() + 1, objtreasure->getYCentro()) && !mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objtreasure->getXCentro() - 1, objtreasure->getYCentro()))
		{
			//Sem saída pra direita.	
			treasurebox.setAnimacao(3);
		}
	}	   	

	//LAVANCA SETPOS	
	if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objalavanca->getX() - 0.5, objalavanca->getY()))
	{
		//Colisao esquerda
		alavanca.setAnimacao(3);
	}
	if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objalavanca->getX(), objalavanca->getY() + 0.5))
	{
		//Colisao baixo
		alavanca.setAnimacao(2);
	}
	if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objalavanca->getX() + 0.5, objalavanca->getY()))
	{
		//Colisao direita
		alavanca.setAnimacao(1);
	}
	if (mapa.getCamadaDeTiles("Colisor")->getIDdoTile(objalavanca->getX(), objalavanca->getY() - 0.5))
	{
		//Colisao cima	
		alavanca.setAnimacao(0);
	} 	

	//TRAPS

	//nv 1 = 2
	//nv 2 = 7

	if (nivel == 1)
	{
		for (int i = 1; i < 3; i++)
		{
			objtrap = mapa.getCamadaDeObjetos("Armadilhas")->getObjeto("Trap" + std::to_string(i));
			objtrap->setPosCentro(mapa.getCamadaDeObjetos("Armadilhas")->getObjeto("Trap" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Armadilhas")->getObjeto("Trap" + std::to_string(i))->getYCentro());
			objtrap->setSprite(&trap);

			traps.push_back(objtrap);

			//LAVANCAS
			objalavanca = mapa.getCamadaDeObjetos("Alavancas")->getObjeto("Alavanca" + std::to_string(i));
			objalavanca->setPosCentro(mapa.getCamadaDeObjetos("Alavancas")->getObjeto("Alavanca" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Alavancas")->getObjeto("Alavanca" + std::to_string(i))->getYCentro());
			objalavanca->setSprite(&alavanca);

			alavancas.push_back(objalavanca);			
		}

		bonusstage = mapa.getCamadaDeObjetos("bonus_stage")->getObjeto("Bonus_stage1");
		bonusstage->setPosCentro(mapa.getCamadaDeObjetos("bonus_stage")->getObjeto("Bonus_stage1")->getXCentro(), mapa.getCamadaDeObjetos("bonus_stage")->getObjeto("Bonus_stage1")->getYCentro());
		
	}
	else if (nivel == 2)
	{
		for (int i = 1; i <= 7; i++)
		{
			objtrap = mapa.getCamadaDeObjetos("Armadilhas")->getObjeto("Trap" + std::to_string(i));
			objtrap->setPosCentro(mapa.getCamadaDeObjetos("Armadilhas")->getObjeto("Trap" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Armadilhas")->getObjeto("Trap" + std::to_string(i))->getYCentro());
			objtrap->setSprite(&trap);

			traps.push_back(objtrap);

			//LAVANCAS
			objalavanca = mapa.getCamadaDeObjetos("Alavancas")->getObjeto("Alavanca" + std::to_string(i));
			objalavanca->setPosCentro(mapa.getCamadaDeObjetos("Alavancas")->getObjeto("Alavanca" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Alavancas")->getObjeto("Alavanca" + std::to_string(i))->getYCentro());
			objalavanca->setSprite(&alavanca);

			alavancas.push_back(objalavanca);
		}

		bonusstage = mapa.getCamadaDeObjetos("bonus_stage")->getObjeto("Bonus_stage1");
		bonusstage->setPosCentro(mapa.getCamadaDeObjetos("bonus_stage")->getObjeto("Bonus_stage1")->getXCentro(), mapa.getCamadaDeObjetos("bonus_stage")->getObjeto("Bonus_stage1")->getYCentro());
	}
	else if (nivel == 3)
	{
		for (int i = 1; i <= 1; i++)
		{
			objtrap = mapa.getCamadaDeObjetos("Armadilhas")->getObjeto("Trap" + std::to_string(i));
			objtrap->setPosCentro(mapa.getCamadaDeObjetos("Armadilhas")->getObjeto("Trap" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Armadilhas")->getObjeto("Trap" + std::to_string(i))->getYCentro());
			objtrap->setSprite(&trap);

			traps.push_back(objtrap);

		}
	
	}
			 
	//SCORE
		
	//Randomicamente objeto score
	/*srand(time(0));*/
	/*rand_posScore = rand() % q_score + 1;*/

	int i = 1;
	if (nivel == 1)
	{
		do {
			objscore = mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i));
			objscore->setPosCentro(mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getYCentro());
			objscore->setSprite(&sscore);

			vetor_rand.push_back(objscore);
			i++;
		} while (i <= 5);
		//std::vector<ObjetoTileMap*>::iterator it;

		//if (save(o_arquivo))
		//{
		//	while (!scoresrestantes.empty())//Zera vetor de scores restantes.
		//	{
		//		scoresrestantes.pop_back();
		//	}

		//	for (it; it != vetor_rand.end();it++)//Percorre e salva em um vetor auxiliar os scores que restaram no mapa.
		//	{
		//		scoresrestantes.push_back(*it);
		//	}
		//}
		//else if (load(i_arquivo))
		//{
		//	while (!vetor_rand.empty())//Zera vetor de scores.
		//	{
		//		vetor_rand.pop_back();
		//	}

		//	it = scoresrestantes.begin();

		//	for (it; it != scoresrestantes.end();it++) //Percorre o vetor auxiliar e carrega os scores que restaram no mapa.
		//	{
		//		vetor_rand.push_back(*it);
		//	}
		//}
		//else
		//{
		//	do {
		//		objscore = mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i));
		//		objscore->setPosCentro(mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getYCentro());
		//		objscore->setSprite(&sscore);

		//		vetor_rand.push_back(objscore);
		//		i++;
		//	} while (i <= 9);
		//	it = vetor_rand.begin();
		//}
		
	}
	else if (nivel == 2)
	{
		do {
			objscore = mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i));
			objscore->setPosCentro(mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getYCentro());
			objscore->setSprite(&sscore);

			vetor_rand.push_back(objscore);
			i++;
		} while (i <= 46);
		//std::vector<ObjetoTileMap*>::iterator it;

		//if (save(o_arquivo))
		//{
		//	while (!scoresrestantes.empty())//Zera vetor de scores restantes.
		//	{
		//		scoresrestantes.pop_back();
		//	}

		//	for (it; it != vetor_rand.end();it++)//Percorre e salva em um vetor auxiliar os scores que restaram no mapa.
		//	{
		//		scoresrestantes.push_back(*it);					
		//	}
		//}
		//else if (load(i_arquivo))
		//{
		//	while (!vetor_rand.empty())//Zera vetor de scores.
		//	{
		//		vetor_rand.pop_back();
		//	}

		//	it = scoresrestantes.begin();

		//	for (it; it != scoresrestantes.end();it++) //Percorre o vetor auxiliar e carrega os scores que restaram no mapa.
		//	{
		//		vetor_rand.push_back(*it);
		//	}
		//}
		//else
		//{
		//	do {
		//		objscore = mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i));
		//		objscore->setPosCentro(mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getYCentro());
		//		objscore->setSprite(&sscore);

		//		vetor_rand.push_back(objscore);
		//		i++;
		//	} while (i <= 46);

		//	it = vetor_rand.begin();
		//}
		//
	}
	else if (nivel == 3)
	{
		do {
			objscore = mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i));
			objscore->setPosCentro(mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getYCentro());
			objscore->setSprite(&sscore);

			vetor_rand.push_back(objscore);
			i++;
		} while (i <= 22);
	}
	else if (nivel == 4)
	{
		//BÔNUS STAGE
		do {
			objscore = mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i));
			objscore->setPosCentro(mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getYCentro());
			objscore->setSprite(&sscore);

			vetor_rand.push_back(objscore);
			i++;
		} while (i <= 26);
		//std::vector<ObjetoTileMap*>::iterator it;

		//if (save(o_arquivo))
		//{
		//	while (!scoresrestantes.empty())//Zera vetor de scores restantes.
		//	{
		//		scoresrestantes.pop_back();
		//	}

		//	for (it; it != vetor_rand.end();it++)//Percorre e salva em um vetor auxiliar os scores que restaram no mapa.
		//	{
		//		scoresrestantes.push_back(*it);
		//	}
		//}
		//else if (load(i_arquivo))
		//{
		//	while (!vetor_rand.empty())//Zera vetor de scores.
		//	{
		//		vetor_rand.pop_back();
		//	}

		//	it = scoresrestantes.begin();

		//	for (it; it != scoresrestantes.end();it++) //Percorre o vetor auxiliar e carrega os scores que restaram no mapa.
		//	{
		//		vetor_rand.push_back(*it);
		//	}
		//}
		//else
		//{
		//	do {
		//		objscore = mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i));
		//		objscore->setPosCentro(mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getXCentro(), mapa.getCamadaDeObjetos("Objetos")->getObjeto("Score" + std::to_string(i))->getYCentro());
		//		objscore->setSprite(&sscore);

		//		vetor_rand.push_back(objscore);
		//		i++;
		//	} while (i <= 9);
		//	it = vetor_rand.begin();
		//}
	}
	
		
	//PERSONAGEM

	personagem->setSpriteSheet("Explorador", mapa.getCamadaDeObjetos("Player")->getObjeto("Player1")); //Recebe spritesheet e objeto do mapa tile.

	//MINOTAURO

	minotauro = mapa.getCamadaDeObjetos("Inimigos")->getObjeto("Minotauro");
	minotauro->setPosCentro(mapa.getCamadaDeObjetos("Inimigos")->getObjeto("Minotauro")->getXCentro(), mapa.getCamadaDeObjetos("Inimigos")->getObjeto("Minotauro")->getYCentro());
	minotauro->setSprite(&minotaurospr);
	
	
}

//bool Jogo::save(std::ostream & os)
//{
//	if (os)
//	{  	//Sobreescrever atributos salvos.
//		estado_jogo.setVida(vida);
//		estado_jogo.setNivel(nivel);	//		
//		estado_jogo.setScore(vscore);
//		os.write(reinterpret_cast<char *>(&estado_jogo), sizeof(EstadoJogo)); 
//	}
//	else
//	{
//		return false;
//		gDebug.erro("Erro no ao salvar stream");
//	}  
//	return true;
//}
//
//bool Jogo::load(std::istream & is)
//{
//	if (is)
//	{	//Carrega atributos salvos.
//
//		is.read(reinterpret_cast<char *>(&estado_jogo), sizeof(EstadoJogo));
//
//		vida = estado_jogo.getVida();
//		nivelMapa(estado_jogo.getNivel());
//		vscore = estado_jogo.getScore(); //			   				
//	}
//	else
//	{
//		return false;
//		gDebug.erro("Erro no ao carregar stream");
//	}
//
//
//	return true;
//}
