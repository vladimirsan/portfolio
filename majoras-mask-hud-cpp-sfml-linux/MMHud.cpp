#include "model/Clock.h"
#include "view/Clock.h"
#include "model/events.h"

#include <SFML/Graphics.hpp>
#include <cstdio>
#include <queue>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 300;

//For this small example the main function will act as the "controller"
int main(void)
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32),"Majora's Mask HUD");
	sf::Event event;
	
	//This queue represents the link between the model and the controller (this function)
	std::queue<Model::EventType> eventsQueue;

	//The Clock class represents the controller
	Model::Clock terminaClock(&eventsQueue);
	 //The only likely cause for an exeption would be the View::Clock constructor, so I enclose everything from this point
	 //with a try-catch block
	 try 
    {
		View::Clock clockHud(284,WINDOW_HEIGHT - 135);
		window.SetFramerateLimit(60);
		window.Clear();

		while(window.IsOpened())
		{
			//Updating SFML Events
			while(window.GetEvent(event))
			{
				if(event.Type == sf::Event::Closed)
					window.Close();

				if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Space)
				{
					if(terminaClock.isTimeSlow())
					{
						terminaClock.setNormalTime();
						clockHud.setNormalAnimation();
					}
					else
					{
						terminaClock.setSlowTime();
						clockHud.setSlowAnimation();
					}
				}
			}
			
			//Processing messages from the model
			Model::EventType queueEvent;
			while(!eventsQueue.empty())
			{
				queueEvent = eventsQueue.front();
				switch(queueEvent)
				{
					case Model::HOUR_CHANGE:
						clockHud.setHourNumber(terminaClock.getHours());
						break;
					case Model::DAY_TO_NIGHT:
						clockHud.setNightTime();
						break;
					case Model::NEW_DAY:
						clockHud.setDay(terminaClock.getDay());
						break;
					case Model::END:
						exit(0);
						break;
				}
				eventsQueue.pop();
			}
			terminaClock.update(window.GetFrameTime());

			//Debug Information
			//printf("FrameTime:%f -- Termina Clock:%d:%d:%f Day: %d \n",window.GetFrameTime(),terminaClock.getHours(),
			//		terminaClock.getMinutes(),terminaClock.getSeconds(),terminaClock.getDay());

			clockHud.update(window.GetFrameTime());

			window.Clear();
			clockHud.draw(&window);
			window.Display();
		}
	 }
	 catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        exit(0);
    }
	return 0;
}
