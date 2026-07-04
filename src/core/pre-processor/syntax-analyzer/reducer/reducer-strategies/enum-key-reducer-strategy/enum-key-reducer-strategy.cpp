//
// Created by Johny Georges on 2024-03-23.
//

#include "enum-key-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

std::shared_ptr<ASTNode> EnumKeyReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to enum key since nodes list is not 2");
    }
    return std::make_shared<ASTEnumKeyNode>(
            (std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(nodes[0]))->getIdentifierNode()->getLexeme()
    );
}
