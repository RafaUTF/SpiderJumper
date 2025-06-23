#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class InimigoPequeno : public Inimigo
		{
		private:
			Vector2f posinicial;
			int direcao;

			float aceleracaoextra;

			void mover();
		public:
			InimigoPequeno(Vector2f pos = (Vector2f(100.f, 100.f)), float acelex = 0);
			~InimigoPequeno();
			void executar();
			Vector2f getPosicaoInicial();
			Vector2f getPosicaoAtual();

			float getAceleracaoExtra() const;

			void salvar(json& j);
		};

	}
}