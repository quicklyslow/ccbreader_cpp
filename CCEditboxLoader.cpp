//
//  CCEditboxLoader.cpp
//  cocos2d_libs
//
//  Created by xuruoji on 14-4-12.
//
//

#include "CCEditboxLoader.h"

namespace cocosbuilder {
    
    cocos2d::ui::EditBox * EditBoxLoader::createNode(cocos2d::Node * pParent, cocosbuilder::CCBReader * ccbReader)
    {
        cocos2d::ui::EditBox* pNode = cocos2d::ui::EditBox::create(cocos2d::Size::ZERO, nullptr);
        
        //pNode->setAnchorPoint(cocos2d::Point(0.5,0.5));
        
        return pNode;
    }
    
    void EditBoxLoader::onHandlePropTypeBlock(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * ccbReader) {
        NodeLoader::onHandlePropTypeBlockControl(pNode, pParent, pPropertyName, (BlockControlData*)pBlockData, ccbReader);
    }
    
    
    void EditBoxLoader::onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader)
    {
        if (strcmp(pPropertyName, "backgroundSpriteFrame") == 0) {
            //save pos
            const cocos2d::Point pos = pNode->getPosition();
            if (pSpriteFrame != nullptr)
            {
                //((cocos2d::ui::EditBox*)pNode)->setBackgroundSprite(cocos2d::ui::Scale9Sprite::createWithSpriteFrame(pSpriteFrame));
            }
            
            //pNode->setPosition(pos);
        } else {
            NodeLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
        }
    }
    
    void EditBoxLoader::onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader)
    {
        if (strcmp(pPropertyName, "preferredSize") == 0) {
             //((cocos2d::ui::EditBox*)pNode)->setPreferredSize(pSize);
        } else {
            NodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
        }
    }
    
    void EditBoxLoader::onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader)
    {
        if (strcmp(pPropertyName, "padding") == 0) {
            
        } else {
            NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
        }
    }
    
    void EditBoxLoader::onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float theFloat, CCBReader * ccbReader)
    {
        if (strcmp(pPropertyName, "fontSize") == 0) {
            ((cocos2d::ui::EditBox*)pNode)->setFontSize(theFloat);
        } else {
            NodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, theFloat, ccbReader);
        }
    }
    
}

