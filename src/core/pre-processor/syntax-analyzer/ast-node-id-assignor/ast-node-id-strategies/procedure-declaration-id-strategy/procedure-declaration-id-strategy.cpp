//
// Created by Johny Georges on 2024-05-02.
//

#include "procedure-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"

void ProcedureDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto procedureDeclarationNode = std::dynamic_pointer_cast<ASTProcedureDeclarationNode>(node);
    procedureDeclarationNode->setId(
            _tokenTable->getIdentifier(
                procedureDeclarationNode
                ->getName()
                ->getLexeme()
                ->getToken()
                ->getValueId()
                .value()
            )
    );
}