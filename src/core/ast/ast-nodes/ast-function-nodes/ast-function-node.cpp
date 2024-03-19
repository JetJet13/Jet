//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionNode::ASTFunctionNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFunctionNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTFunctionNode::getNodeType() {
    return AST_FUNCTION_NODE;
}

std::string ASTFunctionNode::toString() {
    return "FUNCTION";
}

bool ASTFunctionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFunctionNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFunctionNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}