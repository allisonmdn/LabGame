#include<iostream>
#include <fstream>
#include <string>
#include "libUnicornio.h"

#pragma once
class CarregadorAssets
{
public:
	CarregadorAssets();
	~CarregadorAssets();
	bool Carregador(std::fstream & f_arquivos_rec);

private:
	int n_assets;
	
};

