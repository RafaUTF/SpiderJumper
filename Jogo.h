#pragma once
#include "Fase1.h"
#include "Fase2.h"

#include "MenuInicial.h"
class Jogo {
private:
	MenuInicial menu;

	Fases::Fase1* pF1;
	Fases::Fase2* pF2;

	Gerenciadores::Gerenciador_Grafico* GG;
	Gerenciadores::Gerenciador_Colisoes* GC;

	int fase;
	int nJogs;


	void executarFase();
	void executar();
	Fases::Fase* getFase();
	void mudarParaFase2(const std::string& caminho);

	void sementear();

public:
	Jogo();
	~Jogo();
	
};