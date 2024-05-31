//
// Created by Johny Georges on 2024-05-31.
//

#include "procedure-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

ASTNode* ProcedureTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return ASTTypeNodeFactory::createProcedureTypeNode(
        new ASTProcedureTypeNode((ASTProcedureLambdaTypeParameterListNode*)nodes[0])
    );
}