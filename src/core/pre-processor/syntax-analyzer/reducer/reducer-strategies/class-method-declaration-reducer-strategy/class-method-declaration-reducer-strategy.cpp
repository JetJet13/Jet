//
// Created by Johny Georges on 2024-04-21.
//

#include "class-method-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"

ASTNode* ClassMethodDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 4) {
        return new ASTClassMethodDeclarationNode(
                (ASTAccessModifierNode*)nodes[0],
                (ASTClassMethodNameNode*)nodes[1],
                (ASTFunctionParameterListNode*)nodes[2],
                (ASTFunctionBlockNode*)nodes[3]
        );
    }

    if (nodes.size() == 5) {
        return new ASTClassMethodDeclarationNode(
                (ASTAccessModifierNode*)nodes[0],
                (ASTClassMethodNameNode*)nodes[1],
                (ASTFunctionParameterListNode*)nodes[2],
                (ASTFunctionBlockNode*)nodes[4],
                (ASTTypeNode*)nodes[3]
        );
    }

    throw std::invalid_argument("unable to reduce to class method declaration since nodes list is not of size 4 or 5");
}