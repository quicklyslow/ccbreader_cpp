#include "CCControlButtonLoader.h"
#include "2d/CCLabel.h"

using namespace cocos2d;
using namespace cocos2d::extension;

namespace cocosbuilder {;
    
#define PROPERTY_BLOCK "block"
#define PROPERTY_TITLE_NORMAL "title"
#define PROPERTY_ZOOMONTOUCHDOWN "zoomWhenHighlighted"
#define PROPERTY_TOGGLE_SELECTED_STATE "togglesSelectedState"
#define PROPERTY_PREFEREDSIZE "preferredSize"
#define PROPERTY_MAXSIZE "maxSize"

#define PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL "backgroundSpriteFrame|Normal"
#define PROPERTY_BACKGROUND_OPACITY_NORMAL "backgroundOpacity|Normal"
#define PROPERTY_BACKGROUND_COLOR_NORMAL "backgroundColor|Normal"
#define PROPERTY_LABEL_OPACITY_NORMAL "labelOpacity|Normal"
#define PROPERTY_TITLECOLOR_NORMAL "labelColor|Normal"
    
#define PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED "backgroundSpriteFrame|Highlighted"
#define PROPERTY_BACKGROUND_OPACITY_HIGHLIGHTED "backgroundOpacity|Highlighted"
#define PROPERTY_BACKGROUND_COLOR_HIGHLIGHTED "backgroundColor|Highlighted"
#define PROPERTY_LABEL_OPACITY_HIGHLIGHTED "labelOpacity|Highlighted"
#define PROPERTY_TITLECOLOR_HIGHLIGHTED "labelColor|Highlighted"

#define PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED "backgroundSpriteFrame|Disabled"
#define PROPERTY_BACKGROUND_OPACITY_DISABLED "backgroundOpacity|Disabled"
#define PROPERTY_BACKGROUND_COLOR_DISABLED "backgroundColor|Disabled"
#define PROPERTY_LABEL_OPACITY_DISABLED "labelOpacity|Disabled"
#define PROPERTY_TITLECOLOR_DISABLED "labelColor|Disabled"
    
#define PROPERTY_BACKGROUNDSPRITEFRAME_SELECTED "backgroundSpriteFrame|Selected"
#define PROPERTY_BACKGROUND_OPACITY_SELECTED "backgroundOpacity|Selected"
#define PROPERTY_BACKGROUND_COLOR_SELECTED "backgroundColor|Selected"
#define PROPERTY_LABEL_OPACITY_SELECTED "labelOpacity|Selected"
#define PROPERTY_TITLECOLOR_SELECTED "labelColor|Selected"
    
#define PROPERTY_TITLE_HIGHLIGHTED "title|2"
#define PROPERTY_TITLE_DISABLED "title|3"

#define PROPERTY_TITLETTF_NORMAL "fontName"
#define PROPERTY_TITLETTF_HIGHLIGHTED "titleTTF|2"
#define PROPERTY_TITLETTF_DISABLED "titleTTF|3"
#define PROPERTY_TITLETTFSIZE_NORMAL "fontSize"
#define PROPERTY_TITLETTFSIZE_HIGHLIGHTED "titleTTFSize|2"
#define PROPERTY_TITLETTFSIZE_DISABLED "titleTTFSize|3"
#define PROPERTY_HORIZONTAL_PADDING "horizontalPadding"
#define PROPERTY_VERTICAL_PADDING "verticalPadding"
#define PROPERTY_LABELANCHORPOINT "labelAnchorPoint"

#define PROPERTY_COLOR "color"
#define PROPERTY_FONT_COLOR "fontColor"
#define PROPERTY_OUTLINE_COLOR "outlineColor"
#define PROPERTY_OUTLINE_WIDTH "outlineWidth"
#define PROPERTY_SHADOW_COLOR "shadowColor"
#define PROPERTY_SHADOW_BLUR_RADIUS "shadowBlurRadius"
#define PROPERTY_SHADOW_OFFSET "shadowOffset"
    
#define PROPERTY_MARGINLEFT "marginLeft"
#define PROPERTY_MARGINRIGHT "marginRight"
#define PROPERTY_MARGINTOP "marginTop"
#define PROPERTY_MARGINBOTTOM "marginBottom"
    
void ControlButtonLoader::onHandlePropTypeBlock(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * ccbReader) {
        ControlLoader::onHandlePropTypeBlockControl(pNode, pParent, pPropertyName, (BlockControlData*)pBlockData, ccbReader);
    }

void ControlButtonLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ZOOMONTOUCHDOWN) == 0) {
        ((ControlButton *)pNode)->setZoomOnTouchDown(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_TOGGLE_SELECTED_STATE) == 0) {
        ((ControlButton *)pNode)->setSelected(pCheck);
    } else {
        ControlLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeString(Node * pNode, Node * pParent, const char * pPropertyName, const char * pString, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLE_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleForState(pString, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLETTF_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, Control::State::DISABLED);
    } else {
        ControlLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, ccbReader);
    }
}
    
