/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Event_Updater.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	Event_Updater::Event_Updater(Scene * scene_aux)
	{
		scene = scene_aux;
		num = 1;

		scene->get_dispatcher()->add_listener(MOVE_UP, *this);
		scene->get_dispatcher()->add_listener(MOVE_DOWN, *this);
		scene->get_dispatcher()->add_listener(MOVE_RIGHT, *this);
		scene->get_dispatcher()->add_listener(MOVE_LEFT, *this);
		scene->get_dispatcher()->add_listener(TURN_RIGHT, *this);
		scene->get_dispatcher()->add_listener(TURN_LEFT, *this);
	}

	void Event_Updater::handle(Message & msg)
	{
		//Guardamos el player
		player = dynamic_cast<Transform_Component*>(scene->get_entity("player")->get_component("transform").get());

		//Lo movemos dependiendo del msg recibido
		switch (msg)
		{
			//1º se delimitan los movimientos: mov solo dentro de la ventana
			//2º si no se puede mover, salta un sonido de error
			case MOVE_UP:
			{
				if (player->get_position().y < 0.4f)
				{
					player->move(0.f, 0.1f, 0.f, 0.f, 0.f);
				}
				else PlaySound(TEXT("../../../assets/error"), NULL, SND_ASYNC | SND_FILENAME);
				break;
			}

			case MOVE_DOWN:
			{
				if (player->get_position().y > -2.8f)
				{
					player->move(0.f, -0.1f, 0.f, 0.f, 0.f);
				}
				else PlaySound(TEXT("../../../assets/error"), NULL, SND_ASYNC | SND_FILENAME);
				break;
			}

			case MOVE_RIGHT:
			{
				if (player->get_position().x < 2.8f)
				{
					player->move(0.1f, 0.f, 0.f, 0.f, 0.f);
				}
				else PlaySound(TEXT("../../../assets/error"), NULL, SND_ASYNC | SND_FILENAME);
				break;
			}

			case MOVE_LEFT:
			{
				if (player->get_position().x > -2.8f)
				{
					player->move(-0.1f, 0.f, 0.f, 0.f, 0.f);
				}
				else PlaySound(TEXT("../../../assets/error"), NULL, SND_ASYNC | SND_FILENAME);
				break;
			}

			case TURN_LEFT:
			{
				player->move(0.f, 0.f, 0.f, -15.f, 0.f);
				break;
			}

			case TURN_RIGHT:
			{
				player->move(0.f, 0.f, 0.f, 15.f, 0.f);
				break;
			}
		}
	}

	void Event_Updater::quest_update()
	{
		//1º si el player esta en la posicion de una de las cajas (aproximadamente) y sigue bien el orden, la recoge y deja de renderizarla
		//2º si las recoge en el orden adecuado, salta un sonido de error
		if ((player->get_position().x < 0.4f  && player->get_position().x > -0.4f) && (player->get_position().y < 0.4f && player->get_position().y > -0.4f) && num <= 1)
		{
			if (num == 1)
			{
				//puntero a esa caja, para quitarle el render
				mesh = dynamic_cast<Render_Component*>(scene->get_entity("cube1")->get_component("render").get());
				mesh->get_mesh()->set_render(false);
				num++;
			}
			else PlaySound(TEXT("../../../assets/error"), NULL, SND_ASYNC | SND_FILENAME);
		}

		else if ((player->get_position().x < 2.8f && player->get_position().x > 1.6f) && (player->get_position().y > -2.f && player->get_position().y < -0.8f) && num <= 2)
		{
			if (num == 2)
			{
				mesh = dynamic_cast<Render_Component*>(scene->get_entity("cube2")->get_component("render").get());
				mesh->get_mesh()->set_render(false);
				num++;
			}
			else PlaySound(TEXT("../../../assets/error"), NULL, SND_ASYNC | SND_FILENAME);
		}

		else if ((player->get_position().x < 2.4f && player->get_position().x > 1.2f) && (player->get_position().y < -2.6f) && num <= 3)
		{
			if (num == 3)
			{
				mesh = dynamic_cast<Render_Component*>(scene->get_entity("cube3")->get_component("render").get());
				mesh->get_mesh()->set_render(false);
				num++;
			}
			else PlaySound(TEXT("../../../assets/error"), NULL, SND_ASYNC | SND_FILENAME);
		}

		else if ((player->get_position().x > -2.4f && player->get_position().x < -1.2f) && (player->get_position().y < -2.6f) && num <= 4)
		{
			if (num == 4)
			{
				mesh = dynamic_cast<Render_Component*>(scene->get_entity("cube4")->get_component("render").get());
				mesh->get_mesh()->set_render(false);
				num++;
			}
			else PlaySound(TEXT("../../../assets/error"), NULL, SND_ASYNC | SND_FILENAME);
		}

		else if ((player->get_position().x > -2.8f && player->get_position().x < -1.6f) && (player->get_position().y > -2.f && player->get_position().y - 0.8f) && num <= 5)
		{
			if (num == 5)
			{
				mesh = dynamic_cast<Render_Component*>(scene->get_entity("cube5")->get_component("render").get());
				mesh->get_mesh()->set_render(false);
				num++;
				//Sonido de victoria al recoger la ultima caja
				PlaySound(TEXT("../../../assets/win"), NULL, SND_ASYNC | SND_FILENAME);
			}
			else PlaySound(TEXT("../../../assets/error"), NULL, SND_ASYNC | SND_FILENAME);
		}
	}
}