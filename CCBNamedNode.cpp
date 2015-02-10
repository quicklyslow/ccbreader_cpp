#include "CCBNamedNode.h"


namespace cocosbuilder {
    
    CCBNamedNode::CCBNamedNode()
    {
        init();
    }
    
    bool CCBNamedNode::init()
    {
        return true;
    }
    
    CCBNamedNode::~CCBNamedNode()
    {
    }
    
    cocos2d::Node* CCBNamedNode::getNodeByName(const std::string& name) const
    {
        cocos2d::Map<std::string, cocos2d::Node*>::const_iterator it = _namedNodes.find(name);
        if (it != _namedNodes.end()) {
            return it->second;
        }
        return nullptr;
    }
    
    void CCBNamedNode::addNodeWithName(const std::string &name, cocos2d::Node *node)
    {
        CCASSERT( node != nullptr, "NameNode addNodeWithName, node must be non-nil");
        CCASSERT(_namedNodes.at(name) == nullptr, "node already in namedNodes. It can't be added again");
        _namedNodes.insert(name, node);
        if (_names.length() > 0) {
            _names.append(",");
        }
        _names.append(name);
    }
}