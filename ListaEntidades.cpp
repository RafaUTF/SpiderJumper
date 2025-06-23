#include "ListaEntidades.h"


using namespace Entidades;

namespace Listas {

	ListaEntidades::ListaEntidades() : LEs(), it()
	{
		LEs.clear();
		primeiro();
	}

	ListaEntidades::~ListaEntidades()
	{
		cout << "destrutora ListaEntidades" << endl;
		limpar();
		
	}

	void ListaEntidades::incluir(Entidades::Entidade* pE)
	{
		if (pE)
			LEs.push_back(pE);
		else
			cout << "ponteiro nulo nao inserido" << endl;
	}

	void ListaEntidades::percorrer() {
		for (Lista<Entidades::Entidade*>::iterator it = LEs.begin(); it != LEs.end(); ++it) {
			if (*it && *it != nullptr) { // Check for NULL and invalid pointers
				(*it)->executar();
			}
		}
	}

	void ListaEntidades::desenhar()
	{
		for (Lista<Entidades::Entidade*>::iterator it = LEs.begin(); it != LEs.end(); ++it) {
			if (*it) {
				(*it)->desenhar(static_cast<Ente*>(*it));
			}
		}
	}

	Entidades::Entidade* ListaEntidades::getAtual()
	{
		return *it;
	}

	void ListaEntidades::primeiro()
	{
		it = LEs.begin();
	}

	bool ListaEntidades::fim()
	{
		return it == LEs.end();
	}

	void ListaEntidades::operator++()
	{
		if (fim())
			cout << "Passou do final de LEs em ListaEntidades!" << endl;
		else
			++it;
	}

	void ListaEntidades::retirar(Entidades::Entidade* pE)
	{
		if (pE == NULL) {
			cout << "ponteiro nulo nao retirado" << endl;
			return;
		}
		Lista<Entidades::Entidade*>::iterator anterior = it;
		++it;//gambiarra para quando deletar percorrendo a lista o it fique na posicao certa
		if (LEs.remove(pE)) {
			cout << "ponteiro retirado do LEs" << endl;

		}
		else {
			cout << "ponteiro nao encontrado em LEs(nao retirado)" << endl;
			it = anterior;

		}
	}

	void ListaEntidades::limpar()
	{
		for (Lista<Entidades::Entidade*>::iterator it = LEs.begin(); it != LEs.end(); ++it) {
			if (*it) {
				delete* it;
				*it = NULL;
			}
		}
		LEs.clear();
	}

}