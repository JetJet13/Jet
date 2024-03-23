//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-identifier-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "ast-function-nodes/ast-function-name-node.h"
#include "ast-enum-nodes/ast-enum-name-node.h"
#include "ast-enum-nodes/ast-enum-key-node.h"

ASTIdentifierNode::ASTIdentifierNode(Lexeme *lexeme) {
    _identifier = lexeme;
}

Lexeme* ASTIdentifierNode::getIdentifier() {
    return _identifier;
}

ASTNode* ASTIdentifierNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_NODE, AST_PROCEDURE_NODE })) {
        return new ASTFunctionNameNode(this->getIdentifier());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_ENUM_NODE })) {
        return new ASTEnumNameNode(this->getIdentifier());
    }

    if (mode == SA_ENUM_KEY_VALUE_LIST_MODE) {
        return new ASTEnumKeyNode(this->getIdentifier());
    }

    return this;
}

ASTNodeType ASTIdentifierNode::getNodeType() {
    return AST_IDENTIFIER_NODE;
}

std::string ASTIdentifierNode::toString() {
    return "IDENTIFIER";
}

bool ASTIdentifierNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTIdentifierNode*)other;
    return this->getIdentifier()->hasSameSymbolTypeAs(otherNode->getIdentifier());
}

void ASTIdentifierNode::print() {
    Logger::log(this->toString(), "-", _identifier->toString());
}