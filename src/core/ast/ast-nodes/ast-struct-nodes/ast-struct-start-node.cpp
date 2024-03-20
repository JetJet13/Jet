//
// Created by Johny Georges on 2024-03-20.
//

#include "ast-struct-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTStructStartNode::ASTStructStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTStructStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTStructStartNode::getNodeType() {
    return AST_STRUCT_START_NODE;
}

std::string ASTStructStartNode::toString() {
    return "STRUCT_START";
}

bool ASTStructStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTStructStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTStructStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}