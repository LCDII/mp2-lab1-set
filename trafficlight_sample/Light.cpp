#include "Light.h"

TL::TL()
{
    n = 0;
    set = new TSet(0);
}
TL::TL(int _n)
{
    n = _n;
    set = new TSet(n);
}
TL::TL(const TL& tl)
{
    set = new TSet(tl.n);
    for (size_t i = 0; i < n; i++)
    {
        set = tl.set;
    }
}
TL::~TL()
{
    delete set;
}

TSet* TL::getSet()
{
    return set;
}
int TL::getAmmLights()
{
    return n;
}

TL& TL::operator= (const TL& tl)
{
    delete set;
    set = new TSet(tl.n);
    for (size_t i = 0; i < n; i++)
    {
        set = tl.set;
    }
    return *this;
}



PTL::PTL() : TL(2)
{
    set->InsElem(0);
}
PTL::PTL(TL& ptl)
{
    set = new TSet(ptl.getAmmLights());
    for (size_t i = 0; i < n; i++)
    {
        set = ptl.getSet();
    }
}

bool PTL::isGreen()
{
    if (set->IsMember(0))
        return true;
    return false;
}
bool PTL::isYellow()
{
    throw -1;
}
bool PTL::isRed()
{
    if (set->IsMember(1))
        return true;
    return false;
}

PTL& PTL::operator= (TL& tl)
{
    delete set;
    set = new TSet(tl.getAmmLights());
    for (size_t i = 0; i < n; i++)
    {
        set = tl.getSet();
    }
    return *this;
}



CTL::CTL() : TL(3)
{
    set = new TSet(3);
    set->InsElem(2);
}
CTL::CTL(TL& ctl)
{
    set = new TSet(ctl.getAmmLights());
    for (size_t i = 0; i < n; i++)
    {
        set = ctl.getSet();
    }
}

CTL& CTL::operator= (TL& tl)
{
    delete set;
    set = new TSet(tl.getAmmLights());
    for (size_t i = 0; i < n; i++)
    {
        set = tl.getSet();
    }
    return *this;
}
bool CTL::isGreen()
{
    if (set->IsMember(0))
        return true;
    return false;
}
bool CTL::isYellow()
{
    if (set->IsMember(1))
        return true;
    return false;
}
bool CTL::isRed()
{
    if (set->IsMember(2))
        return true;
    return false;
}