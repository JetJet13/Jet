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
// Created by Johny Georges on 2024-05-27.
//

#include "for-in-statement-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace ForInStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTForInStatementNode> forStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(forStatementNode->getBlock(), typeCheckerResult, fileScope);
        auto notIterableMessage = TypeCheckerErrorMessageTable::ForInStatementSourceNotIterable(forStatementNode->getSource());

        auto sourceTypeSignature = forStatementNode->getSource()->getTypeSignature();
        if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
            auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature);
            sourceTypeSignature = sharedTypeSignature->getUnderlyingType();
        }
        TypeCheckerRuleProvider::getIterableTypeSignatureTypeCheckerRule()
        ->enforce(
            sourceTypeSignature,
            notIterableMessage,
            typeCheckerResult
        );

    }
}