//
// Created by Johny Georges on 2024-05-25.
//

#include "procedure-declaration-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../jet-utils-type-signature-map/jet-utils-type-signature-map.h"
#include "../../../../../../shared/utils/function-id-generator/function-id-generator.h"

namespace ProcedureDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTProcedureDeclarationNode> procedureDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getParameters(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getBlock(), typeCheckerResult, fileScope);
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