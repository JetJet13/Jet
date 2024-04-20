//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-this-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTThisTypeNode::ASTThisTypeNode(ASTThisNode* thisNode) {
    _this = thisNode;
}

ASTThisNode* ASTThisTypeNode::getThis() {
    return _this;
}

ASTNodeType ASTThisTypeNode::getNodeType() {
    return AST_THIS_TYPE_NODE;
}

std::string ASTThisTypeNode::toString() {
    return "THIS_TYPE";
}

bool ASTThisTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTThisTypeNode*)other;
    return this->getThis()->isSameAs(otherNode->getThis());
}

void ASTThisTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _this->print();
    Logger::log("----------");
}