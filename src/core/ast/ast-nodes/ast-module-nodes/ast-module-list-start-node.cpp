//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleListStartNode::ASTModuleListStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTModuleListStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTModuleListStartNode::getNodeType() {
    return AST_MODULE_LIST_START_NODE;
}

std::string ASTModuleListStartNode::toString() {
    return "MODULE_LIST_START";
}

bool ASTModuleListStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleListStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTModuleListStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}