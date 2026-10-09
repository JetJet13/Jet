// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-05-21.
//

#include "variable-declaration-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../jet-utils-type-signature-map/jet-utils-type-signature-map.h"

namespace VariableDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTVariableDeclarationNode> variableDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
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

        TypeChecker::applyPolicyTo(variableDeclarationNode->getInitializerNode(), typeCheckerResult, fileScope);
    }
}
