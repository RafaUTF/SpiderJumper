
#pragma once
#include "Ente.h"
#include "ListaEntidades.h"
#include "Gerenciador_Colisoes.h"
#include "Gerenciador_Grafico.h"
#include "Plataforma.h"
#include "TeiaAranha.h"
#include "Inimigo.h"
#include "Chefao.h"
#include "InimigoPequeno.h"
#include "InimigoAlto.h"

#include "MenuPause.h"
namespace Fases {

    class Fase : public Ente {
    protected:
        MenuPause* menuPause;

		sf::Font fonteHUD;
        sf::Text HUD;

        int pontos;

        int numPlayers;

        Entidades::Personagens::Jogador* pJog1;
        Entidades::Personagens::Jogador* pJog2;

        Listas::ListaEntidades LE;
        Listas::ListaEntidades* tiros;

        Gerenciadores::Gerenciador_Colisoes* pGC;
        Gerenciadores::Gerenciador_Grafico* pGG;

        virtual void incluirProjeteisGC();

        virtual void desenharProjeteis();

        virtual void destruirProjeteis();

        virtual void destruirNeutralizados() = 0;

        virtual void salvarJogo(const std::string& caminho) = 0;
        void gravarNome(sf::RenderWindow* window);
        void criarHUD();
        void mostrarVidaPontos();
        bool fimFase();
    public:

        Fase(Gerenciadores::Gerenciador_Colisoes* gc, Gerenciadores::Gerenciador_Grafico* gg, int numPlayers_);
        virtual ~Fase();

        virtual void carregarJogo(const std::string& caminho) = 0;
        virtual void criarMapa(const std::string& caminhoJson) = 0;
        virtual void executar()=0;

        Listas::ListaEntidades* getListaEntidades();

        int getNumPlayers() const; 

        Entidades::Personagens::Jogador* getJogador1() const; 
        Entidades::Personagens::Jogador* getJogador2() const;

    };

}