#pragma once
#include "Lista.h"
#include "Entidade.h"

namespace Listas {

	class ListaEntidades {
	private:
		Lista<Entidades::Entidade*> LEs;
		Lista<Entidades::Entidade*>::iterator it;

	public:
		ListaEntidades();
		~ListaEntidades();
		void incluir(Entidades::Entidade* pE = NULL);
		void percorrer();

		void desenhar();

		Entidades::Entidade* getAtual();
		void primeiro();
		bool fim();
		void operator++();

		void retirar(Entidades::Entidade* pE = NULL);

		void limpar();
	};

}