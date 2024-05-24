//
// Created by Johny Georges on 2024-05-21.
//

#include "type-checker.h"

TypeCheckerResult TypeChecker::applyPolicyFor(ASTNode* node) {
    switch (node->getNodeType()) {
        case AST_VARIABLE_DECLARATION_NODE:
            return VariableDeclarationTypeCheckerPolicy::verify((ASTVariableDeclarationNode*)node);
        default:
            throw std::logic_error("no type-signature policy found for " + node->toString());
    }
}