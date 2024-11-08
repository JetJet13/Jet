//
// Created by Johny Georges on 2024-11-06.
//

#include "module-access-expression-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-module-access-expression-node.h"

void ModuleAccessExpressionIdStrategy::assign(ASTNode* node) {
    auto moduleAccessExpression = (ASTModuleAccessExpressionNode*)node;
    moduleAccessExpression->setId(
            _tokenTable->getIdentifier(
                    moduleAccessExpression
                    ->getSource()
                    ->getSource()
                    ->getIdentifierNode()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId()
                    .value()
            )
            + "::"
            + _tokenTable->getIdentifier(
                    moduleAccessExpression
                    ->getTarget()
                    ->getTarget()
                    ->getIdentifierNode()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId()
                    .value()
            )
    );
}