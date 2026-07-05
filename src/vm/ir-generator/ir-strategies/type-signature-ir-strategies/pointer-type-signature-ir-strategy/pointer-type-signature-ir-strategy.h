//
// Created by Johny Georges on 2024-11-21.
//

#ifndef JETLANG_POINTER_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_POINTER_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/pointer-type-signature/pointer-type-signature.h"

class PointerTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRPointerType> generate(std::shared_ptr<PointerTypeSignature> pointerTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRTypeValueInstructionNode* generateTypeValue(std::shared_ptr<IRPointerType> irType, IRGenerator* irGenerator);
};

#endif //JETLANG_POINTER_TYPE_SIGNATURE_IR_STRATEGY_H
