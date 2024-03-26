//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-argument-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionArgumentListStartNode::ASTFunctionArgumentListStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFunctionArgumentListStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTFunctionArgumentListStartNode::getNodeType() {
    return AST_FUNCTION_ARGUMENT_LIST_START_NODE;
}

std::string ASTFunctionArgumentListStartNode::toString() {
    return "FUNCTION_ARGUMENT_LIST_START";
}

bool ASTFunctionArgumentListStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFunctionArgumentListStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFunctionArgumentListStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}