#pragma once
#include "stdafx.h"
#include "Gerenciador_Grafico.h"

class Ente
{
protected:
	static int cont;
	int id;
	static Gerenciadores::Gerenciador_Grafico* pGG;
	RectangleShape corpo;
	Texture textura;

public:
	Ente();
	virtual ~Ente();
	static void setpGG(Gerenciadores::Gerenciador_Grafico* p);

	void desenhar(Ente* pE=nullptr);

	RectangleShape& getCorpo();

	void carregarTextura(const std::string& caminho);

};
