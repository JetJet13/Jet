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
// Created by Johny Georges on 2024-12-31.
//

#ifndef JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_STRATEGY_H

#include "../type-signature-strategy-provider.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"

class ArgumentListTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTFunctionArgumentListNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_STRATEGY_H
