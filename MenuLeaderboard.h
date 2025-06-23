#pragma once
#include "MenuBase.h"
class MenuLeaderboard : public MenuBase
{
private:
	const int nPosicoes;
public:
	MenuLeaderboard();
	~MenuLeaderboard();
	int mostrar(sf::RenderWindow& window);// override;
};

