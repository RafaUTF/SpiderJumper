#pragma once
#include "Inimigo.h"

namespace Entidades {

	namespace Personagens {

		class Chefao : public Inimigo
		{
		private:
			short int forca;
			void mover();
			void atirar();
		public:
			//sobrecarga construtora
			//quando eh criada:
			Chefao(Listas::ListaEntidades* t, Jogador* pp1 = nullptr, Jogador* pp2 = nullptr,
				Vector2f pos = (Vector2f(100.f, 100.f)));
			//quando eh carregada:
			Chefao(Listas::ListaEntidades* t, Jogador* pp1, Jogador* pp2,
				Vector2f pos, short int f, int vida);
			~Chefao();

			void executar();

			const short int getForca() const;

			void salvar(json& j);
		};

	}
}