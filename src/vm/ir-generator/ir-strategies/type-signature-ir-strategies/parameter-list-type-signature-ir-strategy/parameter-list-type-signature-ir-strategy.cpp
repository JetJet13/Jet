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
// Created by Johny Georges on 2024-07-12.
//

#include "parameter-list-type-signature-ir-strategy.h"

std::shared_ptr<IRParameterListType> ParameterListTypeSignatureIRStrategy::generate(std::shared_ptr<ParameterListTypeSignature> parameterListTypeSignature,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::optional<std::shared_ptr<ParameterListItemTypeSignature>> scopeParameter) {
    auto parameters = std::vector<std::shared_ptr<IRParameterType>>();
    for (auto parameter : *parameterListTypeSignature->getParameters()) {
        parameters.push_back(irGenerator->generateParameterType(parameter, scope, irContext));
    }

    if (scopeParameter) {
        parameters.push_back(irGenerator->generateParameterType(scopeParameter.value(), scope, irContext));
    }

    return std::make_shared<IRParameterListType>(parameters);
}