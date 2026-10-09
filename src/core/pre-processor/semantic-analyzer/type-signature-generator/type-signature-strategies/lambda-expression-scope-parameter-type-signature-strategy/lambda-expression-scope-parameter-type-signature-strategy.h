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
// Created by Johny Georges on 2024-11-11.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_SCOPE_PARAMETER_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LAMBDA_EXPRESSION_SCOPE_PARAMETER_TYPE_SIGNATURE_STRATEGY_H

#include <set>
#include "../../../../../type-signature/type-signature.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../type-signature-strategy-provider.h"

class LambdaExpressionScopeParameterTypeSignatureStrategy {
public:
    std::shared_ptr<ParameterListItemTypeSignature> create(std::set<std::string>* captureVariableIds);
};


#endif //JETLANG_LAMBDA_EXPRESSION_SCOPE_PARAMETER_TYPE_SIGNATURE_STRATEGY_H
