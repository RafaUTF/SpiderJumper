#pragma once
#include "Personagem.h" 

namespace Entidades {
	namespace Personagens {

		class Jogador : public Personagem
		{
		protected:
			int pontos;
			bool j1;//flag principal
			static bool jogador1;//flag temporaria
			void mover();
			void atirar();
		public:
			Jogador(Listas::ListaEntidades* t = nullptr, Vector2f pos = (Vector2f(0.f, 0.f)));
			~Jogador();
			void executar();
			void colidirJog(Jogador* p = nullptr, int d = 0);
			const int getPontos() const;
			void operator+=(const int n);
			void operator++();
			void salvar(json& j);
			static void reiniciarJogs();

		};


	}
}