//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-this-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTThisTypeNode::ASTThisTypeNode(std::shared_ptr<ASTThisNode> thisNode) {
    _this = thisNode;
    _children.push_back(_this);
}

std::shared_ptr<ASTThisNode> ASTThisTypeNode::getThis() {
    return _this;
}

std::shared_ptr<Position> ASTThisTypeNode::getStartPosition() {
    return _this->getStartPosition();
}

std::shared_ptr<Position> ASTThisTypeNode::getEndPosition() {
    return _this->getEndPosition();
}

ASTNodeType ASTThisTypeNode::getNodeType() {
    return AST_THIS_TYPE_NODE;
}

std::string ASTThisTypeNode::toString() {
    return "THIS_TYPE";
}

bool ASTThisTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTThisTypeNode>(other);
    return this->getThis()->isSameAs(otherNode->getThis());
}

void ASTThisTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _this->print();
    Logger::log("----------");
}

std::string ASTThisTypeNode::toSourceCode() {
    return _this->toSourceCode();
}