// MenuBase.h
#pragma once
#include "stdafx.h"
#include <vector>
#include <string>

class MenuBase {
protected:
    sf::Font fonte;
    sf::Text titulo;
    std::vector<sf::Text> opcoes;
    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;
    int opcaoSelecionada;

    void desenharBase(sf::RenderWindow& window);

public:
    MenuBase();
    virtual ~MenuBase() {}

    virtual int mostrar(sf::RenderWindow& window) = 0;
};