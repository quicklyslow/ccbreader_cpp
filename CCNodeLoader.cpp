#include "cocos2d.h"

#include "CCNodeLoader.h"
#include "CCBSelectorResolver.h"
#include "CCBMemberVariableAssigner.h"
#include "CCBAnimationManager.h"
#include "CCNode+CCBRelativePositioning.h"


using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

namespace gtx {
	cocos2d::SpriteFrame* createSpriteFrameFromPath(const std::string& path);
}

namespace cocosbuilder {

NodeLoader::NodeLoader()
{
}

NodeLoader::~NodeLoader()
{
}

ValueMap& NodeLoader::getCustomProperties()
{
    return _customProperties;
}

Node * NodeLoader::loadNode(Node * pParent, CCBReader * ccbReader)
{
    Node * ccNode = this->createNode(pParent, ccbReader);

    //clear _customProperties, ready for load next node.
    _customProperties.clear();

    return ccNode;
}

void NodeLoader::parseProperties(Node * pNode, Node * pParent, CCBReader * ccbReader)
{
    int numRegularProps = ccbReader->readInt(false);
    int numExturaProps = ccbReader->readInt(false);
    int propertyCount = numRegularProps + numExturaProps;

    for(int i = 0; i < propertyCount; i++) {
        bool isExtraProp = (i >= numRegularProps);
        CCBReader::PropertyType type = (CCBReader::PropertyType)ccbReader->readInt(false);
        std::string propertyName = ccbReader->readCachedString();

        // Check if the property can be set for this platform
		bool setProp = true;

        // Forward properties for sub ccb files
        if (dynamic_cast<CCBFile*>(pNode) != NULL)
        {
            CCBFile *ccbNode = (CCBFile*)pNode;
            if (ccbNode->getCCBFileNode() && isExtraProp)
            {
                pNode = ccbNode->getCCBFileNode();
                
                // Skip properties that doesn't have a value to override
                __Array *extraPropsNames = (__Array*)pNode->getUserObject();
                Ref* pObj = NULL;
                bool bFound = false;
                CCARRAY_FOREACH(extraPropsNames, pObj)
                {
                    __String* pStr = static_cast<__String*>(pObj);
                    if (0 == pStr->compare(propertyName.c_str()))
                    {
                        bFound = true;
                        break;
                    }
                }
                setProp &= bFound;
            }
        }
        else if (isExtraProp && pNode == ccbReader->getAnimationManager()->getRootNode())
        {
            __Array *extraPropsNames = static_cast<__Array*>(pNode->getUserObject());
            if (! extraPropsNames)
            {
                extraPropsNames = Array::create();
                pNode->setUserObject(extraPropsNames);
            }
            
            extraPropsNames->addObject(String::create(propertyName));
        }

        switch(type) 
        {
            case CCBReader::PropertyType::POSITION:
            {
                Vec2 position = this->parsePropTypePosition(pNode, pParent, ccbReader, propertyName.c_str());
                if (setProp) 
                {
                    this->onHandlePropTypePosition(pNode, pParent, propertyName.c_str(), position, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::POINT:
            {
                Vec2 point = this->parsePropTypePoint(pNode, pParent, ccbReader);
                if (setProp) 
                {
                    this->onHandlePropTypePoint(pNode, pParent, propertyName.c_str(), point, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::POINT_LOCK:
            {
                Vec2 pointLock = this->parsePropTypePointLock(pNode, pParent, ccbReader);
                if (setProp) 
                {
                    this->onHandlePropTypePointLock(pNode, pParent, propertyName.c_str(), pointLock, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::SIZE:
            {
                Size size = this->parsePropTypeSize(pNode, pParent, ccbReader);
                if(setProp) {
                    this->onHandlePropTypeSize(pNode, pParent, propertyName.c_str(), size, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::SCALE_LOCK:
            {
                float * scaleLock = this->parsePropTypeScaleLock(pNode, pParent, ccbReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeScaleLock(pNode, pParent, propertyName.c_str(), scaleLock, ccbReader);
                }
                CC_SAFE_DELETE_ARRAY(scaleLock);
                break;
            }
            case CCBReader::PropertyType::FLOAT:
            {
                float f = this->parsePropTypeFloat(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloat(pNode, pParent, propertyName.c_str(), f, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::FLOAT_XY:
            {
                float * xy =  this->parsePropTypeFloatXY(pNode, pParent, ccbReader);
                if(setProp)
                {
                    this->onHandlePropTypeFloatXY(pNode, pParent, propertyName.c_str(), xy, ccbReader);
                }
                CC_SAFE_DELETE_ARRAY(xy);
                break;
            }

            case CCBReader::PropertyType::DEGREES:
            {
                float degrees = this->parsePropTypeDegrees(pNode, pParent, ccbReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeDegrees(pNode, pParent, propertyName.c_str(), degrees, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::FLOAT_SCALE:
            {
                float floatScale = this->parsePropTypeFloatScale(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloatScale(pNode, pParent, propertyName.c_str(), floatScale, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::INTEGER:
            {
                int integer = this->parsePropTypeInteger(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeInteger(pNode, pParent, propertyName.c_str(), integer, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::INTEGER_LABELED:
            {
                int integerLabeled = this->parsePropTypeIntegerLabeled(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeIntegerLabeled(pNode, pParent, propertyName.c_str(), integerLabeled, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::FLOAT_VAR:
            {
                float * floatVar = this->parsePropTypeFloatVar(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFloatVar(pNode, pParent, propertyName.c_str(), floatVar, ccbReader);
                }
                CC_SAFE_DELETE_ARRAY(floatVar);
                break;
            }
            case CCBReader::PropertyType::CHECK:
            {
                bool check = this->parsePropTypeCheck(pNode, pParent, ccbReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeCheck(pNode, pParent, propertyName.c_str(), check, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::SPRITEFRAME:
            {
                SpriteFrame * ccSpriteFrame = this->parsePropTypeSpriteFrame(pNode, pParent, ccbReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeSpriteFrame(pNode, pParent, propertyName.c_str(), ccSpriteFrame, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::ANIMATION:
            {
                Animation * ccAnimation = this->parsePropTypeAnimation(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeAnimation(pNode, pParent, propertyName.c_str(), ccAnimation, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::TEXTURE:
            {
                Texture2D * ccTexture2D = this->parsePropTypeTexture(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeTexture(pNode, pParent, propertyName.c_str(), ccTexture2D, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::BYTE:
            {
                unsigned char byte = this->parsePropTypeByte(pNode, pParent, ccbReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeByte(pNode, pParent, propertyName.c_str(), byte, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::COLOR3:
            {
                Color3B color3B = this->parsePropTypeColor3(pNode, pParent, ccbReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeColor3(pNode, pParent, propertyName.c_str(), color3B, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::COLOR4F_VAR:
            {
                Color4F * color4FVar = this->parsePropTypeColor4FVar(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeColor4FVar(pNode, pParent, propertyName.c_str(), color4FVar, ccbReader);
                }
                CC_SAFE_DELETE_ARRAY(color4FVar);
                break;
            }
            case CCBReader::PropertyType::FLIP:
            {
                bool * flip = this->parsePropTypeFlip(pNode, pParent, ccbReader);
                if(setProp) {
                    this->onHandlePropTypeFlip(pNode, pParent, propertyName.c_str(), flip, ccbReader);
                }
                CC_SAFE_DELETE_ARRAY(flip);
                break;
            }
            case CCBReader::PropertyType::BLEND_MODE:
            {
                BlendFunc blendFunc = this->parsePropTypeBlendFunc(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeBlendFunc(pNode, pParent, propertyName.c_str(), blendFunc, ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::FNT_FILE:
            {
                std::string fntFile = ccbReader->getCCBRootPath() + this->parsePropTypeFntFile(pNode, pParent, ccbReader);
                if(setProp) 
                {
                    this->onHandlePropTypeFntFile(pNode, pParent, propertyName.c_str(), fntFile.c_str(), ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::FONT_TTF:
            {
                std::string fontTTF = this->parsePropTypeFontTTF(pNode, pParent, ccbReader);
                if(setProp) {
                    this->onHandlePropTypeFontTTF(pNode, pParent, propertyName.c_str(), fontTTF.c_str(), ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::STRING:
            {
                std::string string = this->parsePropTypeString(pNode, pParent, ccbReader);
                if(setProp) {
                    this->onHandlePropTypeString(pNode, pParent, propertyName.c_str(), string.c_str(), ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::TEXT:
            {
                std::string text = this->parsePropTypeText(pNode, pParent, ccbReader);
                if(setProp) {
                    this->onHandlePropTypeText(pNode, pParent, propertyName.c_str(), text.c_str(), ccbReader);
                }
                break;
            }
            case CCBReader::PropertyType::BLOCK:
            {
                BlockData * blockData = this->parsePropTypeBlock(pNode, pParent, ccbReader);
                if(setProp) {
                    this->onHandlePropTypeBlock(pNode, pParent, propertyName.c_str(), blockData, ccbReader);
                }
                CC_SAFE_DELETE(blockData);
                break;
            }
            case CCBReader::PropertyType::BLOCK_CONTROL:
            {
                BlockControlData * blockControlData = this->parsePropTypeBlockControl(pNode, pParent, ccbReader);
                if(setProp && blockControlData != NULL) {
                    this->onHandlePropTypeBlockControl(pNode, pParent, propertyName.c_str(), blockControlData, ccbReader);
                }
                CC_SAFE_DELETE(blockControlData);
                break;
            }
            case CCBReader::PropertyType::CCB_FILE:
            {
                Node * ccbFileNode = this->parsePropTypeCCBFile(pNode, pParent, ccbReader);
                if(false) {
                    this->onHandlePropTypeCCBFile(pNode, pParent, propertyName.c_str(), ccbFileNode, ccbReader);
                }
                break;
            }
			case CCBReader::PropertyType::COLOR4:
            {
                Color4B color4B = this->parsePropTypeColor4(pNode, pParent, ccbReader, propertyName.c_str());
                if(setProp) 
                {
                    this->onHandlePropTypeColor4(pNode, pParent, propertyName.c_str(), color4B, ccbReader);
                }
                break;
            }
            default:
                ASSERT_FAIL_UNEXPECTED_PROPERTYTYPE(type);
                break;
        }
    }
}

Vec2 NodeLoader::parsePropTypePosition(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName)
{
    float x = ccbReader->readFloat();
    float y = ccbReader->readFloat();
    
    CCBReader::PositionType type = static_cast<CCBReader::PositionType>(ccbReader->readByte());
	CCBReader::PositionUnit xUnit = static_cast<CCBReader::PositionUnit>(ccbReader->readByte());
	CCBReader::PositionUnit yUnit = static_cast<CCBReader::PositionUnit>(ccbReader->readByte());
    
    Size containerSize = ccbReader->getAnimationManager()->getContainerSize(pParent);
    
    Vec2 pt = getAbsolutePosition(Vec2(x,y), type, xUnit, yUnit, containerSize, pPropertyName);
    
    if (ccbReader->getAnimatedProperties()->find(pPropertyName) != ccbReader->getAnimatedProperties()->end())
    {
        ValueVector vec;
        vec.push_back(Value(x));
        vec.push_back(Value(y));
        vec.push_back(Value((int)type));
		vec.push_back(Value((int)xUnit));
		vec.push_back(Value((int)yUnit));
        
        ccbReader->getAnimationManager()->setBaseValue(Value(vec), pNode, pPropertyName);
    }

    return pt;
}

Vec2 NodeLoader::parsePropTypePoint(Node * pNode, Node * pParent, CCBReader * ccbReader) 
{
    float x = ccbReader->readFloat();
    float y = ccbReader->readFloat();

    return Vec2(x, y);
}

Vec2 NodeLoader::parsePropTypePointLock(Node * pNode, Node * pParent, CCBReader * ccbReader) {
    float x = ccbReader->readFloat();
    float y = ccbReader->readFloat();

    return Vec2(x, y);
}

Size NodeLoader::parsePropTypeSize(Node * pNode, Node * pParent, CCBReader * ccbReader) {
    float width = ccbReader->readFloat();
    float height = ccbReader->readFloat();

	CCBReader::SizeUnit widthUnit = static_cast<CCBReader::SizeUnit>(ccbReader->readByte());
	CCBReader::SizeUnit heightUnit = static_cast<CCBReader::SizeUnit>(ccbReader->readByte());

    Size containerSize = ccbReader->getAnimationManager()->getContainerSize(pParent);

    switch (widthUnit) 
    {
		case CCBReader::SizeUnit::UNIT_POINTS:
        {
            /* Nothing. */
            break;
        }
		case CCBReader::SizeUnit::UNIT_UI_POINTS:
        {
			width *= CCBReader::getResolutionScale();
            break;
        }
        case CCBReader::SizeUnit::UNIT_NORMALIZED:
        {
            width *= containerSize.width;
            break;
        }
		case CCBReader::SizeUnit::UNIT_INSET_POINTS:
        {
            width = containerSize.width - width;
            break;
        }
		case CCBReader::SizeUnit::UNIT_INSET_UI_POINTS:
        {
			width = containerSize.width - width * CCBReader::getResolutionScale();
            break;
        }
        default:
        {
            log("Unknown CCB type of width.");
        }
        break;
    }

	switch (heightUnit) 
    {
		case CCBReader::SizeUnit::UNIT_POINTS:
        {
            /* Nothing. */
            break;
        }
		case CCBReader::SizeUnit::UNIT_UI_POINTS:
        {
			height *= CCBReader::getResolutionScale();
            break;
        }
        case CCBReader::SizeUnit::UNIT_NORMALIZED:
        {
            height *= containerSize.height;
            break;
        }
		case CCBReader::SizeUnit::UNIT_INSET_POINTS:
        {
            height = containerSize.height - height;
            break;
        }
		case CCBReader::SizeUnit::UNIT_INSET_UI_POINTS:
        {
			height = containerSize.width - height * CCBReader::getResolutionScale();
            break;
        }
        default:
        {
            log("Unknown CCB type of height.");
        }
        break;
    }
    
    return Size(width, height);
}



float * NodeLoader::parsePropTypeFloatXY(Node * pNode, Node * pParent, CCBReader * ccbReader) {
    float x = ccbReader->readFloat();
    float y = ccbReader->readFloat();

    float * floatXY = new float[2];
    floatXY[0] = x;
    floatXY[1] = y;

    return floatXY;
}

float * NodeLoader::parsePropTypeScaleLock(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName) {
    float x = ccbReader->readFloat();
    float y = ccbReader->readFloat();
    
    CCBReader::ScaleType type = static_cast<CCBReader::ScaleType>(ccbReader->readByte());
    
    setRelativeScale(pNode, x, y, type, pPropertyName);
    
    if (ccbReader->getAnimatedProperties()->find(pPropertyName) != ccbReader->getAnimatedProperties()->end())
    {
        ValueVector baseValue;
        baseValue.push_back(Value(x));
        baseValue.push_back(Value(y));
        baseValue.push_back(Value((int)type));
        
        ccbReader->getAnimationManager()->setBaseValue(Value(baseValue), pNode, pPropertyName);
    }
    
    if (type == CCBReader::ScaleType::MULTIPLY_RESOLUTION) 
    {
        x *= ccbReader->getResolutionScale();
        y *= ccbReader->getResolutionScale();
    }
    
    float * scaleLock = new float[2];
    scaleLock[0] = x;
    scaleLock[1] = y;

    return scaleLock;
}

float NodeLoader::parsePropTypeFloat(Node * pNode, Node * pParent, CCBReader * ccbReader) {
    return ccbReader->readFloat();
}

float NodeLoader::parsePropTypeDegrees(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName) {
    float ret = ccbReader->readFloat();
    if (ccbReader->getAnimatedProperties()->find(pPropertyName) != ccbReader->getAnimatedProperties()->end())
    {
        ccbReader->getAnimationManager()->setBaseValue(Value(ret), pNode, pPropertyName);
    }
    
    return ret;
}

float NodeLoader::parsePropTypeFloatScale(Node * pNode, Node * pParent, CCBReader * ccbReader) 
{
    float f = ccbReader->readFloat();

    CCBReader::ScaleType type = static_cast<CCBReader::ScaleType>(ccbReader->readInt(false));
    
    if(type == CCBReader::ScaleType::MULTIPLY_RESOLUTION) 
    {
        f *= ccbReader->getResolutionScale();
    }

    return f;
}

int NodeLoader::parsePropTypeInteger(Node * pNode, Node * pParent, CCBReader * ccbReader) 
{
    return ccbReader->readInt(true);
}

int NodeLoader::parsePropTypeIntegerLabeled(Node * pNode, Node * pParent, CCBReader * ccbReader) 
{
    return ccbReader->readInt(true);
}

float * NodeLoader::parsePropTypeFloatVar(Node * pNode, Node * pParent, CCBReader * ccbReader) 
{
    float f = ccbReader->readFloat();
    float fVar = ccbReader->readFloat();
    
    float * arr = new float[2];
    arr[0] = f;
    arr[1] = fVar;
    
    return arr;
}

bool NodeLoader::parsePropTypeCheck(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName) 
{
    bool ret = ccbReader->readBool();
    
    if (ccbReader->getAnimatedProperties()->find(pPropertyName) != ccbReader->getAnimatedProperties()->end())
    {
        ccbReader->getAnimationManager()->setBaseValue(Value(ret), pNode, pPropertyName);
    }
    
    return ret;
}


SpriteFrame * NodeLoader::parsePropTypeSpriteFrame(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName) 
{
    SpriteFrame *spriteFrame = nullptr;
    std::string spriteFile = ccbReader->readCachedString();
    if (spriteFile.length() != 0)
    {
		spriteFile = ccbReader->getCCBRootPath() + spriteFile;
		spriteFrame = gtx::createSpriteFrameFromPath(spriteFile);
    }
    return spriteFrame;
}

Animation * NodeLoader::parsePropTypeAnimation(Node * pNode, Node * pParent, CCBReader * ccbReader) {
    std::string animationFile = ccbReader->getCCBRootPath() + ccbReader->readCachedString();
    std::string animation = ccbReader->readCachedString();
    
    Animation * ccAnimation = NULL;
    
    // Support for stripping relative file paths, since ios doesn't currently
    // know what to do with them, since its pulling from bundle.
    // Eventually this should be handled by a client side asset manager
    // interface which figured out what resources to load.
    // TODO Does this problem exist in C++?
    animation = CCBReader::lastPathComponent(animation.c_str());
    animationFile = CCBReader::lastPathComponent(animationFile.c_str());
    
    if (animation.length() > 0) 
    {
        AnimationCache * animationCache = AnimationCache::getInstance();
        animationCache->addAnimationsWithFile(animationFile.c_str());
        
        ccAnimation = animationCache->getAnimation(animation.c_str());
    }
    return ccAnimation;
}

Texture2D * NodeLoader::parsePropTypeTexture(Node * pNode, Node * pParent, CCBReader * ccbReader) {
    SpriteFrame *spriteFrame = nullptr;
    std::string spriteFile = ccbReader->readCachedString();
    if (spriteFile.length() != 0)
    {
		spriteFrame = gtx::createSpriteFrameFromPath(ccbReader->getCCBRootPath() + spriteFile);
		if(spriteFrame != nullptr)
			return spriteFrame->getTexture();
    }

    return nullptr;
}

unsigned char NodeLoader::parsePropTypeByte(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName) 
{
    unsigned char ret = ccbReader->readByte();
    
    if (ccbReader->getAnimatedProperties()->find(pPropertyName) != ccbReader->getAnimatedProperties()->end())
    {
        ccbReader->getAnimationManager()->setBaseValue(Value(ret), pNode, pPropertyName);
    }
    
    return ret;
}

Color3B NodeLoader::parsePropTypeColor3(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName) {
	unsigned char r = ccbReader->readFloat() * 255;
	unsigned char g = ccbReader->readFloat() * 255;
	unsigned char b = ccbReader->readFloat() * 255;
	unsigned char a = ccbReader->readFloat() * 255;

	Color3B color(r, g, b);

	ValueMap colorMap;
	colorMap["r"] = r;
	colorMap["g"] = g;
	colorMap["b"] = b;

	if (ccbReader->getAnimatedProperties()->find(pPropertyName) != ccbReader->getAnimatedProperties()->end())
	{
		ccbReader->getAnimationManager()->setBaseValue(Value(colorMap), pNode, pPropertyName);
	}
	return color;
}
    
    Color4B NodeLoader::parsePropTypeColor4(Node * pNode, Node * pParent, CCBReader * ccbReader, const char *pPropertyName) {
        unsigned char r = ccbReader->readFloat() * 255;
        unsigned char g = ccbReader->readFloat() * 255;
        unsigned char b = ccbReader->readFloat() * 255;
        unsigned char a = ccbReader->readFloat() * 255;
        
        Color4B color(r, g, b, a);
        
        ValueMap colorMap;
        colorMap["r"] = r;
        colorMap["g"] = g;
        colorMap["b"] = b;
        colorMap["a"] = a;
        
        if (ccbReader->getAnimatedProperties()->find(pPropertyName) != ccbReader->getAnimatedProperties()->end())
        {
            ccbReader->getAnimationManager()->setBaseValue(Value(colorMap), pNode, pPropertyName);
        }
        return color;
    }

Color4F * NodeLoader::parsePropTypeColor4FVar(Node * pNode, Node * pParent, CCBReader * ccbReader) {
    float red = ccbReader->readFloat();
    float green = ccbReader->readFloat();
    float blue = ccbReader->readFloat();
    float alpha = ccbReader->readFloat();
    float redVar = ccbReader->readFloat();
    float greenVar = ccbReader->readFloat();
    float blueVar = ccbReader->readFloat();
    float alphaVar = ccbReader->readFloat();
    
    Color4F * colors = new Color4F[2];
    colors[0].r = red;
    colors[0].g = green;
    colors[0].b = blue;
    colors[0].a = alpha;
    
    colors[1].r = redVar;
    colors[1].g = greenVar;
    colors[1].b = blueVar;
    colors[1].a = alphaVar;
    
    return colors;
}

bool * NodeLoader::parsePropTypeFlip(Node * pNode, Node * pParent, CCBReader * ccbReader) {
    bool flipX = ccbReader->readBool();
    bool flipY = ccbReader->readBool();

    bool * arr = new bool[2];
    arr[0] = flipX;
    arr[1] = flipY;

    return arr;
}

BlendFunc NodeLoader::parsePropTypeBlendFunc(Node * pNode, Node * pParent, CCBReader * ccbReader) 
{
    int source = ccbReader->readInt(false);
    int destination = ccbReader->readInt(false);
    
    BlendFunc blendFunc;
    blendFunc.src = source;
    blendFunc.dst = destination;
    
    return blendFunc;
}

std::string NodeLoader::parsePropTypeFntFile(Node * pNode, Node * pParent, CCBReader * ccbReader) 
{
    return ccbReader->readCachedString();
}

std::string NodeLoader::parsePropTypeString(Node * pNode, Node * pParent, CCBReader * ccbReader) {
	const std::string& txt = ccbReader->readCachedString();
	bool localized = ccbReader->readBool();
	return txt;
}

std::string NodeLoader::parsePropTypeText(Node * pNode, Node * pParent, CCBReader * ccbReader) {
	const std::string& txt = ccbReader->readCachedString();
	bool localized = ccbReader->readBool();
	return txt;
}

std::string NodeLoader::parsePropTypeFontTTF(Node * pNode, Node * pParent, CCBReader * ccbReader) {
    std::string fontTTF = ccbReader->readCachedString();

    // String * ttfEnding = String::create(".ttf");

    // TODO Fix me if it is wrong
    /* If the fontTTF comes with the ".ttf" extension, prepend the absolute path. 
     * System fonts come without the ".ttf" extension and do not need the path prepended. */
    /*
    if(CCBReader::endsWith(CCBReader::toLowerCase(fontTTF), ttfEnding)){
        fontTTF = CCBReader::concat(ccbReader->getCCBRootPath(), fontTTF);
    }
     */

    return fontTTF;
}

BlockData * NodeLoader::parsePropTypeBlock(Node * pNode, Node * pParent, CCBReader * ccbReader)
{
    std::string selectorName = ccbReader->readCachedString();
    CCBReader::TargetType selectorTarget = static_cast<CCBReader::TargetType>(ccbReader->readInt(false));

    if(selectorTarget != CCBReader::TargetType::NONE)
    {
        Ref*  target = NULL;
        if(!ccbReader->isJSControlled())
        {
            if(selectorTarget == CCBReader::TargetType::DOCUMENT_ROOT)
            {
                target = ccbReader->getAnimationManager()->getRootNode();
            }
            else if(selectorTarget == CCBReader::TargetType::OWNER)
            {
                target = ccbReader->getOwner();
            }
            
            if(target != NULL)
            {
                if(selectorName.length() > 0)
                {
                    SEL_MenuHandler selMenuHandler = 0;
                    
                    CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);
                    
                    if(targetAsCCBSelectorResolver != NULL)
                    {
                        selMenuHandler = targetAsCCBSelectorResolver->onResolveCCBCCMenuItemSelector(target, selectorName.c_str());
                    }
                    
                    if(selMenuHandler == 0)
                    {
                        CCBSelectorResolver * ccbSelectorResolver = ccbReader->getCCBSelectorResolver();
                        if(ccbSelectorResolver != NULL)
                        {
                            selMenuHandler = ccbSelectorResolver->onResolveCCBCCMenuItemSelector(target, selectorName.c_str());
                        }
                    }
                    
                    if(selMenuHandler == 0) {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    } else {
                        BlockData * blockData = new BlockData();
                        blockData->mSELMenuHandler = selMenuHandler;
                        
                        blockData->_target = target;
                        
                        return blockData;
                    }
                } else {
                    CCLOG("Unexpected empty selector.");
                }
            } else {
                CCLOG("Unexpected NULL target for selector.");
            }
        }
        else
        {
            if (selectorTarget == CCBReader::TargetType::DOCUMENT_ROOT)
            {
                ccbReader->addDocumentCallbackNode(pNode);
                ccbReader->addDocumentCallbackName(selectorName);
                // Since there isn't a Control::EventType::NONE, add a TOUCH_DOWN type as a placeholder.
                ccbReader->addDocumentCallbackControlEvents(Control::EventType::TOUCH_DOWN);
            }
            else if (selectorTarget == CCBReader::TargetType::OWNER)
            {
                ccbReader->addOwnerCallbackNode(pNode);
                ccbReader->addOwnerCallbackName(selectorName);
                // Since there isn't a Control::EventType::NONE, add a TOUCH_DOWN type as a placeholder.
                ccbReader->addOwnerCallbackControlEvents(Control::EventType::TOUCH_UP_INSIDE);
            }
        }
    }

    return NULL;
}

BlockControlData * NodeLoader::parsePropTypeBlockControl(Node * pNode, Node * pParent, CCBReader * ccbReader)
{
    std::string selectorName = ccbReader->readCachedString();
    CCBReader::TargetType selectorTarget = static_cast<CCBReader::TargetType>(ccbReader->readInt(false));
    int controlEvents = ccbReader->readInt(false);

    if(selectorTarget != CCBReader::TargetType::NONE)
    {
        if(!ccbReader->isJSControlled())
        {
            Ref*  target = NULL;
            if(selectorTarget == CCBReader::TargetType::DOCUMENT_ROOT)
            {
                target = ccbReader->getAnimationManager()->getRootNode();
            }
            else if(selectorTarget == CCBReader::TargetType::OWNER)
            {
                target = ccbReader->getOwner();
            }
            
            if(target != NULL)
            {
                if(selectorName.length() > 0)
                {
                    Control::Handler selControlHandler = 0;
                    
                    CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(target);
                    
                    if(targetAsCCBSelectorResolver != NULL)
                    {
                        selControlHandler = targetAsCCBSelectorResolver->onResolveCCBCCControlSelector(target, selectorName.c_str());
                    }

                    if(selControlHandler == 0)
                    {
                        CCBSelectorResolver * ccbSelectorResolver = ccbReader->getCCBSelectorResolver();
                        if(ccbSelectorResolver != NULL)
                        {
                            selControlHandler = ccbSelectorResolver->onResolveCCBCCControlSelector(target, selectorName.c_str());
                        }
                    }
                    
                    if(selControlHandler == 0)
                    {
                        CCLOG("Skipping selector '%s' since no CCBSelectorResolver is present.", selectorName.c_str());
                    }
                    else
                    {
                        BlockControlData * blockControlData = new BlockControlData();
                        blockControlData->mSELControlHandler = selControlHandler;
                        
                        blockControlData->_target = target;
                        blockControlData->mControlEvents = (Control::EventType)controlEvents;
                        
                        return blockControlData;
                    }
                } else {
                    CCLOG("Unexpected empty selector.");
                }
            } else {
                CCLOG("Unexpected NULL target for selector.");
            }
        }
        else
        {
            if(selectorTarget == CCBReader::TargetType::DOCUMENT_ROOT)
            {
                ccbReader->addDocumentCallbackNode(pNode);
                ccbReader->addDocumentCallbackName(selectorName);
                ccbReader->addDocumentCallbackControlEvents((Control::EventType)controlEvents);
            }
            else
            {
                ccbReader->addOwnerCallbackNode(pNode);
                ccbReader->addOwnerCallbackName(selectorName);
                ccbReader->addOwnerCallbackControlEvents((Control::EventType)controlEvents);
            }
        }
    }

    return NULL;
}

Node * NodeLoader::parsePropTypeCCBFile(Node * pNode, Node * pParent, CCBReader * pCCBReader) {
    std::string ccbFileName = pCCBReader->getCCBRootPath() + "ccb/" + pCCBReader->readCachedString();
    return nullptr;

    /* Change path extension to .ccbi. */
    std::string ccbFileWithoutPathExtension = CCBReader::deletePathExtension(ccbFileName.c_str());
    ccbFileName = ccbFileWithoutPathExtension + ".ccbi";
    
    // Load sub file
    std::string path = FileUtils::getInstance()->fullPathForFilename(ccbFileName.c_str());

    auto dataPtr = std::make_shared<Data>(FileUtils::getInstance()->getDataFromFile(path));
    
    CCBReader * reader = new CCBReader(pCCBReader);
    reader->autorelease();
    reader->getAnimationManager()->setRootContainerSize(pParent->getContentSize());
    
    
    reader->_data = dataPtr;
    reader->_bytes = dataPtr->getBytes();
    reader->_currentByte = 0;
    reader->_currentBit = 0;
    CC_SAFE_RETAIN(pCCBReader->_owner);
    reader->_owner = pCCBReader->_owner;
    
    reader->getAnimationManager()->_owner = reader->_owner;

    // The assignments below are done in the CCBReader constructor.
//     reader->_ownerOutletNames = pCCBReader->_ownerOutletNames;
//     reader->_ownerOutletNodes = pCCBReader->_ownerOutletNodes;
//     reader->_ownerOutletNodes->retain();
//     reader->_ownerCallbackNames = pCCBReader->_ownerCallbackNames;
//     reader->_ownerCallbackNodes = pCCBReader->_ownerCallbackNodes;
//     reader->_ownerCallbackNodes->retain();

    
    Node * ccbFileNode = reader->readFileWithCleanUp(false, pCCBReader->getAnimationManagers());
    
    if (ccbFileNode && reader->getAnimationManager()->getAutoPlaySequenceId() != -1)
    {
        // Auto play animations
        reader->getAnimationManager()->runAnimationsForSequenceIdTweenDuration(reader->getAnimationManager()->getAutoPlaySequenceId(), 0);
    }
    
    if (reader->isJSControlled() && pCCBReader->isJSControlled() && NULL == reader->_owner)
    {
        //set variables and callback to owner
        //set callback
        auto ownerCallbackNames = reader->getOwnerCallbackNames();
        auto& ownerCallbackNodes = reader->getOwnerCallbackNodes();
        if (!ownerCallbackNames.empty() && !ownerCallbackNodes.empty())
        {
            CCASSERT(ownerCallbackNames.size() == ownerCallbackNodes.size(), "");
            ssize_t nCount = ownerCallbackNames.size();
            
            for (ssize_t i = 0 ; i < nCount; i++)
            {
                pCCBReader->addOwnerCallbackName(ownerCallbackNames[i].asString());
                pCCBReader->addOwnerCallbackNode(ownerCallbackNodes.at(i));
            }
        }
        //set variables
        auto ownerOutletNames = reader->getOwnerOutletNames();
        auto ownerOutletNodes = reader->getOwnerOutletNodes();
        if (!ownerOutletNames.empty() && !ownerOutletNodes.empty())
        {
            CCASSERT(ownerOutletNames.size() == ownerOutletNodes.size(), "");
            ssize_t nCount = ownerOutletNames.size();
            
            for (ssize_t i = 0 ; i < nCount; i++)
            {
                pCCBReader->addOwnerOutletName(ownerOutletNames.at(i).asString());
                pCCBReader->addOwnerOutletNode(ownerOutletNodes.at(i));
            }
        }
    }
    return ccbFileNode;
}



void NodeLoader::onHandlePropTypePosition(Node * pNode, Node * pParent, const char* pPropertyName, Vec2 pPosition, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_POSITION) == 0) {
        pNode->setPosition(pPosition);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char* pPropertyName, Vec2 pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ANCHORPOINT) == 0) {
        pNode->setAnchorPoint(pPoint);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypePointLock(Node * pNode, Node * pParent, const char* pPropertyName, Vec2 pPointLock, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char* pPropertyName, Size pSize, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_CONTENTSIZE) == 0) {
        pNode->setContentSize(pSize);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypeFloatXY(Node * pNode, Node * pParent, const char* pPropertyName, float * pFloat, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_SKEW) == 0) {
        pNode->setSkewX(pFloat[0]);
        pNode->setSkewY(pFloat[1]);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}


void NodeLoader::onHandlePropTypeScaleLock(Node * pNode, Node * pParent, const char* pPropertyName, float * pScaleLock, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_SCALE) == 0) {
        pNode->setScaleX(pScaleLock[0]);
        pNode->setScaleY(pScaleLock[1]);
    } else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypeFloat(Node * pNode, Node * pParent, const char* pPropertyName, float pFloat, CCBReader * ccbReader) {
//    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    // It may be a custom property, add it to custom property dictionary.
    _customProperties[pPropertyName] = Value(pFloat);
}


void NodeLoader::onHandlePropTypeDegrees(Node * pNode, Node * pParent, const char* pPropertyName, float pDegrees, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ROTATION) == 0) {
        pNode->setRotation(pDegrees);
    } else if(strcmp(pPropertyName, PROPERTY_ROTATIONX) == 0) {
        pNode->setRotationSkewX(pDegrees);
    } else if(strcmp(pPropertyName, PROPERTY_ROTATIONY) == 0) {
        pNode->setRotationSkewY(pDegrees);
    }
    else {
        ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    }
}

void NodeLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeInteger(Node * pNode, Node * pParent, const char* pPropertyName, int pInteger, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TAG) == 0) {
        pNode->setTag(pInteger);
    } else {
 //       ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
        // It may be a custom property, add it to custom property dictionary.
        _customProperties[pPropertyName] = Value(pInteger);
    }
}

void NodeLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char* pPropertyName, int pIntegerLabeled, CCBReader * ccbReader) {
    //ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
    if (strcmp(pPropertyName, PROPERTY_SCREEN_HALIGN) == 0) {
        pNode->setScreenHorizontalAlign(cocos2d::ScreenHAlignment(pIntegerLabeled));
    } else if (strcmp(pPropertyName, PROPERTY_SCREEN_VALIGN) == 0) {
        pNode->setScreenVerticalAlign(cocos2d::ScreenVAlignment(pIntegerLabeled));
    }
}

void NodeLoader::onHandlePropTypeFloatVar(Node * pNode, Node * pParent, const char* pPropertyName, float * pFloatVar, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char* pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_VISIBLE) == 0) {
        pNode->setVisible(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_IGNOREANCHORPOINTFORPOSITION) == 0) {
        pNode->ignoreAnchorPointForPosition(pCheck);
    } else {
        //ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
        // It may be a custom property, add it to custom property dictionary.
        _customProperties[pPropertyName] = Value(pCheck);
    }
}

void NodeLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char* pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeAnimation(Node * pNode, Node * pParent, const char* pPropertyName, Animation * pAnimation, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeTexture(Node * pNode, Node * pParent, const char* pPropertyName, Texture2D * pTexture2D, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeByte(Node * pNode, Node * pParent, const char* pPropertyName, unsigned char pByte, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char* pPropertyName, Color3B pColor3B, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeColor4FVar(Node * pNode, Node * pParent, const char* pPropertyName, Color4F * pColor4FVar, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeFlip(Node * pNode, Node * pParent, const char* pPropertyName, bool * pFlip, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char* pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeFntFile(Node * pNode, Node * pParent, const char* pPropertyName, const char* pFntFile, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeString(Node * pNode, Node * pParent, const char* pPropertyName, const char * pString, CCBReader * ccbReader) {
    if (strcmp(pPropertyName, PROPERTY_NAME) == 0) {
        if (strlen(pString) > 0) {
            ccbReader->addNamedCallbackNode(pString, pNode);
        }
    } else { // It may be a custom property, add it to custom property dictionary.
        _customProperties[pPropertyName] = Value(pString);
    }
}

void NodeLoader::onHandlePropTypeText(Node * pNode, Node * pParent, const char* pPropertyName, const char * pText, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char* pPropertyName, const char * pFontTTF, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeBlock(Node * pNode, Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char* pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeCCBFile(Node * pNode, Node * pParent, const char* pPropertyName, Node * pCCBFileNode, CCBReader * ccbReader) {
    ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

void NodeLoader::onHandlePropTypeColor4(Node * pNode, Node * pParent, const char* pPropertyName, Color4B pColor4B, CCBReader * ccbReader) {
	ASSERT_FAIL_UNEXPECTED_PROPERTY(pPropertyName);
}

}
