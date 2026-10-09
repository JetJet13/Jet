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

#include "parameter-list-type-checker-policy.h"
#include "../../type-checker.h"

namespace ParameterListTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionParameterListNode> functionParameterList, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        for (auto parameter : functionParameterList->getParameters()) {
            TypeChecker::applyPolicyTo(parameter, typeCheckerResult, fileScope);
            fileScope->insert(parameter->getIdentifier()->getId(), parameter->getTypeSignature());
            fileScope->insertVariableContext(parameter->getIdentifier()->getId(), std::make_shared<VariableContext>());
        }
    }
}