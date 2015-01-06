#include "Clock.h"

using namespace View;

const float Clock::HOUR_HAND_NORMAL_ANGULAR_SPEED = 0.0057019974;
const float Clock::HOUR_HAND_SLOW_ANGULAR_SPEED   = 0.001924995499;

const float Clock::HOUR_NUMBER_NORMAL_ROTATION_SPEED = 0.319148936;
const float Clock::HOUR_NUMBER_SLOW_ROTATION_SPEED   = 0.110294117;

const float Clock::MINUTE_HAND_NORMAL_ANGULAR_SPEED  = 0.133684794;
const float Clock::MINUTE_HAND_SLOW_ANGULAR_SPEED    = 0.046199892;


View::Clock::Clock(int x,int y) throw (std::runtime_error)
	:m_position(x,y),
	 m_ellipseCenter(x+116,y+93),
	 m_minuteCircleCenter(x+117,y+74),
	 m_hourHandAngle(3.1416),   // pi
	 m_hourNumberAngle(3.1416),
	 m_minuteHandAngle(4.7123889), //(3pi)/2
	 m_hourNumberRotation(90)
{
	loadImages();
	loadImageNumbers();
	
	setNormalAnimation();

	//Loading the Sprites
	m_arc.SetImage(m_arcImage);
	m_hourHand.SetImage(m_sunImage);
	m_hourHand.SetCenter(17,17);
	m_minuteHand.SetImage(m_minuteHandImage);
	m_minuteHand.SetCenter(7,7);
	m_day.SetImage(m_1stDayImage);
	setHourNumber(6);
	m_hourNumber.SetCenter(10,8); //This is important in order to rotate the number ;)

	//Placing the "static" components
	m_arc.SetPosition(x,y);
	m_diamond.SetPosition(x+69,y+28);
	m_day.SetPosition(x+69,y + 28);

	//Placing the "dynamic" components
	update(0);
}

void View::Clock::update(float timeDelta)
{
	m_hourHandAngle += timeDelta*m_hourHandAngularSpeed;
	m_hourNumberAngle += timeDelta*m_hourHandAngularSpeed;
	m_hourNumberRotation -= timeDelta*m_hourNumberRotationSpeed;
	m_minuteHandAngle += timeDelta*m_minuteHandAngularSpeed;

	setHourHandPosition();
	setHourNumberPositionAndAngle();
	setMinuteHandPosition();
}

void View::Clock::draw(sf::RenderWindow *window)
{
	window->Draw(m_arc);
	window->Draw(m_diamond);
	window->Draw(m_day);
	window->Draw(m_hourHand);
	window->Draw(m_hourNumber);
	window->Draw(m_minuteHand);
}

//I could refactor the ellipse positioning parte of these 3 methods into one method
inline void View::Clock::setHourHandPosition()
{
	m_tempPoint.x = m_ellipseCenter.x + (ELLIPSE_A * cosf(m_hourHandAngle));
	m_tempPoint.y = m_ellipseCenter.y + (ELLIPSE_B * sinf(m_hourHandAngle));
	m_hourHand.SetPosition(m_tempPoint.x,m_tempPoint.y);
}

inline void View::Clock::setMinuteHandPosition()
{
	m_tempPoint.x = m_minuteCircleCenter.x + (MINUTE_CIRCLE_RADIUS * cosf(m_minuteHandAngle));
	m_tempPoint.y = m_minuteCircleCenter.y + (MINUTE_CIRCLE_RADIUS * sinf(m_minuteHandAngle));
	m_minuteHand.SetPosition(m_tempPoint.x,m_tempPoint.y);
}
void View::Clock::setHourNumberPositionAndAngle()
{
	m_tempPoint.x = m_ellipseCenter.x + (HOUR_ELLIPSE_A * cosf(m_hourNumberAngle));
	m_tempPoint.y = m_ellipseCenter.y + (HOUR_ELLIPSE_B * sinf(m_hourNumberAngle));
	m_hourNumber.SetPosition(m_tempPoint.x,m_tempPoint.y);
	m_hourNumber.SetRotation(m_hourNumberRotation);
}

