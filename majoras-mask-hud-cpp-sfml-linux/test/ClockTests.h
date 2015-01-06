#include "../model/Clock.h"
#include "../model/events.h"
#include "../cxxtest/TestSuite.h"
#include <cmath>
#include <queue>


class ClockTests : public CxxTest::TestSuite
{
  private:
	std::queue<Model::EventType> m_eventsQueue;
	Model::Clock m_clock;

	static const float maxError = 0.001;
  public:

    ClockTests() : m_eventsQueue(),m_clock(&m_eventsQueue)
    {}

    void setUp() {} 
    void tearDown(){} 

	void testAccelerationGetter()
	{
		TS_ASSERT_EQUALS(false,m_clock.isTimeSlow());
		m_clock.setSlowTime();
		TS_ASSERT_EQUALS(true,m_clock.isTimeSlow());
		m_clock.setNormalTime();
	}

    void testAdditionUpdate()
    {
		float initialSeconds = m_clock.getSeconds();	
		m_clock.update(0.02f);

		TS_ASSERT_EQUALS(initialSeconds + m_clock.terminaSeconds(0.02f),m_clock.getSeconds());	
    }

    void testMinuteChange()
    {
		m_clock.setSeconds(59.99f);
		m_clock.update(0.02f);

		float updateSeconds = 59.99f + m_clock.terminaSeconds(0.02f);

		TS_ASSERT_DELTA(1,m_clock.getMinutes(),maxError);
		TS_ASSERT_DELTA(updateSeconds - 60.0f, m_clock.getSeconds(),maxError);
    }

	void cleanQueue()
	{
		while(!m_eventsQueue.empty())
		{
			m_eventsQueue.pop();
		}
	}

	void testHourChange()
	{
		cleanQueue();

		m_clock.setSeconds(59.99);
		m_clock.setMinutes(59);
		m_clock.setHours(0);
		
		m_clock.update(0.02f);

		TS_ASSERT_EQUALS(0,m_clock.getMinutes());
		TS_ASSERT_EQUALS(1,m_clock.getHours());
		TS_ASSERT_EQUALS(m_eventsQueue.size(),1);
	}

	void testNormalSecondsConverter()
	{
		m_clock.setNormalTime();
		TS_ASSERT_DELTA(3600.0f/47.0f,m_clock.terminaSeconds(1),maxError);
		TS_ASSERT_DELTA(1.2765,m_clock.terminaSeconds(0.016666),maxError);
	}
	
	void testSlowSecondsConverter()
	{
		m_clock.setSlowTime();
		TS_ASSERT_DELTA(3600.0f/136.0f,m_clock.terminaSeconds(1),maxError);
		TS_ASSERT_DELTA(0.441158,m_clock.terminaSeconds(0.016666),maxError);
	}
	
	void testDayToNight()
	{
		cleanQueue();

		m_clock.setSeconds(59.99);
		m_clock.setMinutes(59);
		m_clock.setHours(17);
		m_clock.setAM(true);
		m_clock.setDay(1);

		m_clock.update(0.02f);

		TS_ASSERT_EQUALS(false,m_clock.isAM());
		TS_ASSERT_EQUALS(6,m_clock.getHours());
		TS_ASSERT_EQUALS(1,m_clock.getDay());
		TS_ASSERT_EQUALS(0,m_clock.getMinutes());
		TS_ASSERT_EQUALS(0,m_clock.getSeconds());
		TS_ASSERT_EQUALS(m_eventsQueue.size(),2);
	}

	void testNewDay()
	{
		cleanQueue();
		m_clock.setSeconds(59.99);
		m_clock.setMinutes(59);
		m_clock.setHours(17);
		m_clock.setAM(false);
		m_clock.setDay(1);

		m_clock.update(0.02f);
		TS_ASSERT_EQUALS(true,m_clock.isAM());
		TS_ASSERT_EQUALS(6,m_clock.getHours());
		TS_ASSERT_EQUALS(2,m_clock.getDay());
		TS_ASSERT_EQUALS(0,m_clock.getMinutes());
		TS_ASSERT_EQUALS(0,m_clock.getSeconds());
		TS_ASSERT_EQUALS(m_eventsQueue.size(),2);
	}
};
