//
// Created by Johny Georges on 2024-12-27.
//

#ifndef JETLANG_CLASS_METHOD_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_CLASS_METHOD_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-type/ir-function-type.h"
#include "../../../../../core/type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../../../ir-generator.h"

class ClassMethodTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRFunctionType> generate(std::shared_ptr<ClassMethodTypeSignature> classMethodTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_CLASS_METHOD_TYPE_SIGNATURE_IR_STRATEGY_H
