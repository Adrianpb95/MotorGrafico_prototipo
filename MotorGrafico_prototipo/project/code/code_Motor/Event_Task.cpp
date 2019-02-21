/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Event_Task.hpp"

#include <Windows.h>
#include <mmsystem.h>
#include <vector>

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	Event_Task::Event_Task(Scene * scene, int priority, bool finished)
		: Task(scene, priority, finished),
		updater(new Event_Updater(scene)),
		move_up(MOVE_UP), move_down(MOVE_DOWN), 
		move_right(MOVE_RIGHT), move_left(MOVE_LEFT), 
		turn_right(TURN_RIGHT), turn_left(TURN_LEFT)
	{
		window = scene->get_view()->get_window();				
	}

	void Event_Task::initialize()
	{
		for (auto & component : components)
		{
			component->initialize();
		}
	}

	void Event_Task::run()
	{		
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
				{					
					scene->get_kernel()->stop();
					break;
				}

				case Event::Resized:
				{
					Vector2u window_size = window->getSize();
					scene->get_view()->resize(window_size.x, window_size.y);
					break;
				}

				case Event::KeyPressed:
				{
					switch (event.key.code)
					{
						//Se lanza el mensaje de movimiento de jugador y se actualiza la mision
						case Keyboard::W: 
						{ 
							scene->get_dispatcher()->send_msg(move_up);
							updater->quest_update();							
							break; 
						}

						case Keyboard::S: 
						{ 
							scene->get_dispatcher()->send_msg(move_down);
							updater->quest_update();							
							break; 
						}

						case Keyboard::D: 
						{
							scene->get_dispatcher()->send_msg(move_right);
							updater->quest_update();							
							break; 
						}

						case Keyboard::A: 
						{ 
							scene->get_dispatcher()->send_msg(move_left);
							updater->quest_update();							
							break;
						}

						case Keyboard::Q:
						{
							scene->get_dispatcher()->send_msg(turn_left);
							break;
						}

						case Keyboard::E:
						{
							scene->get_dispatcher()->send_msg(turn_right);
							break;
						}

						case Keyboard::Escape: 
						{ 
							scene->get_kernel()->stop(); 
							break; 
						}
					}	
					break;
				}
			}
		}		
	}

	void Event_Task::finalize()
	{
		for (auto & component : components)
		{
			component->finalize();
		}
	}
}