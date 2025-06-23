#include "Fase.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace Listas;
using namespace Entidades;
using namespace Gerenciadores;

namespace Fases {

    Fase::Fase(Gerenciadores::Gerenciador_Colisoes* gc, Gerenciadores::Gerenciador_Grafico* gg, int numPlayers_) :
        pGC(gc), pGG(gg), LE(), pontos(0),menuPause(new MenuPause())
    {
        tiros = new Listas::ListaEntidades();

        Ente::setpGG(gg); // define o gerenciador gr�fico no Ente base

        numPlayers = numPlayers_;

        pJog1 = new Entidades::Personagens::Jogador(tiros);
        LE.incluir(pJog1);
        pGC->incluirJogador(pJog1);
        if (numPlayers == 2) {
            pJog2 = new Entidades::Personagens::Jogador(tiros);
            LE.incluir(pJog2);
            pGC->incluirJogador(pJog2);
        }
        else {
            pJog2 = nullptr;
        }
        criarHUD();
    }

    Fase::~Fase() {
        // A lista deve deletar todas as entidades automaticamente.
        cout << "destrutora fase apagando a lista de projeteis(tiros)" << endl;
        delete tiros;
        tiros = nullptr;

        if (menuPause) {
            delete menuPause;
            menuPause = nullptr;
        }
    }

  
    Listas::ListaEntidades* Fase::getListaEntidades() {
        return &LE;
    }

    int Fase::getNumPlayers() const
    {
        return numPlayers;
    }

    Entidades::Personagens::Jogador* Fase::getJogador1() const
    {
        return pJog1;
    }
    Entidades::Personagens::Jogador* Fase::getJogador2() const
    {
        return pJog2;
    }

    void Fase::gravarNome(sf::RenderWindow* window) {

        // Salva a view atual da fase
        sf::View viewAnterior = window->getView();

        // Cria uma view fixa (HUD) centralizada na tela
        sf::View viewHUD(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
        viewHUD.setCenter(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
        sf::Font font;
        if (!font.loadFromFile("upheavtt.ttf")) {
            return; // Verifique se a fonte está disponível
        }

        std::string nome;
        sf::Text texto;
        texto.setFont(font);
        texto.setCharacterSize(28);
        texto.setFillColor(sf::Color::White);


        sf::Text instrucao("Digite seu nome e pressione Enter:", font, 24);
        instrucao.setFillColor(sf::Color::White);

        instrucao.setPosition(window->getSize().x / 2.f - 180, window->getSize().y / 2.f - 60);
        texto.setPosition(window->getSize().x / 2.f - 100, window->getSize().y / 2.f);

        bool inserindo = true;
        while (inserindo && window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                    return;
                }

                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!nome.empty())
                            nome.pop_back();
                    }
                    else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                        inserindo = false;
                    }
                    else if (event.text.unicode < 128 && nome.size() < 15) {
                        nome += static_cast<char>(event.text.unicode);
                    }
                }
            }

            texto.setString("Nome: " + nome);

            window->setView(viewHUD);
            window->clear(sf::Color::Black);
            window->draw(instrucao);
            window->draw(texto);
            window->display();
        }

        window->setView(viewAnterior);

        int total = pontos;
		if (pJog1) {
			total += pJog1->getPontos();
		}
        if (pJog2) {
            total += pJog2->getPontos();
        }

        std::ifstream in("leaderboard.json");
        json lb = json::array();
        if (in.is_open()) {
            in >> lb;
        }

        lb.push_back({ {"nome", nome}, {"pontuacao", total} });

        std::sort(lb.begin(), lb.end(), [](const json& a, const json& b) {
            return a["pontuacao"] > b["pontuacao"];
            });

        //if (lb.size() > 10)
           // lb.erase(lb.begin() + 10, lb.end());
        //
        std::ofstream out("leaderboard.json");
        out << lb.dump(4);
    }

    bool Fase::fimFase()
    {
        
        if (numPlayers == 1) {
            if (pJog1->getcm().x > FINALFASE - 30 && pJog1->getcm().x < FINALFASE + 30) {
                return true;
            }
        }
        else if (numPlayers == 2) {
            if (pJog1 && pJog2) {
                if ((pJog1->getcm().x > FINALFASE - 30 && pJog1->getcm().x < FINALFASE + 30) && (pJog2->getcm().x > FINALFASE - 30 && pJog2->getcm().x < FINALFASE + 30)) {
                    return true;
                }
            }
            else if (pJog1) {
                if (pJog1->getcm().x > FINALFASE - 30 && pJog1->getcm().x < FINALFASE + 30) {
                    return true;
                }
            }
            else
                if (pJog2->getcm().x > FINALFASE - 30 && pJog2->getcm().x < FINALFASE + 30) {
                    return true;
                }
        }
        return false;
    }

    void Fase::criarHUD()
    {
        if (!fonteHUD.loadFromFile("upheavtt.ttf")) {
            std::cerr << "Erro ao carregar a fonte!" << std::endl;
            return;
        }
        else {
            cout << "Fonte carregada com sucesso!" << endl;
        }
        HUD.setFont(fonteHUD);
        HUD.setCharacterSize(36);
        HUD.setFillColor(sf::Color::White);
        HUD.setPosition(50, 50);

    }

    void Fase::mostrarVidaPontos()
    {
        if (pJog1 && pJog2) {
            HUD.setString("1. Vida: " + std::to_string(pJog1->getVidas()) + "    Pontos: " + std::to_string(pJog1->getPontos())
                + "   2. Vida: " + std::to_string(pJog2->getVidas()) + "    Pontos: " + std::to_string(pJog2->getPontos()));
        }
        else if (pJog1) {
            HUD.setString("1. Vida: " + std::to_string(pJog1->getVidas()) + "    Pontos: " + std::to_string(pJog1->getPontos()));
        }
        else if (pJog2) {
            HUD.setString("2. Vida: " + std::to_string(pJog2->getVidas()) + "    Pontos: " + std::to_string(pJog2->getPontos()));
        }
    }

    void Fase::desenharProjeteis()//mostra os projeteis na tela
    {
        tiros->desenhar();

    }
    void Fase::incluirProjeteisGC()
    {
        for (tiros->primeiro(); !tiros->fim(); tiros->operator++()) {
            pGC->incluirProjetil(static_cast<Entidades::Projetil*>(tiros->getAtual()));
        }
    }

    void Fase::destruirProjeteis()//pega os desativados e tira da ListaEntidades e do Gerenciador_Colisoes e deleta
    {
        pGC->retirarProjeteis();

        Projetil* pj = nullptr;
        for (tiros->primeiro(); !tiros->fim(); tiros->operator++()) {
            pj = static_cast<Entidades::Projetil*>(tiros->getAtual());
            if (pj && pj->getAtivo() == false) {
                tiros->retirar(pj);
                delete pj;
                pj = nullptr;
            }
        }
    }

    
}