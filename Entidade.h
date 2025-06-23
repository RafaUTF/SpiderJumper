#pragma once
#include "Ente.h"

namespace Entidades {

	class Entidade : public Ente
	{
	protected:
		Vector2f vel;
	public:
		
		Entidade(Vector2f pos=Vector2f(0.f,0.f));

		virtual ~Entidade();

		Vector2f getcm();

		Vector2f getRaio();
	
		void centralizarEntidade();

		virtual void executar() = 0;

		void setVel(Vector2f v = (Vector2f(0.f, 0.f)));

		Vector2f& getVel();

		virtual void salvar(json& j) = 0;

		void salvarPos(json& j);
	};
}