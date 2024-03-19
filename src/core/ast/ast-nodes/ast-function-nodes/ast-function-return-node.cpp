//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-return-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionReturnNode::ASTFunctionReturnNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFunctionReturnNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTFunctionReturnNode::getNodeType() {
    return AST_FUNCTION_RETURN_NODE;
}

std::string ASTFunctionReturnNode::toString() {
    return "FUNCTION_RETURN_NODE";
}

bool ASTFunctionReturnNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFunctionReturnNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFunctionReturnNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}