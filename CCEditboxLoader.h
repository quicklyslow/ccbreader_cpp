//
//  CCEditboxLoader.h
//  cocos2d_libs
//
//  Created by xuruoji on 14-4-12.
//
//


#ifndef __cocos2d_libs__CCEditboxLoader__
#define __cocos2d_libs__CCEditboxLoader__

#include "CCControlLoader.h"
#include "extensions/GUI/CCEditBox/CCEditBox.h"

namespace cocosbuilder {
    /* Forward declaration. */
    class CCBReader;
    
    class EditBoxLoader : public ControlLoader {
    public:
        virtual ~EditBoxLoader() {};
        
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EditBoxLoader, loader);
    protected:
        
        virtual cocos2d::extension::EditBox * createNode(cocos2d::Node * pParent, cocosbuilder::CCBReader * ccbReader);
        
        virtual void onHandlePropTypeBlock(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * ccbReader);
        
        virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
        
        virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
        
        virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * ccbReader);
        
        virtual void onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float theFloat, CCBReader * ccbReader);
    };
}

#endif /* defined(__cocos2d_libs__CCEditboxLoader__) */
