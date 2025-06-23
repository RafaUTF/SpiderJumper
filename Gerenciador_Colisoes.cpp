#include "Gerenciador_Colisoes.h"
#include "Chefao.h"
#include "InimigoAlto.h"
#include "InimigoPequeno.h"

using namespace Entidades;
using namespace Obstaculos;
using namespace Personagens;

float modulo(float x) {
	return x < 0 ? (-1.f) * x : x;
}

namespace Gerenciadores {


	Gerenciador_Colisoes* Gerenciador_Colisoes::getInstancia()
	{
		static Gerenciador_Colisoes instancia;
		return &instancia;
	}

	void Gerenciador_Colisoes::retirarProjeteis()
	{
		set<Projetil*>::iterator it = LPs.begin();
		while (it != LPs.end()) {
			if (*it && (*it)->getAtivo() == false) {
				it = LPs.erase(it);
				cout << "projetil retirado Gerenciador_Colisoes" << endl;
			}
			else
				it++;
		}
	}

	void Gerenciador_Colisoes::retirarPersonagens()
	{
		vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin();
		while (it != LIs.end()) {
			if (*it && (*it)->getVidas() == 0) {
				it = LIs.erase(it);
				cout << "INIMIGO retirado Gerenciador_Colisoes" << endl;
			}
			else
				it++;
		}

		vector<Entidades::Personagens::Jogador*>::iterator it2 = LJs.begin();
		while (it2 != LJs.end()) {
			if (*it2 && (*it2)->getVidas() == 0) {
				it2 = LJs.erase(it2);
				cout << "JOGADOR retirado Gerenciador_Colisoes" << endl;
			}
			else
				it2++;
		}
	}

	Gerenciador_Colisoes::Gerenciador_Colisoes() :
		LIs(), LOs(), LPs(), LJs()
	{
		LIs.clear();
		LOs.clear();
		LPs.clear();

		LJs.clear();

		cout << "Gerenciador_Colisoes criado" << endl;
	}
	Gerenciador_Colisoes::~Gerenciador_Colisoes()
	{
		//passar deletando tudo dentro das listas
		LIs.clear();
		LOs.clear();
		LPs.clear();
		LJs.clear();

		cout << "destrutora Gerenciador_Colisoes" << endl;
	}

	void Gerenciador_Colisoes::executar() {

		for (vector<Entidades::Personagens::Jogador*>::iterator it = LJs.begin(); it != LJs.end(); it++) {
			if (*it)
				(*it)->setChao(false);
		}
		for (vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end(); it++) {
			if (*it)
				(*it)->setChao(false);
		}

		tratarColisoesProjeteisObstacs();

		//inimigos
		tratarColisoesInimgsProjeteis();
		tratarColisoesInimgsInimgs();
		tratarColisoesInimgsObstacs();

		//jogadores
		if (LJs.size() > 1) {
			tratarColisoesJogs();
		}
		tratarColisoesJogsProjeteis();
		tratarColisoesJogsInimgs();
		tratarColisoesJogsObstacs();

	}


	const int Gerenciador_Colisoes::verificarDirecao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const
	{
		if (pe1 == NULL) {
			cout << "pe1 nulo" << endl;
			return 0;
		}
		if (pe2 == NULL) {
			cout << "pe2 nulo" << endl;
			return 0;
		}
		float dx = pe2->getcm().x - pe1->getcm().x,//+ -> colisao dir do pe1
			dy = pe2->getcm().y - pe1->getcm().y,//+ -> colisao em baixo do pe1
			drx = pe1->getRaio().x + pe2->getRaio().x,
			dry = pe1->getRaio().y + pe2->getRaio().y;
		if (modulo(dx) < drx && modulo(dy) < dry) {
			if (drx - modulo(dx) < dry - modulo(dy)) {//colisao lado
				if (dx > 0)//dir pe1
					return 3;
				else//esq pe1
					return 2;
			}
			else {//colisao vertical
				if (dy > 0)//baixo pe1
					return 4;
				else//cima pe1
					return 1;
			}
		}
		return 0;
	}

	//empurra
	void Gerenciador_Colisoes::tratarColisoesJogs() {

		Entidades::Personagens::Jogador* p1 = LJs[0];
		Entidades::Personagens::Jogador* p2 = LJs[1];
		int d = verificarDirecao(p1, p2);
		if (d != 0) {
			p1->colidirJog(p2, d);

		}
	}

	void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
		//CHAMAR OBSTACULAR PARA PARAR O JOGADOR

