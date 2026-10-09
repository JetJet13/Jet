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
// Created by Johny Georges on 2024-05-09.
//

#ifndef JETLANG_CUSTOM_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CUSTOM_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-custom-type-node.h"
#include "../../../../../type-signature-lookup-table/type-signature-lookup-table.h"

class CustomTypeTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTCustomTypeNode> node, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable);
};

#endif //JETLANG_CUSTOM_TYPE_TYPE_SIGNATURE_STRATEGY_H
