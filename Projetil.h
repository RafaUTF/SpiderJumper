#pragma once
//#include "Personagem.h"
#include "ListaEntidades.h"

namespace Entidades {
	namespace Personagens {
		class Jogador;
		class Personagem;
		class Chefao;
		class InimigoAlto;
		class InimigoPequeno;
	}
}

namespace Entidades {
	class Projetil : public Entidade
	{
	protected:
		bool ativo;
		Listas::ListaEntidades* lista;
		unsigned long long duracao;

		Entidades::Personagens::Jogador* pDono;
	public:
		//sobrecarga construtora
		//quando eh criada:
		Projetil(Vector2f pos = (Vector2f(0.f, 0.f)), bool dir = true, float raio = 0.f,
			Listas::ListaEntidades* pl = nullptr,
			Entidades::Personagens::Jogador* pdono = nullptr, short int f = 0);
		//quando eh carregada:
		Projetil(Vector2f pos = (Vector2f(0.f, 0.f)), Vector2f v = (Vector2f(0.f, 0.f)), 
			Entidades::Personagens::Jogador* pdono = nullptr);
		~Projetil();
		void executar();
		
		const bool getAtivo();

		//quando explode um personagem
		void explodir(Personagens::Personagem* pp);
		//quando explode em um obstaculo
		void explodir();

		Vector2f getVelocidade();
		void setVelocidade(Vector2f v);
		void setDono(Entidades::Personagens::Jogador* pdono);

		void salvar(json& j);
	};
}