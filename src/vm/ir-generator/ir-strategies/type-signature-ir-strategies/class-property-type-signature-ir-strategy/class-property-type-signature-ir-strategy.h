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
