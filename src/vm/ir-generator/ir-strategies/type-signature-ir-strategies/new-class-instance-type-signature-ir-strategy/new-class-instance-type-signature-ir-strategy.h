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
