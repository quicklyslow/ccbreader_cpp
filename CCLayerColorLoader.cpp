#include "CCLayerColorLoader.h"

using namespace cocos2d;

namespace cocosbuilder {

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"

void LayerColorLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
        ((LayerColor *)pNode)->setColor(pColor3B);
    } else {
        LayerLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, ccbReader);
    }
}

void LayerColorLoader::onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float theFloat, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
        ((LayerColor *)pNode)->setOpacity(theFloat*255);
    } else {
        LayerLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, theFloat, ccbReader);
    }
}

void LayerColorLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((LayerColor *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        LayerLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, ccbReader);
    }
}

}