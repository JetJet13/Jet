//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-as-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTAsNode::ASTAsNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTAsNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTAsNode::getNodeType() {
    return AST_AS_NODE;
}

std::string ASTAsNode::toString() {
    return "AS";
}

bool ASTAsNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTAsNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTAsNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}
