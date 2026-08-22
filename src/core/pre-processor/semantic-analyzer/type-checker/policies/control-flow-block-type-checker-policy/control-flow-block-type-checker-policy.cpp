//
// Created by Johny Georges on 2024-05-27.
//

#include "control-flow-block-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace ControlFlowBlockTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTControlFlowBlockNode> controlFlowBlockNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto variableDeclarations = std::vector<std::shared_ptr<ASTVariableDeclarationNode>>();
        auto blockScope = std::make_shared<TypeSignatureLookupTable>(fileScope);
        for (auto statement : *controlFlowBlockNode->getContents()) {
            TypeChecker::applyPolicyTo(statement, typeCheckerResult, blockScope);
            if (statement->is(AST_VARIABLE_DECLARATION_NODE)) {
                auto variable = std::dynamic_pointer_cast<ASTVariableDeclarationNode>(statement);
                auto variableContext = std::make_shared<VariableContext>();
                if (variable->isConst()) {
                    variableContext->markAsConstant();
                }
                blockScope->insert(variable->getId(), variable->getTypeSignature());
                blockScope->insertVariableContext(variable->getId(), variableContext);
                variableDeclarations.push_back(variable);
            }
        }

        TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule()
        ->enforce(
            &variableDeclarations,
            typeCheckerResult
        );
    }
}