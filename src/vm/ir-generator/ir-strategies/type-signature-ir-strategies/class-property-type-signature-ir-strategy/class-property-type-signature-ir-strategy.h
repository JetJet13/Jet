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
// Created by Johny Georges on 2025-10-22.
//

#ifndef JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-type/ir-function-type.h"
#include "../../../../../core/type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"
#include "../../../ir-generator.h"

class ClassPropertyTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRType> generate(std::shared_ptr<ClassPropertyTypeSignature> classPropertyTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_CLASS_PROPERTY_TYPE_SIGNATURE_IR_STRATEGY_H
