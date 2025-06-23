#pragma once
#include "Entidade.h"
#include "Jogador.h"
#include <string>
namespace Entidades {
	namespace Obstaculos {

		class Obstaculo : public Entidade
		{
		protected:
			bool danoso;
		public:
			Obstaculo(Vector2f pos = (Vector2f(0.f, 0.f)));
			~Obstaculo();
			bool isDanoso() const;
			virtual void executar() = 0;
			virtual void obstacular(Personagens::Personagem* p = nullptr, int d = 0) = 0;

			virtual void salvar(json& j)=0;
		};
	}
}