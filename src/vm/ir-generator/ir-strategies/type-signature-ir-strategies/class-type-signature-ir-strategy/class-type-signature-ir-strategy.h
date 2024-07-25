//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/class-type-signature/class-type-signature.h"

class ClassTypeSignatureIRStrategy {
public:
    IRStructType* generate(ClassTypeSignature* classTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_IR_STRATEGY_H
