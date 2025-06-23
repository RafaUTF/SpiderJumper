#include "Entidade.h"

namespace Entidades {
    
    Entidade::Entidade(Vector2f pos) : Ente(), vel(Vector2f(0.f, 0.f))
    {

        centralizarEntidade();
        corpo.setPosition(pos); // o centro do sprite ficará em pos

    }

    Entidade::~Entidade()
    {
    }
    sf::Vector2f Entidade::getcm()
    {
        return corpo.getPosition();
    }

    Vector2f Entidade::getRaio()
    {
        sf::FloatRect bounds = corpo.getGlobalBounds();
        return sf::Vector2f(
            bounds.width / 2.f,
            bounds.height / 2.f
        );
    }

    void Entidade::centralizarEntidade()
    {
        sf::FloatRect bounds = corpo.getLocalBounds();
        corpo.setOrigin(bounds.width / 2.f, bounds.height / 2.f); // origem no centro do sprite
    }

    void Entidade::setVel(Vector2f v)
    {
        vel = v;
    }

    Vector2f& Entidade::getVel()
    {
        return vel;
    }

    void Entidade::salvarPos(json& j)
    {
        j["x"] = getcm().x;
        j["y"] = getcm().y;
    }
}