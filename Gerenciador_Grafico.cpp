#include "Gerenciador_Grafico.h"
#include "Ente.h"
#include "Entidade.h"

using namespace Entidades;

namespace Gerenciadores {

	Gerenciador_Grafico::Gerenciador_Grafico() :
		janela(new sf::RenderWindow(sf::VideoMode(LARGURA_TELA, ALTURA_TELA), "janela", Style::Default)),
		fundo(),
		camera(sf::FloatRect(0, 0, static_cast<int>(LARGURA_TELA), static_cast<int>(ALTURA_TELA)))
	{
		cout << "Gerenciador_Grafico criado" << endl;
		janela->setFramerateLimit(FPS);

		/*
		try {
			if (!textura.loadFromFile("fundo.png")) {
				throw std::runtime_error("Erro ao carregar a textura FUNDO!");
			}
			fundo.setTexture(textura);
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}*/

		fundo.setPosition(0.f, 0.f);
		fundo.scale(1.5f, 1.5f);
	}
	void Gerenciador_Grafico::setFundo(const std::string& caminho)
	{
		try {
			if (!textura.loadFromFile(caminho)) {
				throw std::runtime_error("Erro ao carregar a textura FUNDO!");
			}
			fundo.setTexture(textura);
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	Gerenciador_Grafico::~Gerenciador_Grafico()
	{
		cout << "destrutora Gerenciador_Grafico" << endl;

	}

	void Gerenciador_Grafico::desenhar(Ente* pE)
	{
		if (pE == nullptr) {
			cout << "nao foi possivel desenhar o ente NULO" << endl;
			return;
		}
		janela->draw(pE->getCorpo());
	}

	void Gerenciador_Grafico::desenhar(const RectangleShape& retangulo)
	{
		janela->draw(retangulo);
	}

	void Gerenciador_Grafico::desenhaFundo()
	{
		janela->draw(fundo);
	}

	void Gerenciador_Grafico::mostrar()
	{
		janela->display();
	}

	void Gerenciador_Grafico::fechar()
	{
		janela->close();
	}

	void Gerenciador_Grafico::moverCamera(sf::Text* t, Entidades::Entidade* p1, Entidades::Entidade* p2)
	{
		float larguraJanela = camera.getSize().x;
		float larguraCenario = TAMANHOTOTALLATERAL;

		float centroX = 0;
		if (p2 && p1) {
			centroX = (p1->getcm().x + p2->getcm().x) / 2.f;
		}
		else if (p1) {
			centroX = p1->getcm().x;
		}
		else {//p2
			centroX = p2->getcm().x;
		}

		float minCentro = larguraJanela / 2.f;
		float maxCentro = larguraCenario - larguraJanela / 2.f;

		if (centroX < minCentro)
			centroX = minCentro;
		if (centroX > maxCentro)
			centroX = maxCentro;

		camera.setCenter(Vector2f(centroX, ALTURA_TELA / 2.f));
		janela->setView(camera);
		if(t)
			t->setPosition(camera.getCenter()-Vector2f(LARGURA_TELA/2 - 20.f,ALTURA_TELA/2 - 10.f)); // Move o texto para acompanhar a câmera	
	}

	


	Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() {
		static Gerenciador_Grafico instancia;
		return &instancia;
	}

	sf::RenderWindow* Gerenciador_Grafico::getWindow()
	{
		return janela;
	}

	const bool Gerenciador_Grafico::aberta() const
	{
		return janela->isOpen();
	}

	void Gerenciador_Grafico::clear()
	{
		janela->clear();
	}
	void Gerenciador_Grafico::setJanelaExterna(sf::RenderWindow* j) {
		if (j) {
			delete janela;
			janela = j;
		}
	}

	
}