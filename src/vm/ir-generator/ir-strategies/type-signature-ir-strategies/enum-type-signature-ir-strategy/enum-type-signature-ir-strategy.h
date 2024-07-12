//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_ENUM_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_ENUM_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/enum-type-signature/enum-type-signature.h"

class EnumTypeSignatureIRStrategy {
public:
    IRType* generate(EnumTypeSignature* enumTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
};

#endif //JETLANG_ENUM_TYPE_SIGNATURE_IR_STRATEGY_H
