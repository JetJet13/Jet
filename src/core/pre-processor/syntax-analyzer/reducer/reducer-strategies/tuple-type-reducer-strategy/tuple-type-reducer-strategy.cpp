//
// Created by Johny Georges on 2024-04-09.
//

#include "tuple-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

ASTNode* TupleTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple type since nodes list is not of size 2");
    }

    return ASTTypeNodeFactory::createTupleTypeNode(
        new ASTTupleTypeNode((ASTTypeParameterListNode*)nodes[1])
    );
}