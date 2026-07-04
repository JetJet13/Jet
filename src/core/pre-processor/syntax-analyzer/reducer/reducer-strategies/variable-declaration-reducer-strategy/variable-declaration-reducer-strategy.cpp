//
// Created by Johny Georges on 2024-02-17.
//

#include "variable-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"

std::shared_ptr<ASTNode> VariableDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2 && nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to var declaration since nodes list is not 2 or 3");
    }

    if (nodes.size() == 2) {
        auto variable = std::make_shared<ASTVariableDeclarationNode>(
                std::dynamic_pointer_cast<ASTVariableInitNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
        );
        variable->getVarInitNode()->setParentNode(variable);
        variable->getInitializerNode()->setParentNode(variable);
        return variable;
    } else {
        auto variable = std::make_shared<ASTVariableDeclarationNode>(
                std::dynamic_pointer_cast<ASTVariableInitNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTExpressionNode>(nodes[2]),
                std::dynamic_pointer_cast<ASTExportNode>(nodes[0])
        );
        variable->getVarInitNode()->setParentNode(variable);
        variable->getInitializerNode()->setParentNode(variable);
        return variable;
    }
}
