//
// Created by Johny Georges on 2025-01-15.
//

#include "ast-dref-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTDrefExpressionNode::ASTDrefExpressionNode(ASTDrefNode* drefNode, ASTExpressionNode* astExpressionNode) {
    _drefNode = drefNode;
    _expression = astExpressionNode;
    _children.push_back(_drefNode);
    _children.push_back(_expression);
}

ASTExpressionNode* ASTDrefExpressionNode::getExpressionNode() {
    return _expression;
}

ASTDrefNode* ASTDrefExpressionNode::getDrefNode() {
    return _drefNode;
}

void ASTDrefExpressionNode::markAsReferenced() {
    _isReferenced = true;
    _expression->markAsReferenced();
}

Position* ASTDrefExpressionNode::getStartPosition() {
    return _drefNode->getStartPosition();
}

Position* ASTDrefExpressionNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTDrefExpressionNode::getNodeType() {
    return AST_DREF_EXPRESSION_NODE;
}

std::string ASTDrefExpressionNode::toString() {
    return "DREF_EXPRESSION";
}

bool ASTDrefExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTDrefExpressionNode*)other;
    return this->getExpressionNode()->isSameAs(otherNode->getExpressionNode());
}

void ASTDrefExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _drefNode->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTDrefExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_drefNode)
    ->add(_expression);
    return sourceCodeBuilder.build();
}