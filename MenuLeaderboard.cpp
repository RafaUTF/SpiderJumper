#include "MenuLeaderboard.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

MenuLeaderboard::MenuLeaderboard() :
    nPosicoes(N_LEADERBOARD)
{
    std::ifstream in("leaderboard.json");
    json lb = json::array();
    if (in.is_open()) in >> lb;

    titulo.setFont(fonte);
    titulo.setString("Leaderboard");
    titulo.setCharacterSize(50);
    titulo.setFillColor(sf::Color::White);
    sf::FloatRect bounds = titulo.getLocalBounds();
    titulo.setOrigin(bounds.width / 2, bounds.height / 2);
    titulo.setPosition(480, 50);

    float y = 150;
    int i = 1;

    int j = 0;
    for (auto& entry : lb) {
        sf::Text t;
        t.setFont(fonte);
        t.setCharacterSize(30);
        t.setFillColor(sf::Color::White);

        std::string nome = entry["nome"];
        int pontos = entry["pontuacao"];
        t.setString(std::to_string(i++) + ". " + nome + " - " + std::to_string(pontos));
        t.setPosition(200, y);
        y += 40;
        opcoes.push_back(t);

        j++;
        if (j >= nPosicoes)
            break;
    }

    sf::Text voltar;
    voltar.setFont(fonte);
    voltar.setCharacterSize(25);
    voltar.setFillColor(sf::Color::White);
    voltar.setString("Pressione ESC para voltar");
    voltar.setPosition(300, 550);
    opcoes.push_back(voltar);
}

MenuLeaderboard::~MenuLeaderboard()
{}


int MenuLeaderboard::mostrar(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
                return 0;
        }

        window.clear();
        desenharBase(window);
        window.draw(titulo);
        for (auto& t : opcoes) window.draw(t);
        window.display();
    }

    return 0;
}





