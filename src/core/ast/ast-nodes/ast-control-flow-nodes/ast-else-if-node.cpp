//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-else-if-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTElseIfNode::ASTElseIfNode(Lexeme* elseLexeme, Lexeme* ifLexeme) {
    _else = elseLexeme;
    _if = ifLexeme;
}

Lexeme* ASTElseIfNode::getElse() {
    return _else;
}

Lexeme* ASTElseIfNode::getIf() {
    return _if;
}

ASTNodeType ASTElseIfNode::getNodeType() {
    return AST_ELSE_IF_NODE;
}

std::string ASTElseIfNode::toString() {
    return "ELSE_IF";
}

bool ASTElseIfNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTElseIfNode*)other;
    return this->getElse()->hasSameSymbolTypeAs(otherNode->getElse()) &&
           this->getIf()->hasSameSymbolTypeAs(otherNode->getIf());
}

void ASTElseIfNode::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log(_else->toString());
    Logger::log(_if->toString());
    Logger::log("----------");
}