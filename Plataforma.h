#pragma once
#include "Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {

		class Plataforma : public Obstaculo
		{
		private:

			float deslocamento; 

		public:
			Plataforma(Vector2f pos = (Vector2f(0.f, 0.f)), float desloc = 0);
			~Plataforma();
			void executar();
			void obstacular(Personagens::Personagem* p = nullptr, int d = 0);

			float getDeslocamento() const;

			void salvar(json& j);
		};
	}
}