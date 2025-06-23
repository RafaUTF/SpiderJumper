#include "TeiaAranha.h"

using namespace Entidades::Personagens;

namespace Entidades {
	namespace Obstaculos {

		TeiaAranha::TeiaAranha(Vector2f pos, float redux) :
			Obstaculo(pos), reducao(redux)
		{
			danoso = false;

			if (reducao == 0)
				reducao = 0.05 + (rand() % 10) / 10.f;

			cout << "teia com reducao: " << reducao << endl;

			corpo.setSize(sf::Vector2f(32.f, 32.f));
			centralizarEntidade();
			try {
				carregarTextura("teiaaranha.png");
				corpo.setTexture(&textura);
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				corpo.setFillColor(sf::Color::White); // fallback color
			}
		}

		TeiaAranha::~TeiaAranha()
		{
			cout << "destrutora teia" << endl;
		}


		void TeiaAranha::obstacular(Entidades::Personagens::Personagem* p, int d)
		{
			if (!p) return;

			p->reduzVelocidade(reducao);
			p->reduzPulo();
			if (d == 1) {
				p->getVel().y = 0.f;
				p->getCorpo().setPosition(
					p->getcm().x,
					getcm().y + p->getRaio().y + getRaio().y
				);
			}
			if (d == 4) {
				p->setChao(true);
				p->getVel().y = 0.f;
				p->getCorpo().setPosition(
					p->getcm().x,
					getcm().y - p->getRaio().y - getRaio().y
				);
			}
			if (d == 2) {
				p->getVel().x = 0.f;
				p->getCorpo().setPosition(
					getcm().x + p->getRaio().x + getRaio().x,
					p->getcm().y
				);
			}
			if (d == 3) {
				p->getVel().x = 0.f;
				p->getCorpo().setPosition(
					getcm().x - p->getRaio().x - getRaio().x,
					p->getcm().y
				);
			}
		}

		void TeiaAranha::executar() {

		}
		float TeiaAranha::getReducao() const
		{
			return reducao;
		}
		void TeiaAranha::salvar(json& j)
		{
			j["type"] = "TeiaAranha";
			j["reducao"] = getReducao();
		}
	}
}