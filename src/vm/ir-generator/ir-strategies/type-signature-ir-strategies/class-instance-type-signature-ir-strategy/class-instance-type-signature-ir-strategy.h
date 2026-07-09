//
// Created by Johny Georges on 2025-12-26.
//

#ifndef JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-type/ir-struct-ref-type.h"
#include "../../../../../core/type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../ir-type/ir-class-instance-type.h"

class ClassInstanceTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRClassInstanceType> generate(std::shared_ptr<ClassInstanceTypeSignature> classInstanceTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_IR_STRATEGY_H
