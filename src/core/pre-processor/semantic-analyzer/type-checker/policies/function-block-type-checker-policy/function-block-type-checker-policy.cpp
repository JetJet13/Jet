//
// Created by Johny Georges on 2024-05-25.
//

#include "function-block-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace FunctionBlockTypeCheckerPolicy {
    void apply(ASTFunctionBlockNode* functionBlockNode, TypeCheckerResult* typeCheckerResult) {
        auto scopedVariableDeclarationNames = std::vector<ASTIdentifierNode*>();
        for (auto statement : *functionBlockNode->getContents()) {
            TypeChecker::applyPolicyTo(statement, typeCheckerResult);
            if (statement->is(AST_VARIABLE_DECLARATION_NODE)) {
                scopedVariableDeclarationNames.push_back(
                    ((ASTVariableDeclarationNode*)statement)
                    ->getVarInitNode()
                    ->getIdentifierNode()
                );
            }
        }

        TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
        ->enforce(
            &scopedVariableDeclarationNames,
            // todo: come back to this
            TypeCheckerErrorMessageTable::VariableNamesNotUnique(scopedVariableDeclarationNames[0]),
            typeCheckerResult
        );
    }
}