//
// Created by Johny Georges on 2024-05-25.
//

#include "procedure-declaration-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../jet-utils-type-signature-map/jet-utils-type-signature-map.h"

namespace ProcedureDeclarationTypeCheckerPolicy {
    void apply(ASTProcedureDeclarationNode* procedureDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getBlock(), typeCheckerResult);
        auto returnExpressionMessage = TypeCheckerErrorMessageTable::ProcedureHasReturnExpression(procedureDeclarationNode);
        TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
            procedureDeclarationNode->getBlock(),
            returnExpressionMessage,
            typeCheckerResult
        );

        if (JetUtilsTypeSignatureMap::doesIdConflict(procedureDeclarationNode->getName()->getId())){
            typeCheckerResult->addError(
                TypeCheckerErrorMessageTable::ProcedureNameConflictsWithBuiltInFunctionName(procedureDeclarationNode->getDefinition())()
            );
        }
    }
}