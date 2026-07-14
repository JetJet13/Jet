//
// Created by Johny Georges on 2026-07-13.
//

#ifndef JETLANG_SHARED_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_SHARED_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/type-signature/shared-type-signature/shared-type-signature.h"

class SharedTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRSharedPtrType> generate(std::shared_ptr<SharedTypeSignature> sharedTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IRTypeValueInstructionNode> generateTypeValue(std::shared_ptr<IRSharedPtrType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_SHARED_TYPE_SIGNATURE_IR_STRATEGY_H
