//
// Created by Johny Georges on 2024-03-20.
//

#include "ast-struct-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTStructEndNode::ASTStructEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTStructEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTStructEndNode::getNodeType() {
    return AST_STRUCT_END_NODE;
}

std::string ASTStructEndNode::toString() {
    return "STRUCT_END";
}

bool ASTStructEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTStructEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTStructEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}