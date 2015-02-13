#include "CCLabelTTFLoader.h"

using namespace cocos2d;

#define PROPERTY_COLOR "color"
#define PROPERTY_FONT_COLOR "fontColor"
#define PROPERTY_OUTLINE_COLOR "outlineColor"
#define PROPERTY_OUTLINE_WIDTH "outlineWidth"
#define PROPERTY_SHADOW_COLOR "shadowColor"
#define PROPERTY_SHADOW_BLUR_RADIUS "shadowBlurRadius"
#define PROPERTY_SHADOW_OFFSET "shadowOffset"
#define PROPERTY_SHADOW_OFFSET_TYPE "shadowOffsetType"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_FONTNAME "fontName"
#define PROPERTY_FONTSIZE "fontSize"
#define PROPERTY_HORIZONTALALIGNMENT "horizontalAlignment"
#define PROPERTY_VERTICALALIGNMENT "verticalAlignment"
#define PROPERTY_STRING "string"
#define PROPERTY_DIMENSIONS "dimensions"

namespace cocosbuilder {

	void LabelTTFLoader::onHandlePropTypePosition(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Point pPosition, CCBReader * ccbReader)
	{
		if (strcmp(pPropertyName, PROPERTY_SHADOW_OFFSET) == 0)
		{
            //((Label *)pNode)->enableShadowOffset(Size(pPosition.x, pPosition.y));
		}
		else
		{
			NodeLoader::onHandlePropTypePosition(pNode, pParent, pPropertyName, pPosition, ccbReader);
		}
	}

void LabelTTFLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((Label *)pNode)->setColor(pColor3B);
    } else {
        NodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeColor4(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Color4B pColor4B, CCBReader * ccbReader)
{
	if (strcmp(pPropertyName, PROPERTY_FONT_COLOR) == 0) {
		((Label *)pNode)->setTextColor(pColor4B);
	} else if (strcmp(pPropertyName, PROPERTY_SHADOW_COLOR) == 0) {
		((Label *)pNode)->enableShadow(pColor4B);
	} else if (strcmp(pPropertyName, PROPERTY_OUTLINE_COLOR) == 0) {
		((Label *)pNode)->enableOutline(pColor4B);
	} else {
		NodeLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4B, ccbReader);
	}
}

void LabelTTFLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((Label *)pNode)->setOpacity(pByte);
    } else {
        NodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((Label *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTNAME) == 0) {
        ((Label *)pNode)->setSystemFontName(pFontTTF);
    } else {
        NodeLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeText(Node * pNode, Node * pParent, const char * pPropertyName, const char * pText, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_STRING) == 0) {
        ((Label *)pNode)->setString(pText);
    } else {
        NodeLoader::onHandlePropTypeText(pNode, pParent, pPropertyName, pText, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_FONTSIZE) == 0) {
        ((Label *)pNode)->setSystemFontSize(pFloatScale);
	} else if (strcmp(pPropertyName, PROPERTY_OUTLINE_WIDTH) == 0) {
        //((Label *)pNode)->enableOutlineWithSize(pFloatScale);
	} else if (strcmp(pPropertyName, PROPERTY_SHADOW_BLUR_RADIUS) == 0) {
        //((Label *)pNode)->enableShadowBlurRadius(pFloatScale);
	} else {
        NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_HORIZONTALALIGNMENT) == 0) {
        ((Label *)pNode)->setHorizontalAlignment(TextHAlignment(pIntegerLabeled));
    } else if(strcmp(pPropertyName, PROPERTY_VERTICALALIGNMENT) == 0) {
        ((Label *)pNode)->setVerticalAlignment(TextVAlignment(pIntegerLabeled));
    } else {
        NodeLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, ccbReader);
    }
}

void LabelTTFLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size size, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_DIMENSIONS) == 0) {
        ((Label *)pNode)->setDimensions(size.width,size.height);
    } else {
        NodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, size, ccbReader);
    }
}

}