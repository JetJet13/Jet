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
    IRClassType* generate(ClassTypeSignature* classTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H
