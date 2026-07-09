//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/class-type-signature/class-type-signature.h"
#include "../../../../ir-type/ir-class-type.h"

class ClassTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRClassType> generate(std::shared_ptr<ClassTypeSignature> classTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IRClassType> generateInitial(std::shared_ptr<ClassTypeSignature> classTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IRClassType> generatePostInitial(std::shared_ptr<ClassTypeSignature> classTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H
