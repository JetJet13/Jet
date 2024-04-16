//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-dot-dot-dot-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-module-nodes/ast-module-spread-node.h"

ASTDotDotDotBaseNode::ASTDotDotDotBaseNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTDotDotDotBaseNode::getLexeme() {
    return _lexeme;
}

ASTNode* ASTDotDotDotBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_MODULE_LIST_MODE || mode == SA_IMPORT_MODULE_LIST_MODE) {
        return new ASTModuleSpreadNode(_lexeme);
    }

    return this;
}

ASTNodeType ASTDotDotDotBaseNode::getNodeType() {
    return AST_DOT_DOT_DOT_BASE_NODE;
}

std::string ASTDotDotDotBaseNode::toString() {
    return "DOT_DOT_DOT_BASE";
}

bool ASTDotDotDotBaseNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTDotDotDotBaseNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTDotDotDotBaseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}