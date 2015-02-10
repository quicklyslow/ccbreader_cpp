//
//  spritehelper.cpp
//  gtx
//
//  Created by xuruoji on 14-4-12.
//
//

#include "spritehelper.h"

namespace gtx
{
	static cocos2d::SpriteFrame* getSpriteFrameByName(const std::string& path)
	{
		cocos2d::SpriteFrameCache* frameCache = cocos2d::SpriteFrameCache::getInstance();
		cocos2d::SpriteFrame* spFrame = frameCache->getSpriteFrameByName(path);
		if(spFrame == nullptr)
		{
			int slashpos = path.rfind('/');
			std::string filename = path.substr(slashpos + 1, path.length());

			spFrame = frameCache->getSpriteFrameByName(filename);
			if(spFrame == nullptr)
				frameCache->addSpriteFramesWithXML((path.substr(0, slashpos) + ".plist"));

			spFrame = frameCache->getSpriteFrameByName(path);
			if(spFrame == nullptr)
				spFrame = frameCache->getSpriteFrameByName(filename);
		}

		return spFrame;
	}

    //effect/pic/ef01/ef01_1.png
    cocos2d::Sprite* createSpriteFromPath(const std::string& path)
    {
		cocos2d::SpriteFrame* spFrame = getSpriteFrameByName(path);
		if(spFrame != nullptr)
			return cocos2d::Sprite::createWithSpriteFrame(spFrame);
		return cocos2d::Sprite::create(path);
    }
    
    cocos2d::SpriteFrame* createSpriteFrameFromPath(const std::string& path)
    {
		cocos2d::SpriteFrame* spFrame = getSpriteFrameByName(path);
		if(spFrame == nullptr)
		{
			cocos2d::Texture2D *texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(path);
			if (texture != nullptr)
			{
				cocos2d::Rect rect = cocos2d::Rect::ZERO;
				rect.size = texture->getContentSize();
				spFrame = cocos2d::SpriteFrame::createWithTexture(texture, rect);
				cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(spFrame, path);
			}
		}

		return spFrame;
    }
}