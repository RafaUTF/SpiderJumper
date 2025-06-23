#pragma once
#include "Fase.h"

namespace Fases {
    
    class Fase1 : public Fase {

    private:
        bool proximaFase;

        void salvarJogo(const std::string& caminho);
        
        void setTrocarFase(bool t);
        void destruirNeutralizados();
    public:

        Fase1(Gerenciadores::Gerenciador_Colisoes* gc, Gerenciadores::Gerenciador_Grafico* gg, int numPlayers);
        ~Fase1();

        void executar();
        void criarMapa(const std::string& caminhoJson);
       
        void carregarJogo(const std::string& caminho);

        bool deveTrocarFase();
      
    };
}