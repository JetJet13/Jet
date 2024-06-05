//
// Created by Johny Georges on 2024-03-22.
//

#include "procedure-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"

ASTNode* ProcedureDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to procedure declaration since nodes list is not of size 4");
    }

    return new ASTProcedureDeclarationNode(
            (ASTProcedureNode*)nodes[0],
            (ASTFunctionNameNode*)nodes[1],
            (ASTFunctionParameterListNode*)nodes[2],
            (ASTFunctionBlockNode*)nodes[3]
    );
}