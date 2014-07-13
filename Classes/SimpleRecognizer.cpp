#include "SimpleRecognizer.h"


SimpleRecognizer::SimpleRecognizer(void)
	:m_reference(0)
{
	m_reference++;
}


SimpleRecognizer::~SimpleRecognizer(void)
{
}


SimpleRecognizer *SimpleRecognizer::create()
{
	SimpleRecognizer *pRet = new SimpleRecognizer();
	if(pRet)
		return pRet;
}

void SimpleRecognizer::beginPoint(CCPoint point)
{
	m_result = kNULL;
	m_points.clear();
	m_points.push_back(point);
}

void SimpleRecognizer::movePoint(CCPoint point)
{
	m_points.push_back(point);
}

Direction SimpleRecognizer::endPoint(CCPoint point)
{
	m_points.push_back(point);

	if(m_points.size()<3)
		return kNULL;

	Direction tempDir = kNULL;

	int len = m_points.size();

	//每当触点移动时,在当前触点和之前触点之间计算不同的x坐标和y坐标
	double dx = m_points[len-1].x-m_points[0].x;
	double dy = m_points[len-1].y-m_points[0].y;

	if(abs(dx)>abs(dy))
	{
		        //在这种情况下,运动趋势的触点在x轴方向
		if(dx>50)
		{
			tempDir = kRight;
		}
		else if(dx<-50)
		{
			tempDir = kLeft;
		}
	}
	else
	{
		if(dy>50)
		{
			tempDir = kUp;

		}
		else if(dy<-50)
		{
			tempDir = kDown;
		}
	}

	if(m_result == kNULL)
		m_result = tempDir;

	if(m_result != tempDir)
		m_result = kNULL;


	return m_result;


}

void SimpleRecognizer::simpleRelease()
{
	if(m_reference == 0)
		delete this;
	else if(m_reference>0)
		m_reference--;
	else
	{
		CCAssert(m_reference<0,"m_reference should > 0");
	}

}