		Obstaculos::Obstaculo* po = NULL;
		Entidades::Personagens::Jogador* pJog1 = NULL;
		int d = 0;
		for (int i = 0; i < LJs.size(); i++) {
			pJog1 = LJs[i];
			pJog1->restaurarVelocidade();
			for (list<Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); it++) {
				po = *it;
				d = verificarDirecao(pJog1, po);
				if (d != 0) {
					po->obstacular(pJog1, d);//4 -> setChao(true);
				}
			}

		}

	}

	void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
		Entidades::Personagens::Inimigo* pi = nullptr;
		Entidades::Personagens::Jogador* pJog = nullptr;
		int d = 0;
		for (int i = 0; i < LJs.size(); i++) {
			pJog = LJs[i];
			for (vector<Entidades::Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end(); it++) {
				pi = *it;
				d = verificarDirecao(pJog, pi);
				if (d != 0) {
					if (d == 4) {//neutraliza o inimigo
						pJog->getVel().y = 0.f;
						pJog->getCorpo().setPosition(
							pJog->getcm().x,
							pi->getcm().y - pJog->getRaio().y - pi->getRaio().y - ELASTICIDADE_INIMIGO
						);
						pi->setVida(0);
						if (dynamic_cast<Chefao*>(pi))
							pJog->operator+=(PREMIO_CHEFE);
						else if (dynamic_cast<InimigoAlto*>(pi))
							pJog->operator+=(PREMIO_ALTO);
						else if (dynamic_cast<InimigoPequeno*>(pi))
							pJog->operator+=(PREMIO_BAIXO);
						else
							pJog->operator++();
						pJog->setChao(true);
						pJog->reduzPulo();

					}
					else {
						pi->danificar(pJog, d);
					}
				}
			}

		}
	}





	void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
		Projetil* pj = nullptr;
		Entidades::Personagens::Jogador* pJog1 = nullptr;
		int d = 0;
		for (int i = 0; i < LJs.size(); i++) {
			pJog1 = LJs[i];

			for (set<Projetil*>::iterator it = LPs.begin(); it != LPs.end(); it++) {
				pj = *it;
				d = verificarDirecao(pJog1, pj);
				if (d != 0) {
					pj->explodir(pJog1);
					pJog1->colidir(pj, d);

				}
			}

		}

	}

	void Gerenciador_Colisoes::tratarColisoesInimgsObstacs()
	{
		//CHAMAR OBSTACULAR PARA PARAR O INIMIGO

		Obstaculos::Obstaculo* po = NULL;
		Entidades::Personagens::Inimigo* pJog1 = NULL;
		int d = 0;
		for (int i = 0; i < LIs.size(); i++) {
			pJog1 = LIs[i];
			pJog1->restaurarVelocidade();
			for (list<Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); it++) {
				po = *it;
				d = verificarDirecao(pJog1, po);
				if (d != 0) {
					po->obstacular(pJog1, d);
				}
			}

		}
	}

	void Gerenciador_Colisoes::tratarColisoesInimgsProjeteis()
	{
		Projetil* pj = NULL;
		Entidades::Personagens::Inimigo* pJog1 = NULL;
		int d = 0;
		for (int i = 0; i < LIs.size(); i++) {
			pJog1 = LIs[i];

			for (set<Projetil*>::iterator it = LPs.begin(); it != LPs.end(); it++) {
				pj = *it;
				d = verificarDirecao(pJog1, pj);
				if (d != 0) {
					pj->explodir(pJog1);
					pJog1->colidir(pj, d);
				}
			}

		}
	}

	void Gerenciador_Colisoes::tratarColisoesInimgsInimgs()
	{
		int d = 0;
		for (int i = 0; i < LIs.size(); i++) {
			for (int j = 1; j < LIs.size(); j++) {
				if (i != j && LIs[i] && LIs[j]) {
					d = verificarDirecao(LIs[i], LIs[j]);
					if (d != 0)
						LIs[i]->colidirInim(LIs[j], d);
				}
			}
		}
	}

	void Gerenciador_Colisoes::tratarColisoesProjeteisObstacs()
	{

		Obstaculos::Obstaculo* po = NULL;
		Projetil* pj = NULL;
		int d = 0;
		for (set<Projetil*>::iterator it = LPs.begin(); it != LPs.end(); it++) {
			pj = *it;
			for (list<Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); it++) {
				po = *it;
				d = verificarDirecao(pj, po);
				if (d != 0) {
					pj->explodir();
				}
			}

		}
	}

	void Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo* pi) {
		if (pi)
			LIs.push_back(pi);
		else
			cout << "ponteiro inimigo nulo nao incluido no vector" << endl;
	}

	void Gerenciador_Colisoes::incluirObstaculo(Obstaculos::Obstaculo* po) {
		if (po)
			LOs.push_back(po);
		else
			cout << "ponteiro obstaculo nulo nao incluido no list" << endl;
	}

	void Gerenciador_Colisoes::incluirProjetil(Projetil* pj) {
		if (pj)
			LPs.insert(pj);
		else
			cout << "ponteiro projetil nulo nao incluido no set" << endl;
	}

	void Gerenciador_Colisoes::incluirJogador(Entidades::Personagens::Jogador* pjog)
	{
		if (pjog)
			LJs.push_back(pjog);
		else
			cout << "ponteiro jogador nulo nao incluido no vector" << endl;
	}

	void Gerenciador_Colisoes::removerEntidade(Entidades::Entidade* pE) {
		if (!pE) return;

		// Tenta remover de jogadores
		if (auto* pj = dynamic_cast<Entidades::Personagens::Jogador*>(pE)) {
			auto it = std::find(LJs.begin(), LJs.end(), pj);
			if (it != LJs.end()) {
				LJs.erase(it);
				std::cout << "Jogador removido do Gerenciador_Colisoes." << std::endl;
				return;
			}
		}

		// Tenta remover de inimigos
		if (auto* pi = dynamic_cast<Entidades::Personagens::Inimigo*>(pE)) {
			auto it = std::find(LIs.begin(), LIs.end(), pi);
			if (it != LIs.end()) {
				LIs.erase(it);
				std::cout << "Inimigo removido do Gerenciador_Colisoes." << std::endl;
				return;
			}
		}

		// Tenta remover de obstáculos
		if (auto* po = dynamic_cast<Obstaculos::Obstaculo*>(pE)) {
			auto it = std::find(LOs.begin(), LOs.end(), po);
			if (it != LOs.end()) {
				LOs.erase(it);
				std::cout << "Obstáculo removido do Gerenciador_Colisoes." << std::endl;
				return;
			}
		}

		std::cout << "Entidade não removida: tipo desconhecido." << std::endl;
	}

	set<Projetil*>& Gerenciador_Colisoes::getProjeteis()
	{
		return LPs;
	}
	void Gerenciador_Colisoes::limpaLista() {
		LIs.clear();
		LOs.clear();
		LPs.clear();
		LJs.clear();
	}

}