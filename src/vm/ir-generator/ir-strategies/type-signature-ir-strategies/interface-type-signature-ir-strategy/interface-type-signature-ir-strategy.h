//
// Created by Johny Georges on 2025-07-04.
//

#ifndef JETLANG_INTERFACE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_INTERFACE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/interface-type-signature/interface-type-signature.h"

class InterfaceTypeSignatureIRStrategy {
public:
    IRStructType* generate(InterfaceTypeSignature* interfaceTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRInstructionNode* generateTypeValue(IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext);
};

#endif //JETLANG_INTERFACE_TYPE_SIGNATURE_IR_STRATEGY_H
