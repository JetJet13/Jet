//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-parameter-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionParameterListEndNode::ASTFunctionParameterListEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFunctionParameterListEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTFunctionParameterListEndNode::getNodeType() {
    return AST_FUNCTION_PARAMETER_LIST_END_NODE;
}

std::string ASTFunctionParameterListEndNode::toString() {
    return "FUNCTION_PARAMETER_LIST_END";
}

bool ASTFunctionParameterListEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFunctionParameterListEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFunctionParameterListEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}