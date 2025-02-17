//
// Created by Johny Georges on 2025-01-15.
//

#include "ast-ref-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTRefExpressionNode::ASTRefExpressionNode(ASTRefNode* refNode, ASTExpressionNode* astExpressionNode) {
    _refNode = refNode;
    _expression = astExpressionNode;
    _children.push_back(_refNode);
    _children.push_back(_expression);
}

ASTExpressionNode* ASTRefExpressionNode::getExpressionNode() {
    return _expression;
}

ASTRefNode* ASTRefExpressionNode::getRefNode() {
    return _refNode;
}

void ASTRefExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _expression->markAsGlobal();
}

PointerTypeSignature* ASTRefExpressionNode::getTypeSignature() {
    return _typeSignature;
}

void ASTRefExpressionNode::setTypeSignature(PointerTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

Position* ASTRefExpressionNode::getStartPosition() {
    return _refNode->getStartPosition();
}

Position* ASTRefExpressionNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTRefExpressionNode::getNodeType() {
    return AST_REF_EXPRESSION_NODE;
}

std::string ASTRefExpressionNode::toString() {
    return "REF_EXPRESSION";
}

bool ASTRefExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTRefExpressionNode*)other;
    return this->getExpressionNode()->isSameAs(otherNode->getExpressionNode());
}

void ASTRefExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _refNode->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTRefExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_refNode)
    ->addWithWhitespace(_expression);
    return sourceCodeBuilder.build();
}