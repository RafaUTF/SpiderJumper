#include "Jogador.h"
bool Entidades::Personagens::Jogador::jogador1(true);

using namespace Listas;
float modulo(float x);

namespace Entidades {
    namespace Personagens {

        Jogador::Jogador(Listas::ListaEntidades* t, Vector2f pos) : Personagem(t, pos), pontos(0)
        {
            forca_pulo = PULO_JOG;

            num_vidas = VIDA_JOGADOR;

            aceleracao = ACELERACAO_JOG;

            if (jogador1) {

                try {
                    carregarTextura("j1.png");
                    corpo.setTexture(&textura);
                }
                catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                    corpo.setFillColor(sf::Color::Blue); // fallback color
                }
                cout << "JOGADOR 1 CRIADO" << endl;
                corpo.setSize(Vector2f(64.f, 64.f));
                centralizarEntidade();
                jogador1 = false;
                j1 = true;
            }
            else {//segundo jogador

                try {
                    carregarTextura("j2.png");
                    corpo.setTexture(&textura);
                }
                catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                    corpo.setFillColor(sf::Color::Green); // fallback color
                }
                cout << "JOGADOR 2 CRIADO" << endl;
                corpo.setSize(Vector2f(64.f, 64.f));
                centralizarEntidade();

                j1 = false;
            }

        }
        Jogador::~Jogador()
        {
            cout << "destrutora jogador" << endl;

        }

        void Jogador::executar() {
            mover();
            atirar();
            //tiros->percorrer();
        }


        void Jogador::colidirJog(Jogador* p, int d)
        {
            float dx = p->getcm().x - getcm().x,//+ -> colisao dir do pe1
                dy = p->getcm().y - getcm().y,//+ -> colisao em baixo do pe1
                drx = getRaio().x + p->getRaio().x,
                dry = getRaio().y + p->getRaio().y,
                x = drx - modulo(dx), y = dry - modulo(dy);

            if (d == 1) {
                if (modulo(p->getVel().x) < modulo(getVel().x))
                    p->getVel().x = getVel().x;

                p->setChao(true);
                p->reduzPulo();
                p->getVel().y = getVel().y;
                getCorpo().move(0.f, y / 2);
                p->getCorpo().move(0.f, -y / 2);

            }
            if (d == 4) {
                if (modulo(getVel().x) < modulo(p->getVel().x))
                    getVel().x = p->getVel().x;

                setChao(true);
                reduzPulo();
                getVel().y = p->getVel().y;
                getCorpo().move(0.f, -y / 2);
                p->getCorpo().move(0.f, y / 2);

            }
            if (d == 2) {
                getVel().x = 0.f;
                p->getVel().x = 0.f;
                getCorpo().move(x / 2, 0.f);
                p->getCorpo().move(-x / 2, 0.f);

            }
            if (d == 3) {
                getVel().x = 0.f;
                p->getVel().x = 0.f;

                getCorpo().move(-x / 2, 0.f);
                p->getCorpo().move(x / 2, 0.f);

            }
        }


        void Jogador::atirar()
        {
            if (recarga >= TEMPO_RECARGA) {
                if (j1 && sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                    cout << "p1 ATIROU" << endl;
                    tiros->incluir(new Projetil(getcm(), olhandoDir, getRaio().x, tiros, this, FORCA_JOG));
                    recarga = 0;
                }
                else if (!j1 && sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                    cout << "p2 ATIROU" << endl;
                    tiros->incluir(new Projetil(getcm(), olhandoDir, getRaio().x, tiros, this, FORCA_JOG));
                    recarga = 0;
                }
            }
            else
                recarga++;

        }

        const int Jogador::getPontos() const
        {
            return pontos;
        }

        void Jogador::operator+=(const int n)
        {
            pontos += n;
        }

        void Jogador::operator++()
        {
            pontos++;
        }

        void Jogador::salvar(json& j)
        {
            j["type"] = "Jogador";
            if (j1) {
                j["jogador1"] = { {"x", getCorpo().getPosition().x},
                {"y", getCorpo().getPosition().y}, {"numvidas", getVidas() },
                {"pontos1", getPontos()} };
            }
            else {
                j["jogador2"] = { {"x", getCorpo().getPosition().x},
                {"y", getCorpo().getPosition().y}, {"numvidas", getVidas() },
                {"pontos2", getPontos()} };
            }
            
        }

        void Jogador::reiniciarJogs()
        {
            jogador1 = true;
        }



        void Jogador::mover()
        {

            sofrerGravidade();

            if (j1) {
                if (!comChao) {//NO AR

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        vel.x += -aceleracao / 5.f;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        vel.x += aceleracao / 5.f;

                    //ATRITO AR(VISCOSO)
                    if (vel.x > 0) {
                        vel.x -= VISCOSO;
                        if (vel.x < 0)
                            vel.x = 0.f;
                    }
                    else if (vel.x < 0) {
                        vel.x += VISCOSO;
                        if (vel.x > 0)
                            vel.x = 0.f;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        vel.y += aceleracao;
                }
                else if (getcm().y - getRaio().y < CHAO_CHEFE) {//CHAO

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        vel.x += -aceleracao;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        vel.x += aceleracao;

                    //ATRITO CHAO
                    if (vel.x > 0) {
                        vel.x -= ATRITO;
                        if (vel.x < 0)
                            vel.x = 0.f;
                    }
                    else if (vel.x < 0) {
                        vel.x += ATRITO;
                        if (vel.x > 0)
                            vel.x = 0.f;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        //cout << "pulo unico 2!" << endl;
                        vel.y += forca_pulo;
                        comChao = false;
                    }
                }
            }
            else {//JOGADOR 2
                if (!comChao) {//NO AR

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        vel.x += -aceleracao / 5;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        vel.x += aceleracao / 5;

                    //ATRITO AR(VISCOSO)
                    if (vel.x > 0) {
                        vel.x -= VISCOSO;
                        if (vel.x < 0)
                            vel.x = 0.f;
                    }
                    else if (vel.x < 0) {
                        vel.x += VISCOSO;
                        if (vel.x > 0)
                            vel.x = 0.f;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        vel.y += aceleracao;
                }
                else if (getcm().y - getRaio().y < CHAO_CHEFE) {//CHAO

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        vel.x += -aceleracao;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        vel.x += aceleracao;

                    //ATRITO CHAO
                    if (vel.x > 0) {
                        vel.x -= ATRITO;
                        if (vel.x < 0)
                            vel.x = 0.f;
                    }
                    else if (vel.x < 0) {
                        vel.x += ATRITO;
                        if (vel.x > 0)
                            vel.x = 0.f;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        //cout << "pulo unico 2!" << endl;
                        vel.y += forca_pulo;
                        comChao = false;
                    }
                }
            }
            //atrito do ar em y
            if (vel.y > 0) {
                vel.y -= VISCOSO;
                if (vel.y < 0)
                    vel.y = 0.f;
            }
            else if (vel.y < 0) {
                vel.y += VISCOSO;
                if (vel.y > 0)
                    vel.y = 0.f;
            }

            //paredes invisiveis
            //if (getcm().x - getRaio().x < ESQUERDA && vel.x<0
            //   || getcm().x + getRaio().x > DIREITA && vel.x>0) {
            //    vel.x = 0.f;
            //}

            if (vel.x > MAX_VEL_JOG)
                vel.x = MAX_VEL_JOG;
            else if (vel.x < -MAX_VEL_JOG)
                vel.x = -MAX_VEL_JOG;

            corpo.move(vel);

            if (vel.x > 0)
                olhandoDir = true;
            else if (vel.x < 0)
                olhandoDir = false;
        }

    }
}