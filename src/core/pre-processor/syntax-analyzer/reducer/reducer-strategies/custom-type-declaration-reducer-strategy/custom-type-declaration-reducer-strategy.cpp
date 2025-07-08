//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

ASTNode* CustomTypeDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 4 && nodes.size() != 5) {
        throw std::invalid_argument("unable to reduce to custom type declaration since nodes list is not of size 4 or 5");
    }

    if (nodes.size() == 4) {
        return new ASTCustomTypeDeclarationNode(
                (ASTTypeKeywordNode*)nodes[0],
                (ASTTypeNameNode*)nodes[1],
                (ASTTypeAssignmentOperatorNode*)nodes[2],
                (ASTTypeNode*)nodes[3]
        );
    }

    return new ASTCustomTypeDeclarationNode(
            (ASTTypeKeywordNode*)nodes[1],
            (ASTTypeNameNode*)nodes[2],
            (ASTTypeAssignmentOperatorNode*)nodes[3],
            (ASTTypeNode*)nodes[4],
            (ASTExportNode*)nodes[0]
    );
}