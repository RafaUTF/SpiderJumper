#include "InimigoPequeno.h"

namespace Entidades {
	namespace Personagens {

		InimigoPequeno::InimigoPequeno(Vector2f pos, float acelex) :
			Inimigo(nullptr, pos)
		{

			num_vidas = VIDA_BAIXO;

			if (acelex == 0)
				aceleracaoextra = (rand() % 50);
			else
				aceleracaoextra = acelex;

			nivel_maldade = DANO_BAIXO;
			aceleracao = ACELERACAO_BAIXO * aceleracaoextra;

			cout << "InimigoPequeno criado com aceleracao: " << aceleracao << endl;
			direcao = 1;



			posinicial = pos;


			try {
				carregarTextura("inimigopequeno.png");
				corpo.setTexture(&textura);
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				corpo.setFillColor(sf::Color::Red); // fallback color
			}
			cout << "INIMIGOPEQUENO CRIADO" << endl;
			corpo.setSize(Vector2f(64.f, 64.f));
			centralizarEntidade();
		}
		InimigoPequeno::~InimigoPequeno()
		{
			cout << "destrutora InimigoPequeno" << endl;
		}

		void InimigoPequeno::executar()
		{
			mover();

		}

		void InimigoPequeno::mover()
		{
			sofrerGravidade();

			Vector2f posAtual = corpo.getPosition();
			float distancia = posAtual.x - posinicial.x;

			if (direcao == 1 && distancia >= 96.f) {
				direcao = -1;
			}
			else if (direcao == -1 && distancia <= 0.f) {
				direcao = 1;
			}

			corpo.move(aceleracao * direcao, 0.f);
		}

		float InimigoPequeno::getAceleracaoExtra() const
		{
			return aceleracaoextra;
		}

		void InimigoPequeno::salvar(json& j)
		{
			j["aceleracaoextra"] = getAceleracaoExtra();
			j["xi"] = getPosicaoInicial().x;
			j["yi"] = getPosicaoInicial().y;
			j["vida"] = getVidas();
			j["type"] = "InimigoPequeno";
		}

		Vector2f InimigoPequeno::getPosicaoInicial()
		{
			return posinicial;
		}

		Vector2f InimigoPequeno::getPosicaoAtual()
		{
			return corpo.getPosition();
		}

	}
}