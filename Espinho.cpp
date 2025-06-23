#include "Espinho.h"
#include "Chefao.h"

using namespace Entidades;

namespace Entidades {
	namespace Obstaculos {

		Espinho::Espinho(Vector2f pos) : Obstaculo(pos), dano(1)
		{
			danoso = true;
			corpo.setSize(sf::Vector2f(32.f, 32.f));
			centralizarEntidade();
			try {
				carregarTextura("espinho.png");
				corpo.setTexture(&textura);
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				corpo.setFillColor(sf::Color::White); // fallback color
			}
		}

		Espinho::~Espinho()
		{
			
		}

		void Espinho::causarDano(Personagens::Personagem* p)
		{

			if (p != nullptr) {
				p->operator--();
			}
		}

		void Espinho::obstacular(Personagens::Personagem* p, int d)
		{
			if (!p) return;
			p->reduzPulo();

			Entidades::Personagens::Chefao* chefe = dynamic_cast<Entidades::Personagens::Chefao*>(p);
			if (chefe) {
				if (d == 4) {
					p->getVel().y = 0.f;
					p->getCorpo().setPosition(
						p->getcm().x,
						getcm().y - p->getRaio().y - getRaio().y
					);
				}
			}
			else {//nao é chefe
				causarDano(p);

				if (d == 4) {
					p->setChao(true);

					p->getVel().y = 0.f;
					p->getCorpo().setPosition(
						p->getcm().x,
						getcm().y - p->getRaio().y - getRaio().y - ELASTICIDADE_ESPINHO
					);
				}
			}
			if (d == 1) {
				p->getVel().y = 0.f;
				p->getCorpo().setPosition(
					p->getcm().x,
					getcm().y + p->getRaio().y + getRaio().y + ELASTICIDADE_ESPINHO
				);
			}
			if (d == 2) {
				p->getVel().x = 0.f;
				p->getCorpo().setPosition(
					getcm().x + p->getRaio().x + getRaio().x + ELASTICIDADE_ESPINHO,
					p->getcm().y
				);
			}
			if (d == 3) {
				p->getVel().x = 0.f;
				p->getCorpo().setPosition(
					getcm().x - p->getRaio().x - getRaio().x - ELASTICIDADE_ESPINHO,
					p->getcm().y
				);
			}
		}

		void Espinho::executar() {

		}
		void Espinho::salvar(json& j)
		{
			j["type"] = "Espinho";
		}
	}
}