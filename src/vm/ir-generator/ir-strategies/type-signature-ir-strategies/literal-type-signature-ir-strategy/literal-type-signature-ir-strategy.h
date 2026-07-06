//
// Created by Johny Georges on 2024-07-10.
//

#ifndef JETLANG_LITERAL_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_LITERAL_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-type/ir-pointer-type.h"

class LiteralTypeSignatureIRStrategy {
private:
    llvm::Value* generateInitialTypeValue(std::shared_ptr<IRType> irType, std::shared_ptr<IRTypeValueType> irTypeValueType, IRGenerator* irGenerator, IRContext* irContext);
public:
    std::shared_ptr<IRType> generate(std::shared_ptr<LiteralTypeSignature> literalTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    std::shared_ptr<IRTypeValueInstructionNode> generateTypeValue(std::shared_ptr<IRType> irType, IRGenerator* irGenerator, IRContext* irContext);
};

#endif //JETLANG_LITERAL_TYPE_SIGNATURE_IR_STRATEGY_H
