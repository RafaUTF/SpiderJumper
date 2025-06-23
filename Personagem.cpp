#include "Personagem.h"

using namespace Listas;

namespace Entidades {
    namespace Personagens {

        Personagem::Personagem(Listas::ListaEntidades* t, Vector2f pos) :
            Entidade(pos), num_vidas(VIDA_BASE),
            aceleracao(ACELERACAO_BASE), comChao(false), tiros(t),
            recarga(TEMPO_RECARGA), olhandoDir(true), forca_pulo(PULO_JOG)
        {

        }


        Personagem::~Personagem()
        {
            tiros = nullptr;
        }


        void Personagem::setChao(bool b)
        {
            comChao = b;
        }

        
        void Personagem::reduzVelocidade(float fator)
        {
            vel *= fator;

        }

        void Personagem::restaurarVelocidade() {
            aceleracao = 1.f;
        }

        void Personagem::sofrerGravidade()
        {
            //GRAVIDADE ANTES!
            if (getcm().y + getRaio().y < CHAO_CHEFE && !comChao) {
                vel.y += GRAVIDADE;
            }
            else {//chao // comChao == true
                vel.y = 0;
                comChao = true;//tem q ter!
            }
        }

        void Personagem::operator--() {
            if (num_vidas > 0)
                num_vidas--;
        }

        void Personagem::operator-=(int dano)
        {
            num_vidas -= dano;
        }

        const int Personagem::getVidas() const
        {
            return num_vidas;
        }

        void Personagem::setVida(int v)
        {
            num_vidas = v;
        }

        void Personagem::colidir(Entidade* pe, int d)
        {
            if (d == 1) {
                getVel().y = 0.f;
                getCorpo().setPosition(
                    getcm().x,
                    pe->getcm().y + getRaio().y + pe->getRaio().y
                );
            }

            else if (d == 2) {
                getVel().x = 0.f;
                getCorpo().setPosition(
                    pe->getcm().x + getRaio().x + pe->getRaio().x,
                    getcm().y
                );
            }
            else if (d == 3) {
                getVel().x = 0.f;
                getCorpo().setPosition(
                    pe->getcm().x - getRaio().x - pe->getRaio().x,
                    getcm().y
                );
            }
            else {//d==4
                getVel().y = 0.f;
                getVel().y = pe->getVel().y;
                getCorpo().setPosition(
                    getcm().x,
                    pe->getcm().y - getRaio().y - pe->getRaio().y
                );
            }
        }


        void Personagem::zerarPulo()
        {
            forca_pulo = PULO_JOG;
        }

        void Personagem::reduzPulo(float fator)
        {
            forca_pulo = PULO_JOG * fator;
        }

    }
}