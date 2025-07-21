//
// Created by Johny Georges on 2025-07-21.
//

#include "print-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-print-node.h"

void PrintIdStrategy::assign(ASTNode* node) {
    auto printNode = (ASTPrintNode*)node;
    printNode->setId(
        _tokenTable->getIdentifier(
            printNode
            ->getLexeme()
            ->getToken()
            ->getValueId().value()
        )
    );
}