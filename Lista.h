#pragma once
#include <iostream>

namespace Listas {

	template<class TL>
	class Lista
	{
	private:
		template<class TIPO>
		class Elemento
		{
		private:
			Elemento<TIPO>* pProx;
			TIPO Info;
		public:
			Elemento(TIPO i = NULL) : pProx(NULL), Info(i) {}
			~Elemento() { pProx = NULL; Info = NULL; }
			void setProx(Elemento<TIPO>* pp) { pProx = pp; }
			Elemento<TIPO>* getProx() { return pProx; }
			void setInfo(TIPO i) { Info = i; }
			TIPO& getInfo() { return Info; }
		};

	private:
		Elemento<TL>* pInicio;
		Elemento<TL>* pAtual;
	public:
		Lista() : pInicio(NULL), pAtual(NULL) {}
		~Lista() {
			clear();
			pInicio = NULL;
			pAtual = NULL;
		}
		void clear() {
			Elemento<TL>* pex = pInicio;
			Elemento<TL>* lixo = NULL;
			while (pex) {
				lixo = pex;
				pex = pex->getProx();
				delete lixo;
				lixo = NULL;
			}
			pInicio = NULL;
			pAtual = NULL;
		}

		void push_back(TL i) {
			Elemento<TL>* pex = new Elemento<TL>(i);
			if (pInicio == NULL) {
				pInicio = pex;
				pAtual = pex;
			}
			else {
				pAtual->setProx(pex);
				pAtual = pex;
			}
		}

		bool remove(TL i) {
			Elemento<TL>* lixo = pInicio;
			Elemento<TL>* pex = nullptr;
			while (lixo) {
				if (lixo->getInfo() == i) {
					if (pex)
						pex->setProx(lixo->getProx());
					else
						pInicio = lixo->getProx();
					delete lixo;
					lixo = nullptr;
					return true;
				}
				pex = lixo;
				lixo = lixo->getProx();
			}
			return false;
		}

		class iterator {
		private:
			Elemento<TL>* pex;
		public:
			iterator(Elemento<TL>* p = nullptr) : pex(p) {}
			~iterator() {}

			TL& operator*() const {
				return pex->getInfo();
			}

			iterator& operator++() {
				if (pex) pex = pex->getProx();
				return *this;
			}

			bool operator==(const iterator& outro) const {
				return pex == outro.pex;
			}

			bool operator!=(const iterator& outro) const {
				return pex != outro.pex;
			}
		};


		iterator begin() const {
			return iterator(pInicio);
		}

		iterator end() const {
			return iterator(nullptr);
		}

	};

}