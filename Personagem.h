#pragma once
#include "Entidade.h"
#include "ListaEntidades.h"
#include "Projetil.h"

namespace Entidades {
	namespace Personagens {

		class Personagem : public Entidade
		{
		protected:
			int num_vidas;
			float aceleracao;

			Listas::ListaEntidades* tiros;

			int recarga;

			bool comChao;

			bool olhandoDir;

			float forca_pulo;

			virtual void mover()=0;

			void sofrerGravidade();
		public:
			Personagem(Listas::ListaEntidades* t = nullptr, Vector2f pos = (Vector2f(0.f, 0.f)));
			~Personagem();

			virtual void executar() = 0;

			void setChao(bool b);

			void reduzVelocidade(float fator);
			void restaurarVelocidade();

			void operator--();
			void operator-=(int dano);

			const int getVidas() const;
			void setVida(int v);

			void colidir(Entidade* pe = nullptr, int d = 0);

			virtual void zerarPulo();

			void reduzPulo(float fator = 0.5f);

			virtual void salvar(json& j)=0;
		};

	}
}