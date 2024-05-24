//
// Created by Johny Georges on 2024-05-21.
//

#include "variable-declaration-type-checker-policy.h"


TypeCheckerResult VariableDeclarationTypeCheckerPolicy::verify(ASTVariableDeclarationNode* variableDeclarationNode) {
    auto varTypeSignature = variableDeclarationNode->getTypeSignature();
    auto initializerTypeSignature = variableDeclarationNode->getInitializerNode()->getTypeSignature();
    if (varTypeSignature->isEqualTo(initializerTypeSignature)) {
        return {
            .ok = true,
            .errors = {}
        };
    }
    return {
        .ok = false,
        .errors = { "variable type does not match initializer type" }
    };
}