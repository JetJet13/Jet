//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-this-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTThisExpressionNode::ASTThisExpressionNode(ASTThisNode* thisNode) {
    _this = thisNode;
    _children.push_back(_this);
}

ASTThisNode* ASTThisExpressionNode::getThisNode() {
    return _this;
}

ASTNodeType ASTThisExpressionNode::getNodeType() {
    return AST_THIS_EXPRESSION_NODE;
}

std::string ASTThisExpressionNode::toString() {
    return "THIS_EXPRESSION";
}

bool ASTThisExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTThisExpressionNode*)other;
    return this->getThisNode()->isSameAs(otherNode->getThisNode());
}

void ASTThisExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _this->print();
    Logger::log("----------");
}