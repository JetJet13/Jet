//
// Created by Johny Georges on 2024-05-02.
//

#include "procedure-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"

void ProcedureDeclarationIdStrategy::assign(ASTNode* node) {
    auto procedureDeclarationNode = (ASTProcedureDeclarationNode*)node;
    procedureDeclarationNode->setId(
            _tokenTable->getIdentifier(
                procedureDeclarationNode
                ->getName()
                ->getName()
                ->getToken()
                ->getValueId()
                .value()
            ).value()
    );
}