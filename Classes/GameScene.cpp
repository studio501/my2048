#include "GameScene.h"
#include "CardSprite.h"
//CardSprite **m_cardArr = new CardSprite*[MAX_NUM];
#include "PopLayer.h"
using namespace std;
GameScene::GameScene(void)
	:m_score(0)
	,m_scoreTTF(NULL)
	,m_beginPoint(CCPointZero)
	,m_recognizer(NULL)
	,m_layer(NULL)
	,m_isPause(false)
	,m_isOver(false)
{
}


GameScene::~GameScene(void)
{
	m_recognizer->simpleRelease();
}

CCScene *GameScene::scene()
{
	CCScene *t_scene = CCScene::create();

	GameScene *t_layer = GameScene::create();
	t_scene->addChild(t_layer);
	return t_scene;
}

bool GameScene::init()
{
	bool bRret = false;

	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		setTouchEnabled(true);
        
        setKeypadEnabled(true);

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCLayerColor *layerColorBG = CCLayerColor::create(ccc4(180,170,160,255));
		addChild(layerColorBG);

		CCMenuItemFont::setFontName("Consolas");
		CCMenuItemFont::setFontSize(24);
		CCMenuItemFont * menuItemPause = CCMenuItemFont::create("pause",this,menu_selector(GameScene::pauseClick));

		menuItemPause->setPosition(ccp(visibleSize.width-menuItemPause->getContentSize().width/2,visibleSize.height-menuItemPause->getContentSize().height/2-visibleSize.height/10));

		CCMenu *menu = CCMenu::create(menuItemPause,NULL);
		menu->setPosition(CCPointZero);
		addChild(menu);

		//CCLabelTTF *score = CCLabelTTF::create("SCORE","Consolas",24);
		//score->setPosition(ccp(visibleOrigin.x+visibleSize.width/2-100,visibleOrigin.y+visibleSize.height-score->getContentSize().height/2));
		//addChild(score);

		m_scoreTTF = CCLabelTTF::create(CCString::createWithFormat("SCORE %d",m_score)->getCString(),"Consolas",24);
		m_scoreTTF->setPosition(ccp(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height-m_scoreTTF->getContentSize().height/2));
		addChild(m_scoreTTF);

		CCLabelTTF * logo = CCLabelTTF::create(CCString::createWithFormat("TangWen O.O")->getCString(),"Consolas",20);
		logo->setPosition(ccp(visibleOrigin.x+logo->getContentSize().width/2,visibleOrigin.y+visibleSize.height-50));
		addChild(logo);

		//初始化卡片
        CCLog("visible size %f,%f",visibleSize.width,visibleSize.height);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCLog("window size %f,%f",winSize.width,winSize.height);
        
		createCardSprite(winSize);
		createCardNum();
		createCardNum();

		//

		m_recognizer = SimpleRecognizer::create();


		bRret = true;
	} while (0);

	return bRret;
}

void GameScene::createCardSprite(CCSize size)
{
//	CC_UNUSED(size);
	int cardSize = (size.width-80)/4;
    CCLog("cardSize = %d",cardSize);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			CardSprite * card = CardSprite::createCardSprite(0,cardSize,cardSize,cardSize*i+15,cardSize*j+80);//高，宽 分辨率适配
			m_cardArr[i][j] =  card;
			addChild(card);
		}
	}
}
void GameScene::createCardNum()
{
	srand(time(0));
	if(!m_isOver)
	{
		while(1)
		{
			int i = CCRANDOM_0_1()*4;
			int j = CCRANDOM_0_1()*4;

	
			//;

			if(m_cardArr[i][j]->getNumber() == 0)
			{
				//2:4 = 9:1
				m_cardArr[i][j]->setNumber(CCRANDOM_0_1()*10<1?4:2);
				CCLog("[%d][%d]",i,j);
				break;
			}
		}
	}
}


