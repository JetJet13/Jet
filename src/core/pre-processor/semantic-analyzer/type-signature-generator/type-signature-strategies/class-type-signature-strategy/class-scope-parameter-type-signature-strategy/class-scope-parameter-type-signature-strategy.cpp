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
// Created by Johny Georges on 2024-12-09.
//

#include "class-scope-parameter-type-signature-strategy.h"

std::shared_ptr<ParameterListItemTypeSignature> ClassScopeParameterTypeSignatureStrategy::create(std::shared_ptr<ClassTypeSignature> classTypeSignature) {
    auto scopeParameterTypeSignature = std::make_shared<StructTypeSignature>();
    for (const auto& keyValue : classTypeSignature->getInstanceProperties()->getKeyValues()) {
        auto typeSignature = keyValue.second->getType()->convertToVariableTypeSignature();
        scopeParameterTypeSignature->addKeyValuePair(classTypeSignature->stripClassNameFromKey(keyValue.first), typeSignature);
    }
    return ParameterListItemTypeSignature::createClassScopeParameter(std::make_shared<PointerTypeSignature>(scopeParameterTypeSignature));
}