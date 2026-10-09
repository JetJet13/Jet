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
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_ENUM_KEY_VALUE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ENUM_KEY_VALUE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"
#include "../../type-signature-strategy-provider.h"

class EnumKeyValueTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTEnumKeyValueNode> node, std::shared_ptr<TypeSignatureContext> context, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_ENUM_KEY_VALUE_TYPE_SIGNATURE_STRATEGY_H
