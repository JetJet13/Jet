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

#ifndef JETLANG_NEW_CLASS_INSTANCE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_NEW_CLASS_INSTANCE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../../../../ir-type/ir-new-class-instance-type.h"

class NewClassInstanceTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRNewClassInstanceType> generate(std::shared_ptr<NewClassInstanceTypeSignature> newClassInstanceTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_NEW_CLASS_INSTANCE_TYPE_SIGNATURE_IR_STRATEGY_H
