//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-this-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTThisExpressionNode::ASTThisExpressionNode(std::shared_ptr<ASTThisNode> thisNode) {
    _this = thisNode;
    _children.push_back(_this);
}

std::shared_ptr<ASTThisNode> ASTThisExpressionNode::getThisNode() {
    return _this;
}

Position* ASTThisExpressionNode::getStartPosition() {
    return _this->getStartPosition();
}

Position* ASTThisExpressionNode::getEndPosition() {
    return _this->getEndPosition();
}

ASTNodeType ASTThisExpressionNode::getNodeType() {
    return AST_THIS_EXPRESSION_NODE;
}

std::string ASTThisExpressionNode::toString() {
    return "THIS_EXPRESSION";
}

bool ASTThisExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTThisExpressionNode>(other);
    return this->getThisNode()->isSameAs(otherNode->getThisNode());
}

void ASTThisExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _this->print();
    Logger::log("----------");
}

std::string ASTThisExpressionNode::toSourceCode() {
    return _this->toSourceCode();
}