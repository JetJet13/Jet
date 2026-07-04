//
// Created by Johny Georges on 2024-04-10.
//

#include "variable-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-definition-node.h"

std::shared_ptr<ASTNode> VariableDefinitionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to var definition node since nodes list is not 2");
    }

    return std::make_shared<ASTVariableDefinitionNode>(
            std::dynamic_pointer_cast<ASTVariableTypeNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTIdentifierNode>(nodes[1])
    );
}