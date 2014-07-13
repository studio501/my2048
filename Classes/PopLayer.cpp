#include "PopLayer.h"


PopLayer::PopLayer(void)
{
}


PopLayer::~PopLayer(void)
{
}

PopLayer *PopLayer::createWithColor(ccColor4B &color)
{
	PopLayer *pRet = new PopLayer();
	if(pRet && pRet->init(color))
	{
		pRet->autorelease();
		return pRet;
	}
	return NULL;
}

bool PopLayer::init(ccColor4B &color)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(color));
		setTouchEnabled(true);
		bRet = true;
	} while (0);

	return bRet;
}
void PopLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-127,true);

}
 bool PopLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
 {
	 return true;
 }
 void PopLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
 {

 }
 void PopLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
 {

 }