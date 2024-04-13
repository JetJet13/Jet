//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleListEndNode::ASTModuleListEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTModuleListEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTModuleListEndNode::getNodeType() {
    return AST_MODULE_LIST_END_NODE;
}

std::string ASTModuleListEndNode::toString() {
    return "MODULE_LIST_END";
}

bool ASTModuleListEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleListEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTModuleListEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}