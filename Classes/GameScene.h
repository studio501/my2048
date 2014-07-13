#pragma once
#include "cocos2d.h"
#include "CardSprite.h"
#include "SimpleRecognizer.h"
using namespace cocos2d;
#define MAX_NUM 4
#define CARDWIDTH 80
#define CARDGAP 36
typedef enum _currentLayer
{
	kNone = 0,
	kPause,
	kGameOver,
	kGameWin,
}CurrentLayer;//��ǰ�ĸ���gamelayer �ϵĲ�
class GameScene :
	public CCLayer
{
	CC_SYNTHESIZE(int,m_score,Score);//fenshu
public:
	GameScene(void);
	~GameScene(void);

	static CCScene * scene();
	CREATE_FUNC(GameScene);

	virtual bool init();
public:
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

public:

    void keyBackClicked();
	void pauseClick(CCObject *sender);
	void createCardSprite(CCSize size);// card sprite 
	void createCardNum();//care num

	//���ƴ���
	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();
	//check state
	bool isWin();
	bool isOver();
	void doCheck();

	
	void showState();//��ʾ����
	void mergetScaleBig(int col,int row);//�ϲ����ַŴ󶯻�
	void updateScore();//������



public:
	CCLabelTTF *m_scoreTTF;
	CardSprite *m_cardArr[MAX_NUM][MAX_NUM];

private:
	CCPoint m_beginPoint;

	SimpleRecognizer *m_recognizer;
	bool m_isPause;
	CCLayer *m_layer;
	bool m_isOver;

	
	
};

