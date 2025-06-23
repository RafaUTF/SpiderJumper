#pragma once
#include "Fase.h"


namespace Fases {

    class Fase2 : public Fase {

    private:

        vector<Entidades::Personagens::Chefao*> LCs;//lista de chefes

        void salvarJogo(const std::string& caminho);
        void destruirNeutralizados();
        void criarChefe(Vector2f pos);

    public:


        Fase2(Gerenciadores::Gerenciador_Colisoes* gc, Gerenciadores::Gerenciador_Grafico* gg, int numPlayers);
        ~Fase2();

        void executar();
        void criarMapa(const std::string& caminhoJson);

        void carregarJogo(const std::string& caminho);
        


    };

}