//
// Created by Johny Georges on 2024-04-20.
//

#include "class-property-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"
#include "../../../../../../shared/utils/logger/logger.h"

ASTNode* ClassPropertyDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 2) {
        return new ASTClassPropertyDeclarationNode(
                (ASTClassPropertyInitNode*)nodes[0],
                (ASTExpressionNode*)nodes[1]
        );
    }

    if (nodes.size() == 1) {
        return new ASTClassPropertyDeclarationNode(
                (ASTClassPropertyInitNode*)nodes[0]
        );
    }
    throw std::invalid_argument("unable to reduce to class property since nodes list size is not 2 or 1");

}