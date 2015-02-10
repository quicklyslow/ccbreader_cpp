#include "CCNode+CCBRelativePositioning.h"
#include "CCBReader.h"

using namespace cocos2d;

namespace cocosbuilder {

Vec2 getAbsolutePosition(const Vec2 &pt, CCBReader::PositionType type, CCBReader::PositionUnit xUnit, CCBReader::PositionUnit yUnit, const Size &containerSize, const std::string& propName)
{
    Vec2 absPt = Vec2(0,0);

	if (xUnit == CCBReader::PositionUnit::UNIT_POINTS)
	{
		absPt.x = pt.x;
	}
	else if (xUnit == CCBReader::PositionUnit::UNIT_UI_POINTS)
	{
		absPt.x = pt.x * CCBReader::getResolutionScale();
	}
	else if (xUnit == CCBReader::PositionUnit::UNIT_NORMALIZED)
	{
		absPt.x = pt.x * containerSize.width;
	}
	

	if (yUnit == CCBReader::PositionUnit::UNIT_POINTS)
	{
		absPt.y = pt.y;
	}
	else if (yUnit == CCBReader::PositionUnit::UNIT_UI_POINTS)
	{
		absPt.y = pt.y * CCBReader::getResolutionScale();
	}
	else if (yUnit == CCBReader::PositionUnit::UNIT_NORMALIZED)
	{
		absPt.y = pt.y * containerSize.height;
	}


    if (type == CCBReader::PositionType::RELATIVE_BOTTOM_LEFT)
    {
        // nothing need to be done
    }
    else if (type == CCBReader::PositionType::RELATIVE_TOP_LEFT)
    {
        absPt.y = containerSize.height - absPt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_TOP_RIGHT)
    {
        absPt.x = containerSize.width - absPt.x;
        absPt.y = containerSize.height - absPt.y;
    }
    else if (type == CCBReader::PositionType::RELATIVE_BOTTOM_RIGHT)
    {
        absPt.x = containerSize.width - absPt.x;
    }
    return absPt;
}

void setRelativeScale(Node *pNode, float scaleX, float scaleY, CCBReader::ScaleType type, const std::string& propName)
{
    CCASSERT(pNode, "pNode should not be null");
    
    if (type == CCBReader::ScaleType::MULTIPLY_RESOLUTION)
    {
        float resolutionScale = CCBReader::getResolutionScale();
        
        scaleX *= resolutionScale;
        scaleY *= resolutionScale;
    }
    
    pNode->setScaleX(scaleX);
    pNode->setScaleY(scaleY);
}

}
