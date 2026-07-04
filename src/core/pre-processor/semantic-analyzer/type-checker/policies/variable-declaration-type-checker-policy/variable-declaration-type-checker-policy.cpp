//
// Created by Johny Georges on 2024-05-21.
//

#include "variable-declaration-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../jet-utils-type-signature-map/jet-utils-type-signature-map.h"

namespace VariableDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTVariableDeclarationNode> variableDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        auto varTypeSignature = variableDeclarationNode->getTypeSignature();
        auto initializerTypeSignature = variableDeclarationNode->getInitializerNode()->getTypeSignature();
        auto unknownMessage = TypeCheckerErrorMessageTable::VariableTypeUnknown(variableDeclarationNode);
        auto invalidMessage = TypeCheckerErrorMessageTable::VariableTypeInvalid(variableDeclarationNode);
        auto voidMessage = TypeCheckerErrorMessageTable::VariableTypeVoid(variableDeclarationNode);
        TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule()
        ->enforce(
            varTypeSignature,
            unknownMessage,
            invalidMessage,
            voidMessage,
            typeCheckerResult
        );

        if (variableDeclarationNode->isGlobal() && JetUtilsTypeSignatureMap::doesIdConflict(variableDeclarationNode->getId())){
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::GlobalVariableNameConflictsWithBuiltInFunctionName(variableDeclarationNode)());
        }

        if (!varTypeSignature->isEquivalentTo(initializerTypeSignature->convertToVariableTypeSignature())){
            typeCheckerResult->addError(TypeCheckerErrorMessageTable::VariableTypeMismatch(variableDeclarationNode)());
        }

        TypeChecker::applyPolicyTo(variableDeclarationNode->getInitializerNode(), typeCheckerResult);
    }
}
