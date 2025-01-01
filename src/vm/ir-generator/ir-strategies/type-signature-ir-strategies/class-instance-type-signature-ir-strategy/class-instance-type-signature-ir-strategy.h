//
// Created by Johny Georges on 2024-12-31.
//

#ifndef JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/enum-type-signature/enum-type-signature.h"
#include "../../../../ir-type/ir-enum-type.h"
#include "../../../../../core/type-signature/module-type-signature/module-type-signature.h"
#include "../../../../ir-type/ir-module-type.h"
#include "../../../../ir-type/ir-class-instance-type.h"
#include "../../../../../core/type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

class ClassInstanceTypeSignatureIRStrategy {
public:
    IRClassInstanceType* generate(ClassInstanceTypeSignature* classInstanceTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_IR_STRATEGY_H
