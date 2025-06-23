#include "Projetil.h"

#include "Jogador.h"
#include "Chefao.h"
#include "InimigoAlto.h"
#include "InimigoPequeno.h"

using namespace Listas;
using namespace Entidades::Personagens;
namespace Entidades {

    Projetil::Projetil(Vector2f pos, bool dir, float raio, Listas::ListaEntidades* lp,
        Entidades::Personagens::Jogador* pdono, short int f) :
        Entidade(pos), ativo(true), lista(lp), duracao(TEMPO_PROJETIL), pDono(pdono)
    {
        try {
            carregarTextura("projetil.png");
            corpo.setTexture(&textura);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            corpo.setFillColor(sf::Color::White); // fallback color
        }

        if (dynamic_cast<Personagens::Jogador*>(pDono)) {
            corpo.setSize(Vector2f(TAM_PROJ_JOG, TAM_PROJ_JOG));
        }
        else {
            corpo.setSize(Vector2f(TAM_PROJ_CHEFE, TAM_PROJ_CHEFE));
        }
        centralizarEntidade();

        float v = static_cast<float>(f);
        if (dir) {
            vel = (Vector2f(v, VY0));
            corpo.move(raio * 1.5f, 0.f);
        }
        else {
            vel = (Vector2f(-1.f * v, VY0));
            corpo.move(-raio * 1.5f, 0.f);
        }

    }

    Projetil::Projetil(Vector2f pos, Vector2f v, Entidades::Personagens::Jogador* pdono):
		Entidade(pos), pDono(pdono), ativo(true), lista(nullptr), duracao(TEMPO_PROJETIL)
    {
        try {
            carregarTextura("projetil.png");
            corpo.setTexture(&textura);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            corpo.setFillColor(sf::Color::White); // fallback color
        }

        if (dynamic_cast<Personagens::Jogador*>(pDono)) {
            corpo.setSize(Vector2f(TAM_PROJ_JOG, TAM_PROJ_JOG));
        }
        else {
            corpo.setSize(Vector2f(TAM_PROJ_CHEFE, TAM_PROJ_CHEFE));
        }
        centralizarEntidade();

        vel = v;

    }

    Projetil::~Projetil()
    {
        cout << "DESTRUTORA PROJETIL" << endl;
    }

    void Projetil::executar()
    {
        vel.y += GRAVIDADE;
        corpo.move(vel);
        duracao--;
        if (duracao == 0) {
            cout << "acabou o tempo do projetil" << endl;
            ativo = false;
        }
    }

    const bool Projetil::getAtivo()
    {
        return ativo;
    }

    void Projetil::explodir(Personagens::Personagem* pp)
    {
        ativo = false;
        cout << "projetil colidiu" << endl;
        if (pp) {
            pp->operator--();
            if (pp->getVidas() == 0) {
                cout << "personagem neutralizado por projetil" << endl;
                if (pDono) {
                    if (dynamic_cast<Jogador*>(pp))
                        pDono->operator+=(PUNICAO_FOGO_AMIGO);
                    else if(dynamic_cast<Chefao*>(pp))
                        pDono->operator+=(PREMIO_CHEFE);
                    else if (dynamic_cast<InimigoAlto*>(pp))
                        pDono->operator+=(PREMIO_ALTO);
                    else if (dynamic_cast<InimigoPequeno*>(pp))
                        pDono->operator+=(PREMIO_BAIXO);
                      
                    else
                        pDono->operator+=(PREMIO_BAIXO);
                }
            }
        }
    }

    void Projetil::explodir()
    {
        ativo = false;
    }

    Vector2f Projetil::getVelocidade()
    {
        return vel;
    }

    void Projetil::setVelocidade(Vector2f v)
    {
        vel = v;
    }

    void Projetil::setDono(Entidades::Personagens::Jogador* pdono)
    {
        pDono = pdono;
    }

    void Projetil::salvar(json& j)
    {
        j["type"] = "Projetil";
        j["projeteis"].push_back({
                 {"x", getCorpo().getPosition().x},
                 {"y", getCorpo().getPosition().y},
                 {"vx", getVelocidade().x},
                 {"vy", getVelocidade().y},

            });
    }

}
