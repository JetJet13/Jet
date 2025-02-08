//
// Created by Johny Georges on 2025-02-07.
//

#include "ref-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

ASTNode* RefTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to ref type since nodes list is not of size 2");
    }

    return ASTTypeNodeFactory::createRefTypeNode(
            new ASTRefTypeNode(
                (ASTRefTypeKeywordNode*)nodes[0],
                (ASTTypeParameterListNode*)nodes[1]
            )
    );
}