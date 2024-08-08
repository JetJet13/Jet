//
// Created by Johny Georges on 2024-07-25.
//

#ifndef JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/enum-type-signature/enum-type-signature.h"
#include "../../../../ir-type/ir-pointer-type.h"
#include "../../../../../core/type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"

class EnumAccessTypeSignatureIRStrategy {
public:
    IRType* generate(EnumAccessTypeSignature* enumAccessTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
};

#endif //JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_IR_STRATEGY_H
