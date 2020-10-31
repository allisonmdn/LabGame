#include "CarregadorAssets.h"



CarregadorAssets::CarregadorAssets()
{
}


CarregadorAssets::~CarregadorAssets()
{
}

bool CarregadorAssets::Carregador(std::fstream & f_arquivos_rec)
{
	bool b_loader_status = true;
	std::string def_resource_type;
	std::string def_resource_name;
	std::string def_resource_local;
	std::string::size_type size;


	//sprite_sheets
	std::string def_n_animations; 
	std::string def_n_max_frames;

	//sounds
	std::string vol;

	//font
	std::string tamanho;
	//std::string estilo;
	//std::string glifoPrim;
	//std::string glifoUlt;
	//std::string qualidadeEscala;

	vector<std::string> tipo_lista;

	
	
	if (f_arquivos_rec)
	{
		//char q_resources = f_arquivos_rec.get();
		//this->n_assets = q_resources - '0';
		//gDebug.depurar("num_Recursos", this->n_assets);
		
		
		while (!f_arquivos_rec.eof())//Repetição para carregar arquivos. 		
		{
			if (!f_arquivos_rec.fail())	 			
			{
				
						
				f_arquivos_rec >> def_resource_type;// >> def_resource_name >> def_resource_local >> def_n_animations >> def_n_max_frames;

				        //SPRITE SHEET BEGIN

				

				if (def_resource_type == "sprite_sheet")
				{
					f_arquivos_rec >> def_resource_name >> def_resource_local >> def_n_animations >> def_n_max_frames;

					
					if (f_arquivos_rec.fail())
					{
						gDebug.depurar("Erro", f_arquivos_rec.fail());
						gDebug.depurar("tipo_do_recurso", def_resource_type);
						gDebug.depurar("nome_do_recurso", def_resource_name);
						gDebug.depurar("caminho_do_recurso", def_resource_local);
						gDebug.depurar("numero_animacoes", def_n_animations);
						gDebug.depurar("n_max_frames", def_n_max_frames);
					}
					
					gRecursos.carregarSpriteSheet(def_resource_name, def_resource_local, std::stoi(def_n_animations, &size), std::stoi(def_n_max_frames, &size), QUALIDADE_ESCALA_BAIXA);
					
					
					if (!gRecursos.carregouSpriteSheet(def_resource_name))
					{
						gDebug.erro("Erro ao carregar recursos (Sprite Sheets)"); 
						return false;
					} 
				}
				   
						     //SPRITE SHEET END

						       //SOUNDS BEGIN
				else if (def_resource_type == "sound") 
				{
					f_arquivos_rec >> def_resource_name >> def_resource_local;


					if (f_arquivos_rec.fail())	
					{								 
						gDebug.depurar("Erro", f_arquivos_rec.fail());
						gDebug.depurar("tipo_do_recurso", def_resource_type);
						gDebug.depurar("nome_do_recurso", def_resource_name);
						gDebug.depurar("caminho_do_recurso", def_resource_local);
					}
					
					gRecursos.carregarAudio(def_resource_name, def_resource_local);
					
					if (!gRecursos.carregouAudio(def_resource_name))					
					{																	
						gDebug.erro("Erro ao carregar recursos (Sounds)");
						
						return false;
					}
				}
						         //SOUNDS END

					              //MUSIC BEGIN
				  
				else if (def_resource_type == "music")
				{
					f_arquivos_rec >> def_resource_name >> def_resource_local >> vol;
										

					if (f_arquivos_rec.fail())
					{
						gDebug.depurar("Erro", f_arquivos_rec.fail());
						gDebug.depurar("tipo_do_recurso", def_resource_type);
						gDebug.depurar("nome_do_recurso", def_resource_name);
						gDebug.depurar("caminho_do_recurso", def_resource_local);
					}
					
					gRecursos.carregarMusica(def_resource_name, def_resource_local, stof(vol, &size));
					
					
					if (!gRecursos.carregouMusica(def_resource_name))
					{
						gDebug.erro("Erro ao carregar recursos (Music_Background)");
						
						return false;
					}
				}
						             //MUSIC END

						             //FONT BEGIN	  
				else if (def_resource_type == "font")
				{
					f_arquivos_rec >> def_resource_name >> def_resource_local >> tamanho;


					if (f_arquivos_rec.fail())
					{
						gDebug.depurar("Erro", f_arquivos_rec.fail());
						gDebug.depurar("tipo_do_recurso", def_resource_type);
						gDebug.depurar("nome_do_recurso", def_resource_name);
						gDebug.depurar("caminho_do_recurso", def_resource_local);
					}
					
					gRecursos.carregarFonte(def_resource_name, def_resource_local, 16 , 0, 0, 255, QUALIDADE_ESCALA_BAIXA); //std::stoi(tamanho, &size), 0, 0, 255, QUALIDADE_ESCALA_BAIXA);
					
					//tamanho padrão = 16.
					//estilo padrão = 0.
					//glifos padrãoPrim = 0.
					//glifos padrãoUlt = 255.
					//qualidade escala padrão = QUALIDADE_ESCALA_BAIXA == 0.
					if (!gRecursos.carregouFonte(def_resource_name))
					{
						gDebug.erro("Erro ao carregar recursos (Font)");
						return false;
					}
				}
						                //FONT END
			}
			
        }							 
		return true;
	}
	
}
