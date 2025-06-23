#include "Fase2.h"
#include <fstream>
#include "json.hpp"

#include "MenuPause.h"

using json = nlohmann::json;
using namespace Entidades;
using namespace Gerenciadores;

namespace Fases {

    Fase2::Fase2(Gerenciadores::Gerenciador_Colisoes* gc, Gerenciadores::Gerenciador_Grafico* gg, int numPlayers)
        : Fase(gc, gg, numPlayers)
    {
		pGG->setFundo("fundoroxo.png"); // Define o fundo da fase 2

    }

    Fase2::~Fase2() {
        cout << "destrutora fase2" << endl;
    }

    void Fase2::executar() {
        while (pGG->aberta()) {
            sf::Event event;
            while (pGG->getWindow()->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    pGG->fechar();

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape && menuPause) {
                        // ABRIR MENU DE PAUSE
                        menuPause->setAtivo();
                        int escolha = menuPause->mostrar(*pGG->getWindow());

                        if (escolha == 1) { // Salvar Jogo
                            salvarJogo("save.json");
                            std::cout << "Jogo salvo.\n";
                        }
                        else if (escolha == 2) { // Sair para Menu
                            menuPause->setAtivo(false);
                            return; // sai da fase e volta ao menu inicial
                        }
                    }
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
                        salvarJogo("save.json");
                        std::cout << "Jogo salvo!" << std::endl;
                    }
                }
            }

            mostrarVidaPontos(); // Atualiza o texto com a vida e pontos dos jogadores
            LE.percorrer();
            tiros->percorrer();
            incluirProjeteisGC();
            pGC->executar();
            pGG->moverCamera(&HUD, pJog1, pJog2);
            pGG->clear();
            pGG->desenhaFundo();
            LE.desenhar();
            tiros->desenhar();
			pGG->getWindow()->draw(HUD);  // Desenha o texto do contador
            pGG->mostrar();
            destruirProjeteis();
            destruirNeutralizados();

            if (pJog1 == nullptr && pJog2 == nullptr) {
                cout << "todos os jogadores foram neutralizados, fim do programa!" << endl;
                cout << "PONTUACAO TOTAL: " << pontos << endl;

                gravarNome(pGG->getWindow());


                pGG->fechar();

                return;

            }

            if (fimFase()) {
                if (pJog1 && pJog2) {
                    pJog1->operator+=(PREMIO2 / 2);
                    pJog2->operator+=(PREMIO2 / 2);
                }
                else if (pJog1)
                    pJog1->operator+=(PREMIO2);
                else
                    pJog2->operator+=(PREMIO2);
                gravarNome(pGG->getWindow());
                pGG->fechar();
            }

        }

    }


    void Fase2::criarChefe(Vector2f pos) {
        Entidades::Personagens::Chefao* chefe = new Entidades::Personagens::Chefao(tiros, pJog1, pJog2, pos);
        LE.incluir(chefe);
        pGC->incluirInimigo(chefe);
        LCs.push_back(chefe);
    }


    void Fase2::criarMapa(const std::string& caminhoJson) {
        std::ifstream arquivo(caminhoJson);
        if (!arquivo.is_open()) {
            std::cerr << "Erro ao abrir o arquivo JSON: " << caminhoJson << std::endl;
            return;
        }

        json mapaJson;
        arquivo >> mapaJson;

        const int larguraTiles = mapaJson["tilewidth"];
        const int alturaTiles = mapaJson["tileheight"];
        const int larguraMapa = mapaJson["width"];
        const int alturaMapa = mapaJson["height"];

        const auto& camada = mapaJson["layers"][0];  // Usando primeira camada ("Camada de Blocos 1")
        const auto& data = camada["data"];

        std::vector<std::pair<float, float>> bloco_teia;
        std::vector<std::pair<float, float>> bloco_plataforma;



        for (int i = 0; i < data.size(); ++i) {
            int id = data[i];
            if (id == 0)
                continue; // sem tile

            int coluna = i % larguraMapa;
            int linha = i / larguraMapa;

            float x = coluna * larguraTiles;
            float y = linha * alturaTiles;




            //plataforma aleatória
            if (id == 12) {
                bloco_plataforma.emplace_back(x, y);
                if (bloco_plataforma.size() == 6) {
                    int chance = rand() % 2;
                    float deslocamento = -rand() % 50;
                    for (auto& pos : bloco_plataforma) {
                        if (chance == 0) {
                            Entidades::Obstaculos::Plataforma* plataforma = new Entidades::Obstaculos::Plataforma({ pos.first, pos.second }, deslocamento);
                            LE.incluir(plataforma);
                            pGC->incluirObstaculo(plataforma);
                        }
                    }
                    bloco_plataforma.clear();
                }
            }
            else {
                // Se encontrar um tile diferente, reseta o bloco
                bloco_plataforma.clear();
            }

            //Espinho aleatório
            if (id == 4) {
                int chance = rand() % 2;
                if (chance == 0) {
                    Entidades::Obstaculos::Espinho* espinho = new Entidades::Obstaculos::Espinho({ x, y });
                    LE.incluir(espinho);
                    pGC->incluirObstaculo(espinho);
                }
            }

            //Boss aleatório
            if (id == 21) {
                int chance = rand() % 2;
                if (chance == 0) {
                    criarChefe({ x, y });
                }
            }

            if (id == 26) {
                int chance = rand() % 2;
                if (chance == 0) {
                    Entidades::Personagens::InimigoPequeno* inimigoPequeno = new Entidades::Personagens::InimigoPequeno({ x, y });
                    LE.incluir(inimigoPequeno);
                    pGC->incluirInimigo(inimigoPequeno);
                }
            }

            if (id == 19) {
                pJog1->getCorpo().setPosition({ x, y });
            }
            if (id == 23) {
                if (pJog2)
                    pJog2->getCorpo().setPosition({ x, y });
            }

            // Ex: id 2 = chão, id 781 = plataforma, etc.
            if (id == 2 || id == 781 || id == 34 || id == 28) {
                auto* plataforma = new Entidades::Obstaculos::Plataforma({ x, y });
                LE.incluir(plataforma);
                pGC->incluirObstaculo(plataforma);
            }

            if (id == 10) {
                criarChefe({ x, y });
            }

            if (id == 20) {
                Entidades::Obstaculos::Espinho* espinho = new Entidades::Obstaculos::Espinho({ x, y });
                LE.incluir(espinho);
                pGC->incluirObstaculo(espinho);
            }

            if (id == 18) {
                Entidades::Personagens::InimigoPequeno* inimigoPequeno = new Entidades::Personagens::InimigoPequeno({ x, y });
                LE.incluir(inimigoPequeno);
                pGC->incluirInimigo(inimigoPequeno);
            }


        }

    }

    void Fase2::salvarJogo(const std::string& caminho) {
        json estado;
        estado["fase"] = 2;
        estado["numPlayers"] = getNumPlayers();
        if (pJog1)
            pJog1->salvar(estado);
        else
            estado["jogador1"] = { {"x", 0}, {"y", 0}, {"numvidas", 0}, { "pontos1", 0 } };
        if (getNumPlayers() == 2)
        {
            if (pJog2) {
                pJog2->salvar(estado);
            }
            else
                estado["jogador2"] = { {"x", 0}, {"y", 0}, {"numvidas", 0}, { "pontos2", 0 } };
        }

        estado["projeteis"] = json::array();
        set<Projetil*>::iterator it = pGC->getProjeteis().begin();
        while (it != pGC->getProjeteis().end()) {
            (*it)->salvar(estado);
            ++it;
        }

        estado["entities"] = json::array();
        for (LE.primeiro(); !LE.fim(); ++LE) {
            Entidades::Entidade* e = LE.getAtual();

            if (e == pJog1 || e == pJog2) continue;
            json je;
            if (e) {
				e->salvarPos(je);
                e->salvar(je);
            }
            estado["entities"].push_back(je);
        }

        std::ofstream out(caminho);
        if (out.is_open()) out << estado.dump(4);
    }
    float modulo(float x) {
        return x < 0 ? (-1.f) * x : x;
    }

    void Fase2::carregarJogo(const std::string& caminho) {
        
        std::ifstream in(caminho);
        if (!in.is_open()) return;

        json estado;
        in >> estado;

        if (!pJog1) {
            pJog1 = new Entidades::Personagens::Jogador(&LE);
            pGC->incluirJogador(pJog1);
        }
        if (estado["numPlayers"] == 2 && !pJog2) {
            pJog2 = new Entidades::Personagens::Jogador(&LE);
            pGC->incluirJogador(pJog2);
        }


        if (estado["jogador1"]["numvidas"] > 0) {

            pJog1->getCorpo().setPosition(estado["jogador1"]["x"], estado["jogador1"]["y"]);
            pJog1->setVida(estado["jogador1"]["numvidas"]);
			pJog1->operator+=(estado["jogador1"]["pontos1"]);
        }
        else {
            pJog1->setVida(0);
        }

        if (estado["numPlayers"] == 2) {
            if (estado["jogador2"]["numvidas"] > 0) {
                pJog2->getCorpo().setPosition(estado["jogador2"]["x"], estado["jogador2"]["y"]);
                pJog2->setVida(estado["jogador2"]["numvidas"]);
				pJog2->operator+=(estado["jogador2"]["pontos2"]);
            }
            else
            {
                pJog2->setVida(0);
            }
        }


        for (auto& je : estado["entities"]) {
            Entidades::Entidade* ne = nullptr;
            Entidades::Obstaculos::Obstaculo* no = nullptr;
            sf::Vector2f pos(je["x"], je["y"]);
            std::string tipo = je["type"];


            if (tipo == "Plataforma") {
                no = new Entidades::Obstaculos::Plataforma(pos);
            }
            else if (tipo == "Espinho") no = new Entidades::Obstaculos::Espinho(pos);
            else if (tipo == "Chefao") ne = new Entidades::Personagens::Chefao(tiros, pJog1, pJog2,
                pos, je["forca"], je["vida"]);

            sf::Vector2f posAtual(je["x"], je["y"]);
            sf::Vector2f posIni = posAtual;
            if (je.contains("xi") && je.contains("yi"))
                posIni = sf::Vector2f(je["xi"], je["yi"]);

            if (tipo == "InimigoPequeno") {
                float acelex = je["aceleracaoextra"];
                Entidades::Personagens::InimigoPequeno* ip = new Entidades::Personagens::InimigoPequeno(posIni, acelex); // posição inicial de patrulha
				ip->setVida(je["vida"]);
                ip->getCorpo().setPosition(posAtual);// posição atual real
                ne = ip;
            }

            std::cout << "Tipo encontrado: [" << tipo << "]" << std::endl;

            if (ne) {
                LE.incluir(ne);
                pGC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo*>(ne));

            }

            if (no) {
                LE.incluir(no);
                pGC->incluirObstaculo(no);
                
            }

        }
		
        

        for (auto& jp : estado["projeteis"]) {
            Entidades::Personagens::Jogador* p = pJog1;
            if(modulo(jp["vx"])!=FORCA_JOG){
                p = nullptr;
            }
            else if(!p) {
                p = pJog2;
            }
            Projetil* proj = new Projetil(sf::Vector2f(jp["x"], jp["y"]),
                sf::Vector2f(jp["vx"], jp["vy"]), p);
            tiros->incluir(proj);
            
            pGC->incluirProjetil(proj);
        
        }


    }

    void Fase2::destruirNeutralizados()
    {
        pGC->retirarPersonagens();

        Entidades::Entidade* pe = nullptr;
        for (LE.primeiro(); !LE.fim(); LE.operator++()) {
            pe = LE.getAtual();
            if (pe) {
                Entidades::Personagens::Personagem* p = dynamic_cast<Entidades::Personagens::Personagem*>(pe);
                if (p && p->getVidas() == 0) {
                    Entidades::Personagens::Jogador* pjog = dynamic_cast<Entidades::Personagens::Jogador*>(pe);
                    if (pJog1 && pjog == pJog1) {
                        if (pJog2)
                            pJog2->operator+=(pJog1->getPontos());
                        else
                            pontos = pJog1->getPontos();
                        pJog1 = nullptr;
                    }
                    else if (pJog2 && pjog == pJog2) {
                        if (pJog1)
                            pJog1->operator+=(pJog2->getPontos());
                        else
                            pontos = pJog2->getPontos();
                        pJog2 = nullptr;
                    }
                    else {
                        Entidades::Personagens::Chefao* pc = dynamic_cast<Entidades::Personagens::Chefao*>(pe);
                        bool eliminou = false;
                        vector<Entidades::Personagens::Chefao*>::iterator it = LCs.begin();
                        while (!eliminou && it != LCs.end()) {
                            if (pc && pc == *it) {
                                cout << "chefe morreu" << endl;
                                LCs.erase(it);
                                eliminou = true;
                            }
                            else
                                it++;
                        }
                    }

                    LE.retirar(pe);
                    delete pe;
                    pe = nullptr;
                }

            }
        }
    }

}