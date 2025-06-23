#include "InimigoAlto.h"

namespace Entidades {
	namespace Personagens {

		InimigoAlto::InimigoAlto(Vector2f pos, int distpad) :
			Inimigo(nullptr, pos)
		{
			num_vidas = VIDA_ALTO;

			nivel_maldade = DANO_ALTO;
			aceleracao = ACELERACAO_ALTO;
			direcao = 1;

			posinicial = pos;

			if (distpad == 0)
				distanciapadrao = rand() % 64 + 32; // Distância aleatória entre 32 e 96 pixels
			else
				distanciapadrao = distpad;


			try {
				carregarTextura("inimigoalto.png");
				corpo.setTexture(&textura);
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				corpo.setFillColor(sf::Color::Red); // fallback color
			}
			cout << "INIMIGOALTO CRIADO" << endl;
			corpo.setSize(Vector2f(64.f, 160.f));
			centralizarEntidade();
		}
		InimigoAlto::~InimigoAlto()
		{
			cout << "destrutora InimigoAlto" << endl;
		}

		void InimigoAlto::executar()
		{
			mover();
		}

		void InimigoAlto::mover()
		{
			sofrerGravidade();

			Vector2f posAtual = corpo.getPosition();
			float distancia = posAtual.x - posinicial.x;

			if (direcao == 1 && distancia >= distanciapadrao) {
				direcao = -1;
			}
			else if (direcao == -1 && distancia <= 0.f) {
				direcao = 1;
			}

			corpo.move(aceleracao * direcao, vel.y);
		}

		int InimigoAlto::getDistanciaPadrao() const
		{
			return distanciapadrao;
		}

		void InimigoAlto::salvar(json& j)
		{
			j["distanciapadrao"] = getDistanciaPadrao();
			j["xi"] = getPosicaoInicial().x;
			j["yi"] = getPosicaoInicial().y;
			j["vida"] = getVidas();
			j["type"] = "InimigoAlto";
		}

		Vector2f InimigoAlto::getPosicaoInicial()
		{
			return posinicial;
		}

		Vector2f InimigoAlto::getPosicaoAtual()
		{
			return corpo.getPosition();
		}

	}
}