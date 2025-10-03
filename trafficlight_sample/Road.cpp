#include "Road.h"
#include <iostream>
using namespace std;
#include<stdint.h>


Road::Road()
{
    ptl = new PTL();
    ctl = new CTL();
}
Road::Road(const Road& road)
{
    ptl = new PTL(*road.ptl);
    ctl = new CTL(*road.ctl);
}
Road& Road::operator=(const Road & road)
{
    if (this == &road) return *this;

    delete ptl;
    delete ctl;

    ptl = new PTL(*road.ptl);
    ctl = new CTL(*road.ctl);
    return *this;
}
Road::~Road()
{
    delete ptl;
    delete ctl;
}

void Road::switchLights()
{
    if (ptl->isGreen())
    {
        ptl->getSet()->InsElem(1);
        ptl->getSet()->DelElem(0);
    }
    else if(ptl->isRed() && ctl->isGreen())
    {
        ptl->getSet()->InsElem(0);
        ptl->getSet()->DelElem(1);
    }
    if (ctl->isGreen())
    {
        ctl->getSet()->InsElem(2);
        ctl->getSet()->DelElem(0);
    }
    else if (ctl->isYellow())
    {
        ctl->getSet()->InsElem(0);
        ctl->getSet()->DelElem(1);
    }
    else if (ctl->isRed())
    {
        ctl->getSet()->InsElem(1);
        ctl->getSet()->DelElem(2);
    }
}
void Road::printColor()
{
    if (ptl->isGreen() && ctl->isRed())
    {
        cout << "p:green"<<endl;
        cout << "c:red" << endl;
    }
    else if(ptl->isRed() && ctl->isYellow())
    {
        cout << "p:red" << endl;
        cout << "c:yellow" << endl;
    }
    else
    {
        cout << "p:red" << endl;
        cout << "c:green" << endl;
    }
}