//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-parameter-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionParameterListStartNode::ASTFunctionParameterListStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFunctionParameterListStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTFunctionParameterListStartNode::getNodeType() {
    return AST_FUNCTION_PARAMETER_LIST_START_NODE;
}

std::string ASTFunctionParameterListStartNode::toString() {
    return "FUNCTION_PARAMETER_LIST_START";
}

bool ASTFunctionParameterListStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFunctionParameterListStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFunctionParameterListStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}