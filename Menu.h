#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

class Menu {
private:
    sf::Font fonte;
    sf::Text titulo;
    std::vector<sf::Text> opcoes;       // Opções após configuração (Novo, Carregar, Sair)
    sf::Text seletores[2];              // Jogadores e Fase
    sf::Text instrucoes;
    int etapa;                          // 0=configuração, 1=escolha ação
    int opcaoSelecionada;
    int nJogadores;
    int fase;

    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;

public:
    Menu();
    ~Menu();

    int mostrar(sf::RenderWindow& window);

    int getNJogadores() const { return nJogadores; }
    int getFase() const { return fase; }
};
