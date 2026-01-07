//
// Created by Johny Georges on 2024-03-07.
//

#include "ast-group-end-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-end-node.h"
#include "../ast-function-nodes/ast-function-argument-list-end-node.h"
#include "../ast-type-nodes/ast-lambda-type-nodes/ast-lambda-type-parameter-list-end-node.h"

ASTNode * ASTGroupEndNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_LAMBDA_TYPE_PARAMETER_LIST_MODE) {
        return new ASTLambdaTypeParameterListEndNode(this->getLexeme());
    }

    if (mode == SA_FUNCTION_PARAMETER_LIST_MODE) {
        return new ASTFunctionParameterListEndNode(this->getLexeme());
    }

    if (nextNode && nextNode.value()->isOneOf({ AST_FAT_ARROW_BASE_NODE, AST_BLOCK_START_NODE })) {
        return new ASTFunctionParameterListEndNode(this->getLexeme());
    }

    if (mode == SA_FUNCTION_ARGUMENT_LIST_MODE) {
        return new ASTFunctionArgumentListEndNode(this->getLexeme());
    }

    return this;
}

ASTNodeType ASTGroupEndNode::getNodeType() {
    return AST_GROUP_END_NODE;
}

std::string ASTGroupEndNode::toString() {
    return "GROUP_END";
}
