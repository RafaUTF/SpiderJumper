#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {
	namespace Obstaculos {

		class Espinho : public Obstaculo
		{
		private:
			int dano;
		public:
			Espinho(Vector2f pos = (Vector2f(0.f, 0.f)));
			~Espinho();
			void causarDano(Personagens::Personagem* p);
			void obstacular(Personagens::Personagem* p = nullptr, int d = 0);
			void executar();
			void salvar(json& j);
		};
	}
}