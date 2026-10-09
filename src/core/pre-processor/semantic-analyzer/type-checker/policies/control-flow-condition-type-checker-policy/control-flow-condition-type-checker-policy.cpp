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

#include "control-flow-condition-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"


namespace ControlFlowConditionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTControlFlowConditionNode> controlFlowConditionNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        auto mismatchMessage = TypeCheckerErrorMessageTable::ControlFlowConditionNotBool(controlFlowConditionNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            controlFlowConditionNode->getTypeSignature(),
            std::make_shared<BoolLiteralTypeSignature>(),
            mismatchMessage,
            typeCheckerResult
        );
    }
}