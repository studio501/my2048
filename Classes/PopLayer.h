#pragma once
#include "cocos2d.h"
USING_NS_CC;

class PopLayer :
	public CCLayerColor
{
public:
	PopLayer(void);
	~PopLayer(void);

	static PopLayer *createWithColor(ccColor4B &color);
	bool init(ccColor4B &color);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);



};

