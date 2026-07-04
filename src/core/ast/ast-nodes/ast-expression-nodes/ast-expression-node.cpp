//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-expression-node.h"
#include "../ast-function-nodes/ast-function-argument-node.h"
#include "../ast-tuple-nodes/ast-tuple-item-node.h"


void ASTExpressionNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

std::string ASTExpressionNode::getModuleId() {
    return "";
}

TypeSignature* ASTExpressionNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<ASTNode> ASTExpressionNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    return this->baseTransformIfNecessary(prevNode, nextNode, mode);
}

bool ASTExpressionNode::isExpression() {
    return true;
}

ASTNodeType ASTExpressionNode::getNodeType() {
    return AST_EXPRESSION_NODE;
}

std::string ASTExpressionNode::toString() {
    return "EXPRESSION";
}

bool ASTExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    return other->is(this->getNodeType());
}

std::shared_ptr<ASTNode> ASTExpressionNode::baseTransformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({AST_COMMA_NODE, AST_FUNCTION_ARGUMENT_LIST_START_NODE }) &&
        nextNode && nextNode.value()->isOneOf({AST_COMMA_NODE, AST_FUNCTION_ARGUMENT_LIST_END_NODE }) &&
        mode == SA_FUNCTION_ARGUMENT_LIST_MODE) {
        return std::make_shared<ASTFunctionArgumentNode>(std::dynamic_pointer_cast<ASTExpressionNode>(shared_from_this()));
    }

    if (prevNode && prevNode.value()->isOneOf({AST_COMMA_NODE, AST_TUPLE_LIST_START_NODE }) &&
        nextNode && nextNode.value()->isOneOf({AST_COMMA_NODE, AST_TUPLE_LIST_END_NODE }) &&
        mode == SA_TUPLE_LIST_MODE) {
        return std::make_shared<ASTTupleItemNode>(std::dynamic_pointer_cast<ASTExpressionNode>(shared_from_this()));
    }

    return shared_from_this();
}