//
// Created by Johny Georges on 2026-01-10.
//

#ifndef JETLANG_VOID_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_VOID_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/type-signature/void-type-signature/void-type-signature.h"
#include "../../../ir-generator.h"

class VoidTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRType> generate(std::shared_ptr<IRGenerator> irGenerator);
    std::shared_ptr<IRTypeValueInstructionNode> generateTypeValue(std::shared_ptr<IRType> irType, std::shared_ptr<IRGenerator> irGenerator);
};

#endif //JETLANG_VOID_TYPE_SIGNATURE_IR_STRATEGY_H
