#pragma once
#include "Personagem.h"

#include "Jogador.h"


namespace Entidades {
	namespace Personagens {

		class Inimigo : public Personagem
		{
		protected:
			int nivel_maldade;
			bool chefao;
			Jogador* p1;
			Jogador* p2;
			Jogador* pAlvo;
			virtual void mover() = 0;

			void escolherAlvo();
			void perseguir();

			void zerarPulo();
		public:
			Inimigo(Listas::ListaEntidades* t, Vector2f pos = (Vector2f(100.f, 100.f)));
			~Inimigo();
			virtual void executar()=0;
			virtual void danificar(Jogador* p = nullptr, int d = 0);
			void colidirInim(Inimigo* p = nullptr, int d = 0);
			virtual void salvar(json& j) = 0;
		};

	}
}