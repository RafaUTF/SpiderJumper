#pragma once
#include "MenuBase.h"

class MenuPause : public MenuBase {
private:
    bool pausado;
public:
    MenuPause();
    ~MenuPause();
    int mostrar(sf::RenderWindow& window);// override;
    void setAtivo(const bool b=true);
};