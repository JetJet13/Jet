//
// Created by Johny Georges on 2024-07-11.
//

#ifndef JETLANG_STRUCT_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_STRUCT_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/struct-type-signature/struct-type-signature.h"

class StructTypeSignatureIRStrategy {
public:
    IRStructType* generate(StructTypeSignature* structTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRInstructionNode* generateTypeValue(IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext);
};

#endif //JETLANG_STRUCT_TYPE_SIGNATURE_IR_STRATEGY_H
