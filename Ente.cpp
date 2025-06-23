#include "Ente.h"

using namespace Gerenciadores;

int Ente::cont(0);
Gerenciadores::Gerenciador_Grafico* Ente::pGG(0);

Ente::Ente() :id(cont++), corpo(Vector2f(200.f, 200.f)) {
	
}

Ente::~Ente()
{
}

void Ente::setpGG(Gerenciadores::Gerenciador_Grafico* p)
{
	pGG = p;
}

void Ente::desenhar(Ente* pE)
{
	if (pE == NULL) {
		cout << "falha ao desenhar ente" << endl;
		return;
	}
	pGG->desenhar(this);

}

RectangleShape& Ente::getCorpo()
{
	return corpo;
}

void Ente::carregarTextura(const std::string& caminho)
{
	if (!textura.loadFromFile(caminho)) {
		throw std::runtime_error("Erro ao carregar a imagem: " + caminho);
	}
}
