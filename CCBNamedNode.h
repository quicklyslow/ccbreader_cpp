

#ifndef __CCB_NAMED_NODE_H__
#define __CCB_NAMED_NODE_H__

#include "base/CCRef.h"
#include "2d/CCNode.h"
#include "base/CCMap.h"

namespace cocosbuilder {
    
    class CCBNamedNode : public cocos2d::Ref
    {
    public:
        /**
         * @js ctor
         */
        CCBNamedNode();
        /**
         * @js NA
         * @lua NA
         */
        ~CCBNamedNode();
        
        virtual bool init();
        
        cocos2d::Node* getNodeByName(const std::string& name) const;
        
        void addNodeWithName(const std::string& name, cocos2d::Node* node);
        
        const std::string& getNodeNames() const { return _names; }
        
		const cocos2d::Map<std::string, cocos2d::Node*>& getNamedNodes() const { return _namedNodes; }
    private:
        cocos2d::Map<std::string, cocos2d::Node*> _namedNodes;
        std::string _names;
    };
    
}

#endif /* defined(__CCB_NAMED_NODE_H__) */
