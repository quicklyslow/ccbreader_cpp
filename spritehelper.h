//
//  spritehelper.h
//  gtx
//
//  Created by xuruoji on 14-4-12.
//
//

#ifndef __gtx__spritehelper__
#define __gtx__spritehelper__

#include "cocos2d.h"

namespace gtx {
	cocos2d::Sprite * createSpriteFromPath(const std::string& path);
	cocos2d::SpriteFrame* createSpriteFrameFromPath(const std::string& path);
}

#endif /* defined(__gtx__spritehelper__) */
