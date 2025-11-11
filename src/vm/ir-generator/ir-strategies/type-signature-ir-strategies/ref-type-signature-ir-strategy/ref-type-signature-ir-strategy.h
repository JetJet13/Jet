//
// Created by Johny Georges on 2025-05-10.
//

#ifndef JETLANG_REF_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_REF_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/ref-type-signature/ref-type-signature.h"

class RefTypeSignatureIRStrategy {
public:
    IRRefType* generate(RefTypeSignature* refTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRInstructionNode* generateTypeValue(IRRefType* irType, IRGenerator* irGenerator, IRContext* irContext);
};

#endif //JETLANG_REF_TYPE_SIGNATURE_IR_STRATEGY_H
