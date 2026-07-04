//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

std::shared_ptr<ASTNode> CustomTypeDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 4 && nodes.size() != 5) {
        throw std::invalid_argument("unable to reduce to custom type declaration since nodes list is not of size 4 or 5");
    }

    if (nodes.size() == 4) {
        return std::make_shared<ASTCustomTypeDeclarationNode>(
                std::dynamic_pointer_cast<ASTTypeKeywordNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTTypeNameNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTTypeAssignmentOperatorNode>(nodes[2]),
                std::dynamic_pointer_cast<ASTTypeNode>(nodes[3])
        );
    }

    return std::make_shared<ASTCustomTypeDeclarationNode>(
            std::dynamic_pointer_cast<ASTTypeKeywordNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTTypeNameNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTTypeAssignmentOperatorNode>(nodes[3]),
            std::dynamic_pointer_cast<ASTTypeNode>(nodes[4]),
            std::dynamic_pointer_cast<ASTExportNode>(nodes[0])
    );
}