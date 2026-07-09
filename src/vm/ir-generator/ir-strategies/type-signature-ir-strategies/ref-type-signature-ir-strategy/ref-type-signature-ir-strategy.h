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
    std::shared_ptr<IRRefType> generate(std::shared_ptr<RefTypeSignature> refTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IRTypeValueInstructionNode> generateTypeValue(std::shared_ptr<IRRefType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_REF_TYPE_SIGNATURE_IR_STRATEGY_H
