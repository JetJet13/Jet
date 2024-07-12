//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_VOID_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_VOID_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/void-type-signature/void-type-signature.h"

class VoidTypeSignatureIRStrategy {
public:
    IRType* generate(std::unique_ptr<llvm::LLVMContext>* context);
};

#endif //JETLANG_VOID_TYPE_SIGNATURE_IR_STRATEGY_H
