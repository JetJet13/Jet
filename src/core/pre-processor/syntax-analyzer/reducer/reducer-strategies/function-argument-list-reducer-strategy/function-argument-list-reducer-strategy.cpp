//
// Created by Johny Georges on 2024-03-25.
//

#include "function-argument-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-node.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"

ASTNode* FunctionArgumentListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto functionArgumentListNode = new ASTFunctionArgumentListNode((ASTFunctionArgumentListStartNode*)nodes[0], (ASTFunctionArgumentListEndNode*)nodes[nodes.size() - 1]);
    for (int i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_FUNCTION_ARGUMENT_NODE)) {
            functionArgumentListNode->addArgument((ASTFunctionArgumentNode*)node);
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            functionArgumentListNode->addComma((ASTCommaNode*)node);
        } else {
            throw std::invalid_argument("unable to reduce to function argument list since node list is malformed");
        }
    }
    return functionArgumentListNode;
}