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