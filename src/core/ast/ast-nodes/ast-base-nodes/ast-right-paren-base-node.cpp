//
// Created by Johny Georges on 2026-06-06.
//

#include "ast-right-paren-base-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-end-node.h"
#include "../ast-function-nodes/ast-function-argument-list-end-node.h"
#include "../ast-type-nodes/ast-lambda-type-nodes/ast-lambda-type-parameter-list-end-node.h"
#include "../ast-group-nodes/ast-group-end-node.h"

ASTNode* ASTRightParenBaseNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_INTERMEDIATE_MODE) {
        return this;
    }

    if (mode == SA_LAMBDA_TYPE_PARAMETER_LIST_MODE) {
        return new ASTLambdaTypeParameterListEndNode(this->getLexeme());
    }

    if (nextNode && nextNode.value()->isOneOf({ AST_LAMBDA_TYPE_FAT_ARROW_NODE })) {
        return new ASTLambdaTypeParameterListEndNode(this->getLexeme());
    }

    if (mode == SA_FUNCTION_PARAMETER_LIST_MODE) {
        return new ASTFunctionParameterListEndNode(this->getLexeme());
    }

    if (mode == SA_FUNCTION_ARGUMENT_LIST_MODE) {
        return new ASTFunctionArgumentListEndNode(this->getLexeme());
    }

    if (nextNode && nextNode.value()->isOneOf({ AST_FAT_ARROW_BASE_NODE, AST_BLOCK_START_NODE })) {
        return new ASTFunctionParameterListEndNode(this->getLexeme());
    }

    return new ASTGroupEndNode(this->getLexeme());
}

ASTNodeType ASTRightParenBaseNode::getNodeType() {
    return AST_RIGHT_PAREN_BASE_NODE;
}

std::string ASTRightParenBaseNode::toString() {
    return "RIGHT_PAREN_BASE";
}