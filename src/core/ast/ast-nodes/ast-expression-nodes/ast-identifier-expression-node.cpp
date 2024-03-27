//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-identifier-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-type-node.h"
#include "../ast-object-nodes/ast-object-access-source-node.h"

ASTIdentifierExpressionNode::ASTIdentifierExpressionNode(ASTIdentifierNode* identifierNode) {
    _identifierNode = identifierNode;
}

ASTIdentifierNode* ASTIdentifierExpressionNode::getIdentifierNode() {
    return _identifierNode;
}

ASTNode* ASTIdentifierExpressionNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_COLON_NODE }) && mode == SA_FUNCTION_PARAMETER_LIST_MODE) {
        return new ASTTypeNode(this->getIdentifierNode()->getIdentifier());
    }

    return this;
}

ASTNodeType ASTIdentifierExpressionNode::getNodeType() {
    return AST_IDENTIFIER_EXPRESSION_NODE;
}

std::string ASTIdentifierExpressionNode::toString() {
    return "IDENTIFIER_EXPRESSION";
}

bool ASTIdentifierExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTIdentifierExpressionNode*)other;
    return this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTIdentifierExpressionNode::print() {
    Logger::log(this->toString(), "-", _identifierNode->toString());
}