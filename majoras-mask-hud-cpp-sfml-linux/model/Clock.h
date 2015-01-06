#ifndef MODEL_CLOCK_INCLUDE
#define MODEL_CLOCK_INCLUDE

#include "events.h"
#include <queue>

namespace Model
{ 
	
    class Clock
    {
	private:
	    Clock(Clock&);
	    Clock& operator=(const Clock& clock);

		static const float m_normalTimeFactor = 76.59574;
		static const float m_slowTimeFactor =   26.47059;

		float m_seconds;
		int m_minutes;
		int m_hours;
		int m_day;

		bool m_am;
		float m_timeConversionFactor;
		
		std::queue<EventType>* m_eventsQueue;
		void checkForEvents();
	public:
	    Clock(std::queue<EventType>* eventsQueue);

		//Getters
	   float getSeconds() { return m_seconds; }
	   int getMinutes()   { return m_minutes; }
	   int getHours()     { return m_hours; }
		int getDay()       { return m_day; }
		bool isAM()        { return m_am; }
		bool isTimeSlow() { return m_timeConversionFactor == m_slowTimeFactor; }

//Breaking encapsulation only for test driven development purposes
#ifdef MM_TDD		
	    void setSeconds(float seconds) { m_seconds = seconds; }
	    void setMinutes(int minutes) { m_minutes = minutes; }
	    void setHours(int hours) { m_hours = hours; }
		void setDay(int day) { m_day = day; }
		void setAM(bool am) { m_am = am; } 
#endif

		////////////////////////////////////////////////////////

	    void update(float timeDelta);

		//Manipulate the passage of time
		void setSlowTime() { m_timeConversionFactor = m_slowTimeFactor; }
		void setNormalTime() { m_timeConversionFactor = m_normalTimeFactor; }

		//Convert "normal" seconds into "termina" seconds
		float terminaSeconds(float normalSeconds) { return (normalSeconds * m_timeConversionFactor); }
    };
}

#endif
