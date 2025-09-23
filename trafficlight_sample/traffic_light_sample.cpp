#include <iostream>
using namespace std;
#include<stdint.h>


#include "tset.h"
class TL
{
protected:
    TL()
    {

    }
	TSet* set;
public:
    TSet* getSet()
    {
        return set;
    }
	virtual  bool isGreen() = 0;
	virtual  bool isYellow() = 0;
	virtual  bool isRed() = 0;
};


class PTL : public TL
{
public:
    PTL()
    {
        set = new TSet(2);
        set->InsElem(0);
    }
	PTL(TL& tl)
    {
        set = tl.getSet();
    }
	virtual  bool isGreen()
    {
        if (set->IsMember(0))
            return true;
        return false;
    }
	virtual  bool isYellow()
    {
        throw -1;
    }
	virtual  bool isRed()
    {
        if (set->IsMember(1))
            return true;
        return false;
    }
};


class CTL : public  TL
{
public:
	CTL()
    {
        set = new TSet(3);
        set->InsElem(2);
    }
    CTL(TL& tl)
    {
        set = tl.getSet();
    }
	virtual  bool isGreen()
    {
        if (set->IsMember(0))
            return true;
        return false;
    }
	virtual  bool isYellow()
    {
        if (set->IsMember(1))
            return true;
        return false;
    }
	virtual  bool isRed()
    {
        if (set->IsMember(2))
            return true;
        return false;
    }
};

class Road
{
	PTL* ptl;
	CTL* ctl;
public:
	Road()
    {
        ptl = new PTL();
        ctl = new CTL();
    }
	Road(const Road& road)
    {
        ptl = new PTL(*road.ptl);
        ctl = new CTL(*road.ctl);
    }
	Road & operator=(const Road & road)
    {
        if (this == &road) return *this;

        delete ptl;
        delete ctl;

        ptl = new PTL(*road.ptl);
        ctl = new CTL(*road.ctl);
    }
	~Road()
    {
        delete ptl;
        delete ctl;
    }

	void switchLights()
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
	void printColor()
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
};




int main()
{
	Road* road = new Road();
	road->printColor();
	road->switchLights();
	road->printColor();
	road->switchLights();
	road->printColor();
	road->switchLights();
}