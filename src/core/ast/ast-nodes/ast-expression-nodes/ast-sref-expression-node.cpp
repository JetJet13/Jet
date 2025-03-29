//
// Created by Johny Georges on 2025-03-29.
//

#include "ast-sref-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTSrefExpressionNode::ASTSrefExpressionNode(ASTSrefNode* srefNode, ASTExpressionNode* astExpressionNode) {
    _srefNode = srefNode;
    _expression = astExpressionNode;
    _children.push_back(_srefNode);
    _children.push_back(_expression);
}

ASTExpressionNode* ASTSrefExpressionNode::getExpressionNode() {
    return _expression;
}

ASTSrefNode* ASTSrefExpressionNode::getSrefNode() {
    return _srefNode;
}

void ASTSrefExpressionNode::markAsReferenced() {
    _isReferenced = true;
    _expression->markAsReferenced();
}

Position* ASTSrefExpressionNode::getStartPosition() {
    return _srefNode->getStartPosition();
}

Position* ASTSrefExpressionNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTSrefExpressionNode::getNodeType() {
    return AST_SREF_EXPRESSION_NODE;
}

std::string ASTSrefExpressionNode::toString() {
    return "SREF_EXPRESSION";
}

bool ASTSrefExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTSrefExpressionNode*)other;
    return this->getExpressionNode()->isSameAs(otherNode->getExpressionNode());
}

void ASTSrefExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _srefNode->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTSrefExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_srefNode)
    ->addWithWhitespace(_expression);
    return sourceCodeBuilder.build();
}