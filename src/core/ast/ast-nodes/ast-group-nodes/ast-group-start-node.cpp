//
// Created by Johny Georges on 2024-03-07.
//

#include "ast-group-start-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-start-node.h"
#include "../ast-function-nodes/ast-function-argument-list-start-node.h"

ASTNode* ASTGroupStartNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {

    if (mode == SA_FUNCTION_PARAMETER_LIST_MODE) {
        return new ASTFunctionParameterListStartNode(this->getLexeme());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_FUNCTION_NAME_NODE, AST_CLASS_METHOD_NAME_NODE, AST_CLASS_METHOD_DEFINITION_NODE, AST_CONSTRUCTOR_NODE })) {
        return new ASTFunctionParameterListStartNode(this->getLexeme());
    }

    if (nextNode && nextNode.value()->isOneOf({ AST_FUNCTION_PARAMETER_LIST_END_NODE })) {
        return new ASTFunctionParameterListStartNode(this->getLexeme());
    }

    if ((!prevNode ||
        prevNode && prevNode.value()->isOneOf({ AST_VARIABLE_INIT_NODE, AST_FUNCTION_RETURN_NODE, AST_LAMBDA_EXPRESSION_FAT_ARROW_NODE })) &&
        nextNode && nextNode.value()->is(AST_GROUP_END_NODE)) {
        return new ASTFunctionParameterListStartNode(this->getLexeme());
    }

    if (prevNode && prevNode.value()->isOneOf({ AST_CALLABLE_IDENTIFIER_EXPRESSION_NODE, AST_CLASS_NAME_NODE, AST_CLASS_METHOD_CALL_NODE, AST_FUNCTION_ARGUMENT_LIST_NODE })) {
        return new ASTFunctionArgumentListStartNode(this->getLexeme());
    }

    return this;
}

ASTNodeType ASTGroupStartNode::getNodeType() {
    return AST_GROUP_START_NODE;
}

std::string ASTGroupStartNode::toString() {
    return "GROUP_START";
}