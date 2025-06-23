// Jogo.cpp
#include "Jogo.h"
#include "Fase1.h"  // Inclua a Fase1 aqui
#include "Fase2.h"
#include "json.hpp"
#include "MenuInicial.h"
#include <fstream>

#include <string>

using json = nlohmann::json;
using namespace Fases;
using namespace Entidades;

Jogo::Jogo()
    : GC(Gerenciadores::Gerenciador_Colisoes::getInstancia()),
    GG(Gerenciadores::Gerenciador_Grafico::getInstancia()),
	pF1(nullptr), pF2(nullptr), menu(), fase(0), nJogs(0)
{
    Ente::setpGG(GG);  // define ponteiro para o gerenciador gráfico na classe base

    sementear();

	executar(); // Chama o método executar para iniciar o jogo
}
Jogo::~Jogo()
{
    if (pF1) {
        delete pF1;
        pF1 = nullptr;
    }
    if (pF2) {
        delete pF2;
        pF2 = nullptr;
    }
    std::cout << "destrutora jogo" << std::endl;
}

void Jogo::executarFase() {
    while (true) {
        if (pF1) {
            pF1->executar();
            if (pF1->deveTrocarFase()) {
                mudarParaFase2("save.json"); // define e executa Fase2
                break;
            }
            else break; // terminou normalmente
        }
        else if (pF2) {
            pF2->executar();
            break; // jogo terminou aqui
        }
    }
}
void Jogo::executar()
{
    sf::RenderWindow window(sf::VideoMode(960, 640), "Jogo");
    
    window.setFramerateLimit(60); // Limita para 60 FPS

    Gerenciadores::Gerenciador_Grafico::getInstancia()->setJanelaExterna(&window);
    int escolha = 0;
    while (GG->aberta()) {

        escolha = menu.mostrar(window);
        nJogs = menu.getNJogadores();
        fase = menu.getFase();


        sementear();


        if (escolha == 0) {

            Fase* faseAtual = nullptr;
            std::ifstream in("save.json");
            json estado;
            in >> estado;

            fase = estado.value("fase", 1); // valor padrão 1, caso não exista
            nJogs = estado.value("numPlayers", 1); // valor padrão 1, caso não exista

            // Cria a fase correta, mas não executa ainda
            if (fase == 1) {
                pF1 = new Fase1(GC, GG, nJogs);
            }
            else {
                pF2 = new Fase2(GC, GG, nJogs);
            }
			cout << "carregando jogo..." << endl;
            getFase()->carregarJogo("save.json");
            cout << "jogo carregado com sucesso!" << endl;
            executarFase();

            if (pF1) {
                delete pF1;
                pF1 = nullptr;
            }
            if (pF2) {
                delete pF2;
                pF2 = nullptr;
            }
            Entidades::Personagens::Jogador::reiniciarJogs();
            GC->limpaLista();
        }
        else if (escolha == 1) {
            if (fase == 1) {
                pF1 = new Fase1(GC, GG, nJogs);
                getFase()->criarMapa("mapa1.json");
            }
            else if (fase == 2) {
                pF2 = new Fase2(GC, GG, nJogs);
                getFase()->criarMapa("mapa2.json");
            }

            executarFase();
            if (pF1) {
                delete pF1;
                pF1 = nullptr;
            }
            if (pF2) {
                delete pF2;
                pF2 = nullptr;
            }
            Entidades::Personagens::Jogador::reiniciarJogs();
            GC->limpaLista();
        }
        else {
            // Leaderboard
        }

    }


}
Fase* Jogo::getFase()
{
    if(pF1)
        return pF1;
    else if(pF2)
		return pF2;
}

void Jogo::mudarParaFase2(const std::string& caminho)
{
    json estado;

    std::ifstream in(caminho);
    if (in.is_open()) {
        in >> estado;
    }

    
	Entidades::Personagens::Jogador::reiniciarJogs(); 

    pF2 = new Fase2(GC, GG, nJogs);
    pF2->criarMapa("mapa2.json");

    if (pF1->getJogador1()) {
        pF2->getJogador1()->setVida(pF1->getJogador1()->getVidas());
        pF2->getJogador1()->operator+=(pF1->getJogador1()->getPontos());
    }
    else {
        pF2->getJogador1()->setVida(0);
    }
    if (estado["numPlayers"] == 2 && pF1->getJogador2()) {
        pF2->getJogador2()->setVida(pF1->getJogador2()->getVidas());
        pF2->getJogador2()->operator+=(pF1->getJogador2()->getPontos());
    }
    else {
        pF2->getJogador2()->setVida(0);
    }
    
    if (pF1) {
        delete pF1;
        pF1 = nullptr;
    }
    executarFase();
}

void Jogo::sementear()
{
    time_t tempo;
	srand(static_cast<unsigned int>(time(&tempo))); 
}
