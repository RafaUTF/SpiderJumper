#include "Chefao.h"

using namespace Listas;

namespace Entidades {

    namespace Personagens {

        Chefao::Chefao(Listas::ListaEntidades* t, Jogador* pp1, Jogador* pp2, Vector2f pos) :
            Inimigo(t, pos), forca(FORCA_JOG)
        {
            while (forca == FORCA_JOG) {
				forca = MIN_FORCA_CHEFE + rand() % (MAX_FORCA_CHEFE - MIN_FORCA_CHEFE);
            }

            chefao = true;

            num_vidas = VIDA_CHEFE;

            nivel_maldade = DANO_CHEFE;

            aceleracao = ACELERACAO_CHEFE;

            p1 = pp1;
            p2 = pp2;
  
            corpo.setSize(Vector2f(150.f, 150.f));
            centralizarEntidade();
            try {
                carregarTextura("boss.png");
                corpo.setTexture(&textura);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                corpo.setFillColor(sf::Color::Red); // fallback color
            }
        }

        Chefao::Chefao(Listas::ListaEntidades* t, Jogador* pp1, Jogador* pp2, Vector2f pos, short int f, int vida):
			Inimigo(t, pos), forca(f)
		{
            chefao = true;

            num_vidas = vida;

            nivel_maldade = DANO_CHEFE;

            aceleracao = ACELERACAO_CHEFE;

            p1 = pp1;
            p2 = pp2;

            recarga = 0;
            corpo.setSize(Vector2f(150.f, 150.f));
            centralizarEntidade();
            try {
                carregarTextura("boss.png");
                corpo.setTexture(&textura);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                corpo.setFillColor(sf::Color::Red); // fallback color
            }
            
        }
        Chefao::~Chefao()
        {
            cout << "destrutora chefao" << endl;
        }

        void Chefao::executar()
        {
            escolherAlvo();
            mover();//mover inimigo
            if (pAlvo) {
                atirar();
            }
        }

        void Chefao::salvar(json& j)
        {
            j["type"] = "Chefao";
            j["vida"] = getVidas();
            j["forca"] = getForca();
        }

        
        void Chefao::mover() {
            sofrerGravidade();
            if (pAlvo)
                perseguir();
            corpo.move(vel);
        }
        void Chefao::atirar()
        {
            if (recarga >= TEMPO_RECARGA) {
                cout << "CHEFAO ATIROU" << endl;
                tiros->incluir(new Projetil(getcm(), olhandoDir, getRaio().x, tiros, nullptr, forca));
                recarga = 0;
            }
            else
                recarga++;

        }
        const short int Chefao::getForca() const
        {
            return forca;
        }
    }
}

