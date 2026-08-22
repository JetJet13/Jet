//
// Created by Johny Georges on 2024-05-25.
//

#include "procedure-declaration-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../jet-utils-type-signature-map/jet-utils-type-signature-map.h"

namespace ProcedureDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTProcedureDeclarationNode> procedureDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto procedureScope = std::make_shared<TypeSignatureLookupTable>();
        procedureScope->inheritGlobalScope(fileScope);
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getParameters(), typeCheckerResult, procedureScope);
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getBlock(), typeCheckerResult, procedureScope);
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