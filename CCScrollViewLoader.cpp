#include "CCScrollViewLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_CONTAINER "contentNode"
#define PROPERTY_DIRECTION "direction"
#define PROPERTY_CLIPSTOBOUNDS "clipsToBounds"
#define PROPERTY_BOUNCES "bounces"
#define PROPERTY_SCALE "scale"

namespace cocosbuilder {

void ScrollViewLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * ccbReader) {
	if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
		((ScrollView *)pNode)->setViewSize(pSize);
	} else {
		NodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
	}
}

void ScrollViewLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_CLIPSTOBOUNDS) == 0) {
        ((ScrollView *)pNode)->setClippingToBounds(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_BOUNCES) == 0) {
        ((ScrollView *)pNode)->setBounceable(pCheck);
    } else if(strcmp(pPropertyName, "horizontalScrollEnabled") == 0) {
        if (pCheck) {
            ((ScrollView*)pNode)->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
        } else {
            ((ScrollView*)pNode)->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
        }
    } else if(strcmp(pPropertyName, "verticalScrollEnabled") == 0) {
        if (pCheck) {
            if (((ScrollView*)pNode)->getDirection() == cocos2d::extension::ScrollView::Direction::HORIZONTAL){
                ((ScrollView*)pNode)->setDirection(cocos2d::extension::ScrollView::Direction::BOTH);
            }
        }
    } else if(strcmp(pPropertyName, "pagingEnabled") == 0) {
        //do nothing
    } else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

void ScrollViewLoader::onHandlePropTypeCCBFile(Node * pNode, Node * pParent, const char * pPropertyName, Node * pCCBFileNode, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTAINER) == 0) {
        //((ScrollView *)pNode)->setContainer(pCCBFileNode);
		//((ScrollView *)pNode)->updateInset();
    } else {
        NodeLoader::onHandlePropTypeCCBFile(pNode, pParent, pPropertyName, pCCBFileNode, ccbReader);
    }
}

void ScrollViewLoader::onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float pFloat, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_SCALE) == 0) {
        ((ScrollView *)pNode)->setScale(pFloat);
    } else {
        NodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, ccbReader);
    }
}

void ScrollViewLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_DIRECTION) == 0) {
        ((ScrollView *)pNode)->setDirection(ScrollView::Direction(pIntegerLabeled));
    } else {
        NodeLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, ccbReader);
    }
}

}