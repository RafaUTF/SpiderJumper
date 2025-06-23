#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <set>

#include "Jogador.h"
#include "Inimigo.h"
#include "Projetil.h"
#include "Obstaculo.h"
#include "Espinho.h"

namespace Gerenciadores {

	class Gerenciador_Colisoes {//chamar todas essas funcoes no executar();

	private:
		
		vector<Entidades::Personagens::Inimigo*> LIs;
		list<Entidades::Obstaculos::Obstaculo*> LOs;
		set<Entidades::Projetil*> LPs;

		vector<Entidades::Personagens::Jogador*> LJs;

		Gerenciador_Colisoes();//privada

		const int verificarDirecao(Entidades::Entidade* pe1 = nullptr, Entidades::Entidade* pe2 = nullptr) const;

		void tratarColisoesJogs();
		void tratarColisoesJogsObstacs();
		void tratarColisoesJogsInimgs();
		void tratarColisoesJogsProjeteis();

		void tratarColisoesInimgsObstacs();
		void tratarColisoesInimgsProjeteis();
		void tratarColisoesInimgsInimgs();

		void tratarColisoesProjeteisObstacs();
	public:
		static Gerenciador_Colisoes* getInstancia();
		~Gerenciador_Colisoes();
		void executar();
		void retirarProjeteis();
		void retirarPersonagens();

		void incluirInimigo(Entidades::Personagens::Inimigo* pi = NULL);
		void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po = NULL);
		void incluirProjetil(Entidades::Projetil* pj = NULL);
		void incluirJogador(Entidades::Personagens::Jogador* pjog = NULL);

		void removerEntidade(Entidades::Entidade* pE);

		set<Entidades::Projetil*>& getProjeteis();

		void limpaLista();


	};
}