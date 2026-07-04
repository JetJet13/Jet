//
// Created by Johny Georges on 2025-01-15.
//

#include "ast-ref-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTRefExpressionNode::ASTRefExpressionNode(std::shared_ptr<ASTRefNode> refNode, std::shared_ptr<ASTExpressionNode> astExpressionNode) {
    _refNode = refNode;
    _expression = astExpressionNode;
    _children.push_back(_refNode);
    _children.push_back(_expression);
}

std::shared_ptr<ASTExpressionNode> ASTRefExpressionNode::getExpressionNode() {
    return _expression;
}

std::shared_ptr<ASTRefNode> ASTRefExpressionNode::getRefNode() {
    return _refNode;
}

std::shared_ptr<TypeSignature> ASTRefExpressionNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<RefTypeSignature> ASTRefExpressionNode::getRefTypeSignature() {
    return std::dynamic_pointer_cast<RefTypeSignature>(_typeSignature);
}

void ASTRefExpressionNode::setTypeSignature(std::shared_ptr<RefTypeSignature> typeSignature) {
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

bool ASTRefExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTRefExpressionNode>(other);
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
    ->add(_expression);
    return sourceCodeBuilder.build();
}