//
// Created by Johny Georges on 2024-05-27.
//

#include "control-flow-block-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace ControlFlowBlockTypeCheckerPolicy {
    void apply(ASTControlFlowBlockNode* controlFlowBlockNode, TypeCheckerResult* typeCheckerResult) {
        auto scopedVariableDeclarationNames = std::vector<ASTIdentifierNode*>();
        for (auto statement : *controlFlowBlockNode->getContents()) {
            TypeChecker::applyPolicyTo(statement, typeCheckerResult);
            if (statement->is(AST_VARIABLE_DECLARATION_NODE)) {
                scopedVariableDeclarationNames.push_back(
                    ((ASTVariableDeclarationNode*)statement)
                    ->getVarInitNode()
                    ->getIdentifierNode()
                );
            }
        }

        auto variableNamesNotUniqueMessage = TypeCheckerErrorMessageTable::VariableNamesNotUnique(controlFlowBlockNode);
        TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
        ->enforce(
            &scopedVariableDeclarationNames,
            variableNamesNotUniqueMessage,
            typeCheckerResult
        );
    }
}