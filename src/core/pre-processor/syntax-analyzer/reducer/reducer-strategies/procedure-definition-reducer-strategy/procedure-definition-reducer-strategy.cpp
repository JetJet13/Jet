//
// Created by Johny Georges on 2024-10-25.
//

#include "procedure-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-procedure-nodes/ast-procedure-definition-node.h"

ASTNode* ProcedureDefinitionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to procedure definition since nodes list is not of size 3");
    }

    return new ASTProcedureDefinitionNode(
            (ASTProcedureNode*)nodes[0],
            (ASTProcedureNameNode*)nodes[1],
            (ASTFunctionParameterListNode*)nodes[2]
    );
}