//
// Created by Johny Georges on 2024-04-24.
//

#include "class-property-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-access-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-assignment-node.h"

ASTNode* ClassPropertyAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class property assignment since nodes list is not 2");
    }
    return new ASTClassPropertyAssignmentNode(
            ((ASTClassPropertyAccessNode*)nodes[0])->getProperty()
    );
}