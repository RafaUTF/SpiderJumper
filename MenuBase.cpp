#include "MenuBase.h"

MenuBase::MenuBase() : opcaoSelecionada(0) {
    fonte.loadFromFile("upheavtt.ttf");
    if (texturaFundo.loadFromFile("fundomenu.png")) {
        spriteFundo.setTexture(texturaFundo);
        spriteFundo.setScale(960.0f / texturaFundo.getSize().x, 640.0f / texturaFundo.getSize().y);
    }
}

void MenuBase::desenharBase(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    window.draw(spriteFundo);
    for (auto& t : opcoes)
        window.draw(t);
}