void View::Clock::loadImages() throw(std::runtime_error)
{
	loadImage(&m_arcImage,"images/arc.png");
	loadImage(&m_sunImage,"images/sun.png");
	loadImage(&m_moonImage,"images/moon.png");
	loadImage(&m_greenDiamondImage,"images/greenDiamond.png");
	loadImage(&m_blueDiamondImage,"images/blueDiamond.png");
	loadImage(&m_minuteHandImage,"images/minuteHand.png");


	loadImage(&m_1stDayImage,"images/days/1st.png");
	loadImage(&m_2ndDayImage,"images/days/2nd.png");
	loadImage(&m_finalDayImage,"images/days/final.png");
}

void View::Clock::loadImage(sf::Image* image,const char* filename,bool noSmooth) 
	throw(std::runtime_error)
{
	if(!image->LoadFromFile(filename))
		throw std::runtime_error("Cannot Load Images");
	if(noSmooth)
		image->SetSmooth(false);
}


void View::Clock::loadImageNumbers() throw(std::runtime_error)
{
	// I could use a string stream here but I think it might be overkill
	loadImage(&m_numberImages[0],"images/numbers/1.png",false);
	loadImage(&m_numberImages[1],"images/numbers/2.png",false);
	loadImage(&m_numberImages[2],"images/numbers/3.png",false);
	loadImage(&m_numberImages[3],"images/numbers/4.png",false);
	loadImage(&m_numberImages[4],"images/numbers/5.png",false);
	loadImage(&m_numberImages[5],"images/numbers/6.png",false);
	loadImage(&m_numberImages[6],"images/numbers/7.png",false);
	loadImage(&m_numberImages[7],"images/numbers/8.png",false);
	loadImage(&m_numberImages[8],"images/numbers/9.png",false);
	loadImage(&m_numberImages[9],"images/numbers/10.png",false);
	loadImage(&m_numberImages[10],"images/numbers/11.png",false);
	loadImage(&m_numberImages[11],"images/numbers/12.png",false);
}

void View::Clock::setSlowAnimation()
{
	m_hourHandAngularSpeed = HOUR_HAND_SLOW_ANGULAR_SPEED;
	m_hourNumberRotationSpeed = HOUR_NUMBER_SLOW_ROTATION_SPEED;
	m_minuteHandAngularSpeed = MINUTE_HAND_SLOW_ANGULAR_SPEED;

	m_diamond.SetImage(m_blueDiamondImage);	
}

void View::Clock::setNormalAnimation()
{
	m_hourHandAngularSpeed = HOUR_HAND_NORMAL_ANGULAR_SPEED;
	m_hourNumberRotationSpeed = HOUR_NUMBER_NORMAL_ROTATION_SPEED;
	m_minuteHandAngularSpeed = MINUTE_HAND_NORMAL_ANGULAR_SPEED;

	m_diamond.SetImage(m_greenDiamondImage);
}


void View::Clock::setDay(int day)
{
	assert(day > 0 && day < 4);
	
	switch(day)
	{
		case 1:
			m_day.SetImage(m_1stDayImage);
		break;
		case 2:
			m_day.SetImage(m_2ndDayImage);
		break;
		case 3:
			m_day.SetImage(m_finalDayImage);
		break;
	}

	m_hourHand.SetImage(m_sunImage);	
	m_hourHandAngle = 3.1416;
	m_hourNumberAngle = 3.1416;
	m_minuteHandAngle = 4.712388;
	m_hourNumberRotation = 90;
	setHourNumber(6);
}

void View::Clock::setNightTime()
{
	m_hourHand.SetImage(m_moonImage);	
	m_hourHandAngle = 3.1416;
	m_hourNumberAngle = 3.1416;
	m_minuteHandAngle = 4.712388;
	m_hourNumberRotation = 90;
	setHourNumber(6);
}


void View::Clock::setHourNumber(int number)
{
	assert(number > 5 && number < 19);
	if(number > 12)
		number -= 12;

	number--;
	m_hourNumber.SetImage(m_numberImages[number]);
}
