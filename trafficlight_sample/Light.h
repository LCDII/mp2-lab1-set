

#include "tset.h"

class TL
{
protected:
	TL();
    TL(int _n);
	TL(const TL& tl);
	~TL();
	int n;
	TSet* set;
public:
	int getAmmLights();
    TSet* getSet();
	virtual  bool isGreen() = 0;
	virtual  bool isYellow() = 0;
	virtual  bool isRed() = 0;

	TL& operator= (const TL& tl);
};

class PTL : public TL
{
public:
    PTL();
	PTL(TL& ptl);
	PTL& operator= (TL& tl);
	virtual  bool isGreen();
	virtual  bool isYellow();
	virtual  bool isRed();
};


class CTL : public  TL
{
public:
	CTL();
	CTL::CTL(TL& ptl);
	CTL& operator= (TL& tl);
	virtual  bool isGreen();
	virtual  bool isYellow();
	virtual  bool isRed();
};