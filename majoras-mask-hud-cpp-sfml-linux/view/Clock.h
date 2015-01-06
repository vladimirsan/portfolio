#ifndef VIEW_CLOCK_INCLUDE
#define VIEW_CLOCK_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cmath>
#include <cassert>
#include <stdexcept>

namespace View
{ 
   class Clock 
	{
		private:
			//Drawing Constants
			static const int ELLIPSE_A = 111;
			static const int ELLIPSE_B = 88;
			static const int HOUR_ELLIPSE_A = ELLIPSE_A * 1.25;
			static const int HOUR_ELLIPSE_B = ELLIPSE_B * 1.35;
			static const int MINUTE_CIRCLE_RADIUS = 48;

			static const float HOUR_HAND_NORMAL_ANGULAR_SPEED;
			static const float HOUR_HAND_SLOW_ANGULAR_SPEED;

			static const float HOUR_NUMBER_NORMAL_ROTATION_SPEED;
			static const float HOUR_NUMBER_SLOW_ROTATION_SPEED;

			static const float MINUTE_HAND_NORMAL_ANGULAR_SPEED;
			static const float MINUTE_HAND_SLOW_ANGULAR_SPEED;

	   	Clock(Clock&);
		   Clock& operator=(const Clock& arg);

			sf::Vector2<int> m_position;
			sf::Vector2<int> m_ellipseCenter;
			sf::Vector2<int> m_minuteCircleCenter;

			float m_hourHandAngle;
			float m_hourNumberAngle;
			float m_minuteHandAngle;

			//I only use this for "optimization purposes" 
			sf::Vector2<int> m_tempPoint;
			
			//All the required images for drawing the clock
			sf::Image m_numberImages[12];	

			sf::Image m_arcImage;
			sf::Image m_sunImage;
			sf::Image m_moonImage;
			sf::Image m_minuteHandImage;

			sf::Image m_greenDiamondImage;
			sf::Image m_blueDiamondImage;

			sf::Image m_1stDayImage;
			sf::Image m_2ndDayImage;
			sf::Image m_finalDayImage;

			sf::Sprite m_arc;
			sf::Sprite m_hourHand;
			sf::Sprite m_minuteHand;
			sf::Sprite m_hourNumber;
			sf::Sprite m_diamond;
			sf::Sprite m_day;

			float m_hourHandAngularSpeed;
			float m_hourNumberRotationSpeed;
			float m_hourNumberRotation;
			float m_minuteHandAngularSpeed;
			
			void setHourHandPosition();
			void setMinuteHandPosition();
			void setHourNumberPositionAndAngle();
			void loadImages() throw(std::runtime_error);
			void loadImage(sf::Image* image,const char* filename,bool noSmooth = true) throw(std::runtime_error);
			void loadImageNumbers() throw(std::runtime_error);
		public:
	   	 Clock(int x,int y) throw (std::runtime_error);

			 void draw(sf::RenderWindow* window); 
			 void update(float timeDelta);
			 
			 void setSlowAnimation();
			 void setNormalAnimation();
			 void setDay(int day);
			 void setNightTime();
			 void setHourNumber(int number);
   };
}

#endif