void ControlButtonLoader::onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float theFloat, CCBReader * ccbReader) {
    if (strcmp(pPropertyName, PROPERTY_BACKGROUND_OPACITY_NORMAL)) {
        ((ControlButton *)pNode)->setBackgroundOpacityForState(theFloat, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUND_OPACITY_HIGHLIGHTED)) {
        ((ControlButton *)pNode)->setBackgroundOpacityForState(theFloat, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUND_OPACITY_DISABLED)) {
        ((ControlButton *)pNode)->setBackgroundOpacityForState(theFloat, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUND_OPACITY_SELECTED)) {
        ((ControlButton *)pNode)->setBackgroundOpacityForState(theFloat, Control::State::SELECTED);
    } else if(strcmp(pPropertyName, PROPERTY_LABEL_OPACITY_NORMAL)) {
        ((ControlButton *)pNode)->setTitleOpacityForState(theFloat, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_LABEL_OPACITY_HIGHLIGHTED)) {
        ((ControlButton *)pNode)->setTitleOpacityForState(theFloat, Control::State::HIGH_LIGHTED);

    } else if(strcmp(pPropertyName, PROPERTY_LABEL_OPACITY_DISABLED)) {
        ((ControlButton *)pNode)->setTitleOpacityForState(theFloat, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_LABEL_OPACITY_SELECTED)) {
        ((ControlButton *)pNode)->setTitleOpacityForState(theFloat, Control::State::SELECTED);
    } else {
        NodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, theFloat, ccbReader);
    }
    
}

void ControlButtonLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_HORIZONTAL_PADDING) == 0) {
        
    } else if(strcmp(pPropertyName, PROPERTY_VERTICAL_PADDING) == 0) {
        
    } else if (strcmp(pPropertyName, PROPERTY_OUTLINE_WIDTH) == 0) {
        //((Label*)((ControlButton*)pNode)->getTitleLabelForState(Control::State::NORMAL))->enableOutlineWithSize((int)pFloatScale);
    } else if (strcmp(pPropertyName, PROPERTY_SHADOW_BLUR_RADIUS) == 0) {
        
    } else {
        ControlLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}
    
    void ControlButtonLoader::onHandlePropTypePosition(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Point pPosition, CCBReader * ccbReader)
    {
        if (strcmp(pPropertyName, PROPERTY_SHADOW_OFFSET) == 0)
		{
            
		}
		else
		{
			NodeLoader::onHandlePropTypePosition(pNode, pParent, pPropertyName, pPosition, ccbReader);
		}
    }

void ControlButtonLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Vec2 pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_LABELANCHORPOINT) == 0) {
        ((ControlButton *)pNode)->setLabelAnchorPoint(pPoint);
    } else {
        ControlLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_PREFEREDSIZE) == 0) {
        ((ControlButton *)pNode)->setPreferredSize(pSize);
    } else if (strcmp(pPropertyName, PROPERTY_MAXSIZE) == 0) {
        // do nothing
    } else {
        ControlLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::NORMAL);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::HIGH_LIGHTED);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::DISABLED);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_SELECTED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, Control::State::SELECTED);
        }
    } else {
        ControlLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}

void ControlButtonLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    if (strcmp(pPropertyName, PROPERTY_BACKGROUND_COLOR_NORMAL) == 0) {
        ((ControlButton *)pNode)->setBackgroundColorForState(pColor3B, Control::State::NORMAL);
    } else if (strcmp(pPropertyName, PROPERTY_BACKGROUND_COLOR_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setBackgroundColorForState(pColor3B, Control::State::HIGH_LIGHTED);
    } else if (strcmp(pPropertyName, PROPERTY_BACKGROUND_COLOR_DISABLED) == 0) {
        ((ControlButton *)pNode)->setBackgroundColorForState(pColor3B, Control::State::DISABLED);
    } else if (strcmp(pPropertyName, PROPERTY_BACKGROUND_COLOR_SELECTED) == 0) {
        ((ControlButton *)pNode)->setBackgroundColorForState(pColor3B, Control::State::SELECTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::NORMAL);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::HIGH_LIGHTED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::DISABLED);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_SELECTED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, Control::State::SELECTED);
    } else {
        ControlLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, ccbReader);
    }
}
    void ControlButtonLoader::onHandlePropTypeColor4(cocos2d::Node *pNode, cocos2d::Node *pParent, const char *pPropertyName, cocos2d::Color4B pColor4B, cocosbuilder::CCBReader *ccbReader)
    {
        if (strcmp(pPropertyName, PROPERTY_FONT_COLOR) == 0) {
            ((ControlButton *)pNode)->setShareColor(pColor4B);
        } else if (strcmp(pPropertyName, PROPERTY_SHADOW_COLOR) == 0) {
            //((Label *)pNode)->setShadowColor();
        } else if (strcmp(pPropertyName, PROPERTY_OUTLINE_COLOR) == 0) {
            //setOutlineColor
        } else {
            NodeLoader::onHandlePropTypeColor4(pNode, pParent, pPropertyName, pColor4B, ccbReader);
        }
    }
    
    void ControlButtonLoader::onHandlePropTypeInteger(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, int pInteger, CCBReader * ccbReader)
    {
        if(strcmp(pPropertyName, PROPERTY_MARGINLEFT) == 0) {
            ((ControlButton *)pNode)->setBackgroundInsetLeft(pInteger);
        } else if(strcmp(pPropertyName, PROPERTY_MARGINTOP) == 0) {
            ((ControlButton *)pNode)->setBackgroundInsetTop(pInteger);
        } else if(strcmp(pPropertyName, PROPERTY_MARGINRIGHT) == 0) {
            ((ControlButton *)pNode)->setBackgroundInsetRight(pInteger);
        } else if(strcmp(pPropertyName, PROPERTY_MARGINBOTTOM) == 0) {
            ((ControlButton *)pNode)->setBackgroundInsetBottom(pInteger);
        } else {
            NodeLoader::onHandlePropTypeInteger(pNode, pParent, pPropertyName, pInteger, ccbReader);
        }
    }

};