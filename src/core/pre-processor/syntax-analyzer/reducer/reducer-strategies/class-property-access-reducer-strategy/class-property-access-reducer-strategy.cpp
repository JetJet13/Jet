//
// Created by Johny Georges on 2024-04-24.
//

#include "class-property-access-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-access-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-access-node.h"

std::shared_ptr<ASTNode> ClassPropertyAccessReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class property access since nodes list is not 2");
    }
    return std::make_shared<ASTClassPropertyAccessNode>(
            std::dynamic_pointer_cast<ASTClassAccessNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTClassPropertyNameNode>(nodes[1])
    );
}