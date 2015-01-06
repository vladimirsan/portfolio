#include "Clock.h"

using namespace Model;

Clock::Clock(std::queue<EventType>* eventsQueue)
	: m_seconds(0.0),m_minutes(0),m_hours(6),m_day(1),m_am(true),
	  m_timeConversionFactor(m_normalTimeFactor),m_eventsQueue(eventsQueue)
{}

void Clock::update(float timeDelta)
{

    m_seconds += terminaSeconds(timeDelta); 
    
    if(m_seconds >= 60.0f)
    {
		m_seconds -= 60.0f;
		m_minutes++;

		if(m_minutes == 60)
		{
			m_hours++;
			m_minutes = 0;

			checkForEvents();
			m_eventsQueue->push(Model::HOUR_CHANGE);
		}
    }
}

void Clock::checkForEvents()
{
	if(m_hours == 18)
	{
		if(m_am == true) //Night time
		{
			m_am = false;
			m_eventsQueue->push(Model::DAY_TO_NIGHT);
		}
		else 
		{ //Dawn of a new day
			m_am = true;
			m_day++;
			m_eventsQueue->push(Model::NEW_DAY);
		}
		m_hours = 6;
		m_minutes = 0;
		m_seconds = 0;
	}
	if(m_day == 3 && m_am == false && m_hours >= 12)
	{
		m_eventsQueue->push(Model::END);
		return;
	}
}
