#include "Menu.h"
#include <iostream>

Menu::Menu()
    : etapa(0), opcaoSelecionada(0), nJogadores(1), fase(1)
{
    fonte.loadFromFile("arial.ttf");

    titulo.setFont(fonte);
    titulo.setString("Configurar Jogo");
    titulo.setCharacterSize(60);
    titulo.setFillColor(sf::Color::White);
    sf::FloatRect tb = titulo.getLocalBounds();
    titulo.setOrigin(tb.width / 2, tb.height / 2);
    titulo.setPosition(900, 150);

    seletores[0].setFont(fonte);
    seletores[0].setCharacterSize(32);
    seletores[0].setFillColor(sf::Color::White);
    seletores[0].setPosition(900, 300);

    seletores[1].setFont(fonte);
    seletores[1].setCharacterSize(32);
    seletores[1].setFillColor(sf::Color::White);
    seletores[1].setPosition(900, 360);

    instrucoes.setFont(fonte);
    instrucoes.setString("Pressione L para Leaderboard");
    instrucoes.setCharacterSize(24);
    instrucoes.setFillColor(sf::Color::White);
    sf::FloatRect bi = instrucoes.getLocalBounds();
    instrucoes.setOrigin(bi.width / 2, bi.height / 2);
    instrucoes.setPosition(900, 430);

    if (texturaFundo.loadFromFile("fundomenu.png")) {
        spriteFundo.setTexture(texturaFundo);
        spriteFundo.setScale(1800.0f / texturaFundo.getSize().x,
            900.0f / texturaFundo.getSize().y);
    }
}

Menu::~Menu() {}

int Menu::mostrar(sf::RenderWindow& window) {
    etapa = 0;
    opcaoSelecionada = 0;

    // Tela inicial: Carregar, Novo, Leaderboard
    std::vector<std::string> nomes = { "Carregar Jogo", "Novo Jogo", "Leaderboard" };
    opcoes.clear();

    float yStart = 300;
    for (int i = 0; i < (int)nomes.size(); ++i) {
        sf::Text t;
        t.setFont(fonte);
        t.setString(nomes[i]);
        t.setCharacterSize(40);
        t.setFillColor(i == 0 ? sf::Color::Blue : sf::Color::White);
        sf::FloatRect br = t.getLocalBounds();
        t.setOrigin(br.width / 2, br.height / 2);
        t.setPosition(900, yStart + i * 100);
        opcoes.push_back(t);
    }

    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
            if (ev.type == sf::Event::KeyPressed) {
                if (etapa == 0) {
                    switch (ev.key.code) {
                    case sf::Keyboard::Up:
                        if (opcaoSelecionada > 0) opcaoSelecionada--;
                        break;
                    case sf::Keyboard::Down:
                        if (opcaoSelecionada + 1 < (int)opcoes.size()) opcaoSelecionada++;
                        break;
                    case sf::Keyboard::Enter:
                        if (opcaoSelecionada == 1) { // Novo Jogo
                            etapa = 1;
                        }
                        else {
                            return opcaoSelecionada; // 0 = Carregar, 2 = Leaderboard
                        }
                        break;
                    default: break;
                    }
                    for (int i = 0; i < (int)opcoes.size(); ++i)
                        opcoes[i].setFillColor(i == opcaoSelecionada ? sf::Color::Blue : sf::Color::White);
                }
                else if (etapa == 1) {
                    switch (ev.key.code) {
                    case sf::Keyboard::S:
                        if (nJogadores > 1) nJogadores--;
                        break;
                    case sf::Keyboard::W:
                        if (nJogadores < 2) nJogadores++;
                        break;
                    case sf::Keyboard::A:
                        if (fase > 1) fase--;
                        break;
                    case sf::Keyboard::D:
                        if (fase < 2) fase++;
                        break;
                    case sf::Keyboard::Enter:
                        return 1; // Iniciar novo jogo
                    case sf::Keyboard::Escape:
                        etapa = 0; // Voltar ao menu inicial
                        break;
                    default: break;
                    }
                }
            }
        }

        window.clear();
        window.draw(spriteFundo);

        if (etapa == 0) {
            for (auto& t : opcoes) window.draw(t);
        }
        else if (etapa == 1) {
            titulo.setString("Configurar Novo Jogo");
            sf::FloatRect bounds2 = titulo.getLocalBounds();
            titulo.setOrigin(bounds2.width / 2, bounds2.height / 2);
			titulo.setPosition(900, 150);
            window.draw(titulo);

            seletores[0].setString("Jogadores: " + std::to_string(nJogadores));
            sf::FloatRect bounds0 = seletores[0].getLocalBounds();
            seletores[0].setOrigin(bounds0.width / 2, bounds0.height / 2);
            seletores[0].setPosition(900, 300);

            seletores[1].setString("Fase: " + std::to_string(fase));
            sf::FloatRect bounds1 = seletores[1].getLocalBounds();
            seletores[1].setOrigin(bounds1.width / 2, bounds1.height / 2);
            seletores[1].setPosition(900, 360);

            window.draw(seletores[0]);
            window.draw(seletores[1]);

            instrucoes.setString("W S Jogadores | A D Fase | Enter para jogar | Esc para voltar");
            sf::FloatRect bi = instrucoes.getLocalBounds();
            instrucoes.setOrigin(bi.width / 2, bi.height / 2);
            window.draw(instrucoes);
        }

        window.display();
    }

    return 2;
}