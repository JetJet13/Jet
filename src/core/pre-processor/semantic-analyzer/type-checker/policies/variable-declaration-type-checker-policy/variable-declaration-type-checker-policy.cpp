//
// Created by Johny Georges on 2024-05-21.
//

#include "variable-declaration-type-checker-policy.h"
#include "../../types/type-checker-result-factory.h"
#include "../../types/type-checker-error-message-table.h"

namespace VariableDeclarationTypeCheckerPolicy {
    void apply(ASTVariableDeclarationNode* variableDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        auto varTypeSignature = variableDeclarationNode->getTypeSignature();
        auto initializerTypeSignature = variableDeclarationNode->getInitializerNode()->getTypeSignature();

        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
                ->enforce(
                        varTypeSignature,
                        TypeCheckerErrorMessageTable::VariableTypeUnknown,
                        TypeCheckerErrorMessageTable::VariableTypeInvalid,
                        TypeCheckerErrorMessageTable::VariableTypeVoid,
                        typeCheckerResult
                );

       if (!varTypeSignature->isEqualTo(initializerTypeSignature)){
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::VariableTypeMismatch);
        }
    }
}
