//
// Created by Johny Georges on 2024-06-17.
//

#ifndef JETLANG_ARRAY_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_ARRAY_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/type-signature/array-type-signature/array-type-signature.h"
#include "../../../ir-generator.h"


class ArrayTypeSignatureIRStrategy {
public:
    IRArrayPointerType* generate(ArrayTypeSignature* arrayTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
};

#endif //JETLANG_ARRAY_TYPE_SIGNATURE_IR_STRATEGY_H
