#include "Obstaculo.h"



using namespace Entidades::Personagens;

namespace Entidades {
	namespace Obstaculos {

		Obstaculo::Obstaculo(Vector2f pos) :
			danoso(false), Entidade(pos)
		{
		}

		Obstaculo::~Obstaculo()
		{
		}

		bool Obstaculo::isDanoso() const { return danoso; }


	}
}