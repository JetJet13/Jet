//
// Created by Johny Georges on 2024-04-09.
//

#include "array-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

ASTNode* ArrayTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array type since nodes list is not of size 2");
    }

    auto parameterList = (ASTTypeParameterListNode*)nodes[1];
    return ASTTypeNodeFactory::createArrayTypeNode(
            new ASTArrayTypeNode(
                    (ASTTypeNode*)parameterList->getParameters()[0]
            )
    );
}