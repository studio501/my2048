#pragma once
#include "cocos2d.h"
USING_NS_CC;

typedef enum _direction
{
	kUp = 0,
	kDown ,
	kLeft ,
	kRight,

	kNULL,
}Direction;
class SimpleRecognizer
{
	CC_SYNTHESIZE(Direction ,m_result,Result);
public:
	SimpleRecognizer(void);
	~SimpleRecognizer(void);

	static SimpleRecognizer * create();

	void beginPoint(CCPoint point);
	void movePoint(CCPoint point);
	Direction endPoint(CCPoint point);

	void simpleRelease();


public:
	std::vector<CCPoint> m_points;

private:
	int m_reference;
	

};

