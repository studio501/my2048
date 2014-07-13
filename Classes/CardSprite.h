#pragma once
#include "cocos2d.h"
USING_NS_CC;


#define LabelTag 8
class CardSprite :
	public CCNode
{
	CC_SYNTHESIZE(CCNode *,m_coloerBg,ColorBg);
	CC_SYNTHESIZE(CCLabelTTF *,m_cardNumTTF,CardNumTTF);
	//CC_SYNTHESIZE(int ,m_cardNum,CardNum);

public:
	CardSprite(void);
	~CardSprite(void);
	static CardSprite * createCardSprite(int number,int wight,int height,float cardx,float cardy);
	bool iniCard(int number,int wight,int height,float cardx,float cardy); 

	int getNumber();
	void setNumber(int var);

private:
	int m_cardNum;
	int m_col;
	int m_row;
};

