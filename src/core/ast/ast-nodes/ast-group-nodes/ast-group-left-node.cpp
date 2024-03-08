//
// Created by Johny Georges on 2024-03-07.
//

#include "ast-group-left-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTGroupStartNode::ASTGroupStartNode(Lexeme *lexeme) {
_lexeme = lexeme;
}

Lexeme* ASTGroupStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTGroupStartNode::getNodeType() {
    return AST_GROUP_START_NODE;
}

std::string ASTGroupStartNode::toString() {
    return "GROUP_START";
}

bool ASTGroupStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTGroupStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTGroupStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}