#include "MenuPause.h"

MenuPause::MenuPause(): pausado(false) {
    std::vector<std::string> nomes = { "Continuar", "Salvar Jogo", "Sair" };
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
}

MenuPause::~MenuPause()
{
}

int MenuPause::mostrar(sf::RenderWindow& window) {
    if (!pausado) return 2;//volta para o jogo
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) window.close();
            if (ev.type == sf::Event::KeyPressed) {
                switch (ev.key.code) {
                case sf::Keyboard::Up:
                    if (opcaoSelecionada > 0) opcaoSelecionada--;
                    break;
                case sf::Keyboard::Down:
                    if (opcaoSelecionada + 1 < (int)opcoes.size()) opcaoSelecionada++;
                    break;
                case sf::Keyboard::Enter:
                    return opcaoSelecionada; // 0 = continuar, 1 = salvar, 2 = sair
                default: break;
                }

                for (int i = 0; i < (int)opcoes.size(); ++i)
                    opcoes[i].setFillColor(i == opcaoSelecionada ? sf::Color::Blue : sf::Color::White);
            }
        }

        window.clear();
        desenharBase(window);
        window.display();
    }

    return 0;
}

void MenuPause::setAtivo(const bool b)
{
    pausado = b;
}
