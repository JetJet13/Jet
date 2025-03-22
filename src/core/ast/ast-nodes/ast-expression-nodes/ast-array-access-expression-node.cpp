//
// Created by Johny Georges on 2024-03-11.
//

#include "ast-array-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessExpressionNode::ASTArrayAccessExpressionNode(ASTExpressionNode* source, ASTArrayAccessNode* arrayAccess) {
    _source = source;
    _arrayAccess = arrayAccess;
    _children.push_back(_source);
    _children.push_back(_arrayAccess);
}

ASTExpressionNode* ASTArrayAccessExpressionNode::getSource() {
    return _source;
}

ASTArrayAccessNode* ASTArrayAccessExpressionNode::getIndex() {
    return _arrayAccess;
}

void ASTArrayAccessExpressionNode::markAsReferenced() {
    _isReferenced = true;
    _source->markAsReferenced();
    _arrayAccess->getIndex()->markAsReferenced();
}

Position* ASTArrayAccessExpressionNode::getStartPosition() {
    return _source->getStartPosition();
}

Position* ASTArrayAccessExpressionNode::getEndPosition() {
    return _arrayAccess->getEndPosition();
}

ASTNodeType ASTArrayAccessExpressionNode::getNodeType() {
    return AST_ARRAY_ACCESS_EXPRESSION_NODE;
}

std::string ASTArrayAccessExpressionNode::toString() {
    return "ARRAY_ACCESS_EXPRESSION";
}

bool ASTArrayAccessExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTArrayAccessExpressionNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource()) &&
           this->getIndex()->isSameAs(otherNode->getIndex());
}

void ASTArrayAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _arrayAccess->print();
    Logger::log("----------");
}

std::string ASTArrayAccessExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_source)
    ->add(_arrayAccess);
    return sourceCodeBuilder.build();
}