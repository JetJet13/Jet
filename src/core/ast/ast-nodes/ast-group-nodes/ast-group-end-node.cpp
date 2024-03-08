//
// Created by Johny Georges on 2024-03-07.
//

#include "ast-group-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTGroupEndNode::ASTGroupEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTGroupEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTGroupEndNode::getNodeType() {
    return AST_GROUP_END_NODE;
}

std::string ASTGroupEndNode::toString() {
    return "GROUP_END";
}

bool ASTGroupEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTGroupEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTGroupEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}