void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator itor = pTouches->begin();
	CCTouch *pTouch = (CCTouch *) (*itor);

	//CCLog("touch: x = %f,y=%f",pTouch->getLocation().x,pTouch->getLocation().y);
	CCPoint point = ccp(pTouch->getLocation().x,pTouch->getLocation().y);
	m_recognizer->beginPoint(point);
	
	//CCLog("%d",m_cardArr[5][5]->getNumber());

}
void GameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator itor = pTouches->begin();
	CCTouch *pTouch = (CCTouch *)(*itor);


	CCPoint point = ccp(pTouch->getLocation().x,pTouch->getLocation().y);
	m_recognizer->movePoint(point);
}
void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator itor = pTouches->begin();
	CCTouch *pTouch = (CCTouch *)(*itor);

	CCPoint point = ccp(pTouch->getLocation().x,pTouch->getLocation().y);
	Direction dtn =  m_recognizer->endPoint(point);

	switch(dtn)
	{
	case kLeft:
		doLeft();
		doCheck();
		//setScore(m_score);
		updateScore();
		break;
	case kRight:
		doRight();
		doCheck();
		//setScore(m_score);
		updateScore();
		break;
	case kUp:
		doUp();
		doCheck();
		//setScore(m_score);
		updateScore();
		break;
	case kDown:
		doDown();
		doCheck();
		//setScore(m_score);
		updateScore();
		break;
	case kNULL:
		CCLog("do nothing!");
		break;
	}
	if(dtn != kNULL && !(m_isOver))
	{
		createCardNum();
	}


}

void GameScene::updateScore()
{
	m_scoreTTF->setString(CCString::createWithFormat("SCORE %d",m_score)->getCString());
}

bool GameScene::doLeft()
{
	bool isMove = false;
	for(int y =0;y<MAX_NUM;y++)
	{
		for(int x =0;x<MAX_NUM;x++)
		{
			for(int x1 = x+1;x1<MAX_NUM;x1++)
			{
				if(m_cardArr[x1][y]->getNumber()>0)
				{
					if(m_cardArr[x][y]->getNumber()<=0)
					{
						m_cardArr[x][y]->setNumber(m_cardArr[x1][y]->getNumber());
						m_cardArr[x1][y]->setNumber(0);
						x--;
						isMove = true;
					}
					else if(m_cardArr[x][y]->getNumber()==m_cardArr[x1][y]->getNumber())
					{
						m_cardArr[x][y]->setNumber(m_cardArr[x][y]->getNumber()*2);
						m_cardArr[x1][y]->setNumber(0);

						m_score+=m_cardArr[x][y]->getNumber();
						isMove = true;
						mergetScaleBig(x,y);
					}
					CCLog("x===== %d",x);
					break;
				}
			}
		}
	}
	return isMove;
}

bool GameScene::doRight()
{
	bool isMove = false;
	for(int y=0;y<MAX_NUM;y++)
	{
		for(int x= MAX_NUM-1;x>-1;x--)
		{
			for(int x1 = x-1;x1>-1;x1--)
			{
				if(m_cardArr[x1][y]->getNumber()>0)
				{
					if(m_cardArr[x][y]->getNumber()==0)
					{
						m_cardArr[x][y]->setNumber(m_cardArr[x1][y]->getNumber());
						m_cardArr[x1][y]->setNumber(0);
						x++;
						isMove = true;
					}
					else if(m_cardArr[x][y]->getNumber()==m_cardArr[x1][y]->getNumber())
					{
						m_cardArr[x][y]->setNumber(m_cardArr[x][y]->getNumber()*2);
						m_cardArr[x1][y]->setNumber(0);

						m_score+=m_cardArr[x][y]->getNumber();
						isMove =true;
						mergetScaleBig(x,y);
					}
					CCLog("right x====%d",x);
					break;
				}
			}
		}
	}

	return isMove;
}
bool GameScene::doUp()
{
	bool isMove = false;
	for(int x = 0;x<MAX_NUM;x++)
	{
		for(int y =MAX_NUM-1;y>-1;y--)
		{
			for(int y1=y-1;y1>-1;y1--)
			{
				if(m_cardArr[x][y1]->getNumber()>0)
				{
					if(m_cardArr[x][y]->getNumber()<=0)
					{
						m_cardArr[x][y]->setNumber(m_cardArr[x][y1]->getNumber());
						m_cardArr[x][y1]->setNumber(0);

						y++;
						isMove = true;
					}
					else if(m_cardArr[x][y]->getNumber()==m_cardArr[x][y1]->getNumber())
					{
						m_cardArr[x][y]->setNumber(m_cardArr[x][y]->getNumber()*2);
						m_cardArr[x][y1]->setNumber(0);
						m_score+=m_cardArr[x][y]->getNumber();
						isMove = true;
						mergetScaleBig(x,y);

					}
					break;
				}
			}
		}
	}
	return isMove;
}
bool GameScene::doDown()
{
	bool isMove = false;
	for(int x=0;x<MAX_NUM;x++)
	{
		for(int y =0;y<MAX_NUM;y++)
		{
			for(int y1=y+1;y1<MAX_NUM;y1++)
			{
				if(m_cardArr[x][y1]->getNumber()>0)
				{
					if(m_cardArr[x][y]->getNumber()<=0)
					{
						m_cardArr[x][y]->setNumber(m_cardArr[x][y1]->getNumber());
						m_cardArr[x][y1]->setNumber(0);

						y--;
						isMove = true;
					}
					else if(m_cardArr[x][y]->getNumber()==m_cardArr[x][y1]->getNumber())
					{
						m_cardArr[x][y]->setNumber(m_cardArr[x][y]->getNumber()*2);
						m_cardArr[x][y1]->setNumber(0);

						m_score+=m_cardArr[x][y]->getNumber();
						isMove = true;
						mergetScaleBig(x,y);
					}
					break;
				}
			}
		}
	}
	return isMove;
}

