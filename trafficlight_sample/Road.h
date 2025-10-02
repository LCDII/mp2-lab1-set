#include "Light.h"

class Road
{
	PTL* ptl;
	CTL* ctl;
public:
	Road();
	Road(const Road& road);
	Road& operator=(const Road & road);
	~Road();

	void switchLights();
	void printColor();
};