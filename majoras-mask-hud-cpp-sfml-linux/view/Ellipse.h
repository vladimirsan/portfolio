#ifndef VIEW_ELLIPSE_INCLUDE
#define VIEW_ELLIPSE_INCLUDE

#include <SFML/System.hpp>

namespace View
{ 
	typedef struct Ellipse
	{
		sf::Vector2<int> center;
		int a,b;
	}Ellipse;
}

#endif
