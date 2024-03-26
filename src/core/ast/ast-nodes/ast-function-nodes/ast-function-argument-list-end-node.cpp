//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-argument-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionArgumentListEndNode::ASTFunctionArgumentListEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFunctionArgumentListEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTFunctionArgumentListEndNode::getNodeType() {
    return AST_FUNCTION_ARGUMENT_LIST_END_NODE;
}

std::string ASTFunctionArgumentListEndNode::toString() {
    return "FUNCTION_ARGUMENT_LIST_END";
}

bool ASTFunctionArgumentListEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFunctionArgumentListEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFunctionArgumentListEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}