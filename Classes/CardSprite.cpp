#include "CardSprite.h"


CardSprite::CardSprite(void)
	:m_cardNum(0)
	,m_coloerBg(NULL)
	,m_cardNumTTF(NULL)
{
}


CardSprite::~CardSprite(void)
{
}

CardSprite *CardSprite::createCardSprite(int number,int wight,int height,float cardx,float cardy)
{
	CardSprite * pRet = new CardSprite();
	if(pRet && pRet->iniCard(number,wight,height,cardx,cardy))
	{
		pRet->autorelease();
		return pRet;
	}
	else return NULL;

}

bool CardSprite::iniCard(int number,int wight,int height,float cardx,float cardy)
{

	m_cardNum = number;

    setPosition(ccp(cardx,cardy ));
	m_coloerBg = static_cast<CCNode *> (CCLayerColor::create(ccc4(200,190,180,255),wight-15,height-15));
	m_coloerBg->setPosition(ccp(wight/2,wight/2));

	if(m_cardNum>0)
	{
		m_cardNumTTF = CCLabelTTF::create(CCString::createWithFormat("%d",m_cardNum)->getCString(),"Consolas",100);

	}
	else
	{
		m_cardNumTTF = CCLabelTTF::create(CCString::createWithFormat("")->getCString(),"Consolas",100);

	}
	m_cardNumTTF->setPosition(ccp(m_coloerBg->getContentSize().width/2,m_coloerBg->getContentSize().height/2));
	m_cardNumTTF->setTag(LabelTag);
	m_coloerBg->addChild(m_cardNumTTF);
	addChild(m_coloerBg);

	
	return true;

}


int CardSprite::getNumber()
{

	return m_cardNum;
}

void CardSprite::setNumber(int var)
{

	m_cardNum = var;
	if(m_cardNum>0)
	{
		m_cardNumTTF->setString(CCString::createWithFormat("%d",m_cardNum)->getCString());

	}
	else
	{
		m_cardNumTTF->setString("");
	}

	if(m_cardNum>=0 && m_cardNum<128)
	{
		m_cardNumTTF->setFontSize(40);
	}
	else if(m_cardNum>=128 && m_cardNum<1024)
	{
		m_cardNumTTF->setFontSize(30);
	}
	else
	{
		m_cardNumTTF->setFontSize(20);
	}
	//根据数字大小 来设置颜色

	//......

	//////////////////////////////////////////////////////////////////////////
	//
	//to do
	//
	//
	//////////////////////////////////////////////////////////////////////////
	if(m_cardNum>=0 && m_cardNum<128)
	{
		m_cardNumTTF->setColor(ccc3(255,255,255));
	}
	else if(m_cardNum>=128 && m_cardNum<1024)
	{
		m_cardNumTTF->setColor(ccc3(153,137,182));
	}
	else 
	{
		m_cardNumTTF->setColor(ccc3(255,140,26));
	}

	//.....
}