//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-variable-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTVariableTypeNode::ASTVariableTypeNode(Lexeme* varTypeQualifier) {
    _varTypeQualifier = varTypeQualifier;
}

Lexeme* ASTVariableTypeNode::getVarType() {
    return _varTypeQualifier;
}

ASTNodeType ASTVariableTypeNode::getNodeType() {
    return AST_VARIABLE_TYPE_NODE;
}

std::string ASTVariableTypeNode::toString() {
    return "VARIABLE_TYPE";
}

bool ASTVariableTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTVariableTypeNode*)other;
    return this->getVarType()->hasSameSymbolTypeAs(otherNode->getVarType());
}

void ASTVariableTypeNode::print() {
    Logger::log(this->toString(), "-", _varTypeQualifier->toString());
}