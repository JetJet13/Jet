//
// Created by Johny Georges on 2024-03-19.
//

#include "function-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"

ASTNode* FunctionParameterListReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto functionParameterListNode = new ASTFunctionParameterListNode(
            (ASTFunctionParameterListStartNode*)nodes[0],
            (ASTFunctionParameterListEndNode*)nodes[nodes.size() - 1]
    );

    for (unsigned long i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_FUNCTION_PARAMETER_NODE)) {
            functionParameterListNode->addParameter((ASTFunctionParameterNode*)node);
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            functionParameterListNode->addComma((ASTCommaNode*)node);
        } else {
            throw std::invalid_argument("unable to reduce to function parameter list since node list is malformed");
        }
    }

    return functionParameterListNode;
}