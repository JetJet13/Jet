//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-expression-node.h"
#include "../ast-function-nodes/ast-function-argument-node.h"
#include "../ast-tuple-nodes/ast-tuple-item-node.h"
#include "../ast-object-nodes/ast-object-access-source-node.h"

ASTExpressionNode::ASTExpressionNode() {
    _childNodes = {};
}

void ASTExpressionNode::addChildNode(ASTNode* astNode) {
    _childNodes.push_back(astNode);
}

ASTNode* ASTExpressionNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {

    if (mode == SA_FUNCTION_ARGUMENT_LIST_MODE) {
        return new ASTFunctionArgumentNode(this);
    }

    if (mode == SA_TUPLE_LIST_MODE) {
        return new ASTTupleItemNode(this);
    }

    return this;
}

ASTNodeType ASTExpressionNode::getNodeType() {
    return AST_EXPRESSION_NODE;
}

std::string ASTExpressionNode::toString() {
    return "EXPRESSION";
}

bool ASTExpressionNode::isSameAs(ASTNode *other) {
    return other->is(this->getNodeType());
}