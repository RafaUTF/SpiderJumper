#include "Plataforma.h"

using namespace Entidades::Personagens;

namespace Entidades {
	namespace Obstaculos {

		Plataforma::Plataforma(Vector2f pos, float desloc) : Obstaculo(Vector2f(pos.x, pos.y + desloc)), deslocamento(desloc)
		{
			corpo.setSize(Vector2f(32.f, 32.f));
			centralizarEntidade();
			try {
				carregarTextura("Plataforma.png");
				corpo.setTexture(&textura);
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				corpo.setFillColor(sf::Color::Yellow); // fallback color
			}
			
		}


		Plataforma::~Plataforma() {
			
		}

		void Plataforma::executar()
		{
		}

		void Plataforma::obstacular(Personagens::Personagem* p, int d)
		{
			if (!p) return;

			if (d == 1) {
				p->getVel().y = 0.f;
				p->getCorpo().setPosition(
					p->getcm().x,
					getcm().y + p->getRaio().y + getRaio().y
				);
			}
			if (d == 4) {
				p->setChao(true);
				p->zerarPulo();

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
		float Plataforma::getDeslocamento() const
		{
			return deslocamento;
		}
		void Plataforma::salvar(json& j)
		{
			j["type"] = "Plataforma";
			j["deslocamento"] = getDeslocamento();
		}
	}
}