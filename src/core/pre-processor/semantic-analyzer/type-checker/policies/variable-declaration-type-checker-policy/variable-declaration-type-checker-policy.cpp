//
// Created by Johny Georges on 2024-05-21.
//

#include "variable-declaration-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../type-checker.h"

namespace VariableDeclarationTypeCheckerPolicy {
    void apply(ASTVariableDeclarationNode* variableDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        auto varTypeSignature = variableDeclarationNode->getTypeSignature();
        auto initializerTypeSignature = variableDeclarationNode->getInitializerNode()->getTypeSignature();
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            varTypeSignature,
            TypeCheckerErrorMessageTable::VariableTypeUnknown(
                variableDeclarationNode
            ),
            TypeCheckerErrorMessageTable::VariableTypeInvalid(
                variableDeclarationNode
            ),
            TypeCheckerErrorMessageTable::VariableTypeVoid(
                variableDeclarationNode
            ),
            typeCheckerResult
        );

       if (!varTypeSignature->isEquivalentTo(initializerTypeSignature)){
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::VariableTypeMismatch(
                    variableDeclarationNode
            ));
        }

        TypeChecker::applyPolicyTo(variableDeclarationNode->getInitializerNode(), typeCheckerResult);
    }
}
