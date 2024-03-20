//
// Created by Johny Georges on 2024-03-20.
//

#include "ast-function-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionNameNode::ASTFunctionNameNode(Lexeme *lexeme) {
    _name = lexeme;
}

Lexeme* ASTFunctionNameNode::getName() {
    return _name;
}

ASTNodeType ASTFunctionNameNode::getNodeType() {
    return AST_FUNCTION_NAME_NODE;
}

std::string ASTFunctionNameNode::toString() {
    return "FUNCTION_NAME";
}

bool ASTFunctionNameNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionNameNode*)other;
    return this->getName()->hasSameSymbolTypeAs(otherNode->getName());
}

void ASTFunctionNameNode::print() {
    Logger::log(this->toString(), "-", _name->toString());
}