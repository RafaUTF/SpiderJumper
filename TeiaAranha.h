#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {
	namespace Obstaculos {

		class TeiaAranha : public Obstaculo
		{
		private:
			float reducao;

		public:
			TeiaAranha(Vector2f pos = (Vector2f(0.f, 0.f)), float redux = 0);
			~TeiaAranha();
			void obstacular(Personagens::Personagem* p = nullptr, int d = 0);
			void executar();

			float getReducao() const;

			void salvar(json& j);
		};
	}
}