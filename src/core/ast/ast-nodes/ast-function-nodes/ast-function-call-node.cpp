//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-function-call-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionCallNode::ASTFunctionCallNode(Lexeme *lexeme) {
    _name = lexeme;
}

Lexeme* ASTFunctionCallNode::getName() {
    return _name;
}

ASTNodeType ASTFunctionCallNode::getNodeType() {
    return AST_FUNCTION_CALL_NODE;
}

std::string ASTFunctionCallNode::toString() {
    return "FUNCTION_CALL";
}

bool ASTFunctionCallNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionCallNode*)other;
    return this->getName()->hasSameSymbolTypeAs(otherNode->getName());
}

void ASTFunctionCallNode::print() {
    Logger::log(this->toString(), "-", _name->toString());
}