void GameScene::doCheck()
{
	
	if( isWin())
	{
		CCLog("win");
		return ;
	}
	if( isOver())
	{
		CCLog("lose");
		m_isOver = true;
		return ;
	}
}

bool GameScene::isWin()
{
	bool win = false;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(2048 == m_cardArr[i][j]->getNumber())
			{
				win = true;
				break;

			}
		}
	}
	return win;
}
bool GameScene::isOver()
{
	bool gameover = true;

	for(int y =0;y<MAX_NUM;y++)
	{
		for(int x =0;x<MAX_NUM;x++)
		{
			if(m_cardArr[x][y]->getNumber()==0||
				(x<3&&m_cardArr[x][y]->getNumber()==m_cardArr[x+1][y]->getNumber())||
				(x>0&&m_cardArr[x][y]->getNumber()==m_cardArr[x-1][y]->getNumber())||
				(y<3&&m_cardArr[x][y]->getNumber()==m_cardArr[x][y+1]->getNumber())||
				(y>0&&m_cardArr[x][y]->getNumber()==m_cardArr[x][y-1]->getNumber()))
			{
				gameover = false;
			}
		}
		
	}
	return gameover;
}

void GameScene::pauseClick(CCObject *sender)
{
	CCLog("pause");

	if(NULL == m_layer && m_isPause == false)
	{
		//m_layer = static_cast<CCLayer *> (PopLayer::create(ccColor4B));
		m_layer = PopLayer::create(ccc4(122, 122, 122, 122));
		addChild(m_layer,100,kPause);
		m_isPause = true;
	
	}
	else
	{
		m_layer = NULL;
		removeChildByTag(kPause);
		m_isPause = false;
	}

	
}

void GameScene::showState()
{
	for(int i= MAX_NUM-1;i>-1;i--)
		for(int j= 0;j<MAX_NUM;j++)
		{
			CCLog("m_cardArr[%d][%d]=%d",j,i,m_cardArr[j][i]->getNumber());
		}
}

void GameScene::mergetScaleBig(int col,int row)
{
	if(m_cardArr[col][row]!=NULL)
	{
		CCScaleBy *big = CCScaleBy::create(0.1f,1.2f);
		CCActionInterval *act = CCSequence::create(big,big->reverse(),NULL);
		//CCLog("anc %f,%f",m_cardArr[col][row]->getAnchorPoint().x,m_cardArr[col][row]->getAnchorPoint().y);
		//m_cardArr[col][row]->runAction(act);
		m_cardArr[col][row]->getColorBg()->runAction(act);
	}
}

void GameScene::keyBackClicked()
{
    CCDirector::sharedDirector()->end();
}