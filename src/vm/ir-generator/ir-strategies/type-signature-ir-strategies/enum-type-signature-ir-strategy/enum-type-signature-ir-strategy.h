//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_ENUM_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_ENUM_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/enum-type-signature/enum-type-signature.h"
#include "../../../../ir-type/ir-enum-type.h"

class EnumTypeSignatureIRStrategy {
public:
    IRPointerType* generate(EnumTypeSignature* enumTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IREnumType* generate(EnumTypeSignature* enumTypeSignature, std::vector<llvm::Constant*> enumValues, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_ENUM_TYPE_SIGNATURE_IR_STRATEGY_H
