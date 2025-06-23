#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class InimigoAlto : public Inimigo
		{
		private:
			Vector2f posinicial;
			int direcao;

			int distanciapadrao;

			void mover();
		public:
			InimigoAlto(Vector2f pos = (Vector2f(100.f, 100.f)), int distpad = 0);
			~InimigoAlto();
			void executar();
			Vector2f getPosicaoInicial();
			Vector2f getPosicaoAtual();

			int getDistanciaPadrao() const;

			void salvar(json& j);
		};

	}
}