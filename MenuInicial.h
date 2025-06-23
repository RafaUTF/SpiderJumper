#pragma once
#include "MenuBase.h"

class MenuInicial : public MenuBase {
private:
    sf::Text seletores[2];
    sf::Text instrucoes;
	sf::Text nomeJogo;
    int etapa;
    int nJogadores;
    int fase;

public:
    MenuInicial();
    ~MenuInicial();
    int mostrar(sf::RenderWindow& window);// override;
    int getNJogadores() const;
    int getFase() const;
};
