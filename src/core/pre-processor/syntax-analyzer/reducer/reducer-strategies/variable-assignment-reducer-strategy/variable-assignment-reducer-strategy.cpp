//
// Created by Johny Georges on 2024-03-22.
//

#include "variable-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-assignment-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

ASTNode* VariableAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to variable assignment since nodes list is not 2");
    }
    return new ASTVariableAssignmentNode(
            ((ASTIdentifierExpressionNode*)nodes[0])->getIdentifierNode()
    );
}
