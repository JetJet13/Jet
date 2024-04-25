//
// Created by Johny Georges on 2024-04-25.
//

#include "class-property-assignment-statement-node.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-assignment-statement-node.h"

ASTNode* ClassPropertyAssignmentStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to var declaration since nodes list is not 2");
    }
    return new ASTClassPropertyAssignmentStatementNode(
            (ASTClassPropertyAssignmentNode*)nodes[0],
            this->createExpressionNode(nodes[1])
    );
}