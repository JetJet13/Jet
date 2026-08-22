//
// Created by Johny Georges on 2024-05-25.
//

#include "function-block-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace FunctionBlockTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionBlockNode> functionBlockNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto variableDeclarations = std::vector<std::shared_ptr<ASTVariableDeclarationNode>>();
        for (auto statement : *functionBlockNode->getContents()) {
            TypeChecker::applyPolicyTo(statement, typeCheckerResult, fileScope);
            if (statement->is(AST_VARIABLE_DECLARATION_NODE)) {
                variableDeclarations.push_back(std::dynamic_pointer_cast<ASTVariableDeclarationNode>(statement));
            }
        }

        TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
        ->enforce(
            &variableDeclarations,
            typeCheckerResult
        );
    }
}