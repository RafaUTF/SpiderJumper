#include "MenuInicial.h"
#include "MenuLeaderboard.h"

MenuInicial::MenuInicial() : etapa(0), nJogadores(1), fase(1) {
    
    
    nomeJogo.setFont(fonte);
    nomeJogo.setString("SpiderJumper");
    nomeJogo.setCharacterSize(60);
    nomeJogo.setFillColor(sf::Color::White);
    sf::FloatRect nJ = nomeJogo.getLocalBounds();
    nomeJogo.setOrigin(nJ.width / 2, nJ.height / 2);
    nomeJogo.setPosition(480, 100);
    
    titulo.setFont(fonte);
    titulo.setString("Configurar Jogo");
    titulo.setCharacterSize(40);
    titulo.setFillColor(sf::Color::White);
    sf::FloatRect tb = titulo.getLocalBounds();
    titulo.setOrigin(tb.width / 2, tb.height / 2);
    titulo.setPosition(480, 100);

    seletores[0].setFont(fonte);
    seletores[0].setCharacterSize(32);
    seletores[0].setFillColor(sf::Color::White);
    seletores[0].setPosition(480, 220);

    seletores[1].setFont(fonte);
    seletores[1].setCharacterSize(32);
    seletores[1].setFillColor(sf::Color::White);
    seletores[1].setPosition(480, 270);

    instrucoes.setFont(fonte);
    instrucoes.setCharacterSize(17);
    instrucoes.setFillColor(sf::Color::White);
    instrucoes.setPosition(480, 320);
}

MenuInicial::~MenuInicial()
{
}

int MenuInicial::mostrar(sf::RenderWindow& window) {
    etapa = 0;
    opcaoSelecionada = 0;
    

    std::vector<std::string> nomes = { "Carregar Jogo", "Novo Jogo", "Leaderboard" };
    opcoes.clear();

    float yStart = 220;
    for (int i = 0; i < (int)nomes.size(); ++i) {
        sf::Text t;
        t.setFont(fonte);
        t.setString(nomes[i]);
        t.setCharacterSize(40);
        t.setFillColor(i == 0 ? sf::Color::Blue : sf::Color::White);
        sf::FloatRect br = t.getLocalBounds();
        t.setOrigin(br.width / 2, br.height / 2);
        t.setPosition(480, yStart + i * 60);
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
                        if (opcaoSelecionada == 1) {
                            etapa = 1; // Configurar novo jogo
                        }
                        else if (opcaoSelecionada == 2) {
                            MenuLeaderboard leaderboard;
                            leaderboard.mostrar(window);
                            continue; // volta ao menu inicial
                        }
                        else {
                            return opcaoSelecionada; // Carregar jogo, etc.
                        }
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
                        return 1; // Novo jogo
                    case sf::Keyboard::Escape:
                        etapa = 0;
                        break;
                    default: break;
                    }
                }
            }
        }

        window.clear();
        window.draw(spriteFundo);



        if (etapa == 0) {
            sf::FloatRect bounds = nomeJogo.getLocalBounds();
            nomeJogo.setOrigin(bounds.width / 2, bounds.height / 2);
            nomeJogo.setPosition(480, 100);
            window.draw(nomeJogo);
            
            for (auto& t : opcoes) window.draw(t);
        }
        else {
            titulo.setString("Configurar Novo Jogo");
            sf::FloatRect bounds = titulo.getLocalBounds();
            titulo.setOrigin(bounds.width / 2, bounds.height / 2);
            titulo.setPosition(480, 100);
            window.draw(titulo);

            seletores[0].setString("Jogadores: " + std::to_string(nJogadores));
            sf::FloatRect bounds0 = seletores[0].getLocalBounds();
            seletores[0].setOrigin(bounds0.width / 2, bounds0.height / 2);
            seletores[0].setPosition(480, 220);

            seletores[1].setString("Fase: " + std::to_string(fase));
            sf::FloatRect bounds1 = seletores[1].getLocalBounds();
            seletores[1].setOrigin(bounds1.width / 2, bounds1.height / 2);
            seletores[1].setPosition(480, 270);

            for (auto& s : seletores) window.draw(s);

            instrucoes.setString("W S Jogadores | A D Fase | Enter para jogar | Esc para voltar");
            sf::FloatRect bi = instrucoes.getLocalBounds();
            instrucoes.setOrigin(bi.width / 2, bi.height / 2);
            instrucoes.setPosition(480, 320);
            window.draw(instrucoes);
        }

        window.display();
    }

    return 2;
}

int MenuInicial::getNJogadores() const
{
    return nJogadores;
}

int MenuInicial::getFase() const
{
    return fase;
}
