//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-identifier-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "ast-function-nodes/ast-function-name-node.h"

ASTIdentifierNode::ASTIdentifierNode(Lexeme *lexeme) {
    _identifier = lexeme;
}

Lexeme* ASTIdentifierNode::getIdentifier() {
    return _identifier;
}

ASTNode* ASTIdentifierNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, HandleMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_NODE })) {
        return new ASTFunctionNameNode(this->getIdentifier());
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