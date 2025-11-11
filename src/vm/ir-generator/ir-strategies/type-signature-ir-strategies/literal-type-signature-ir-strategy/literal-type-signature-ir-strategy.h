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
    llvm::Value* generateInitialTypeValue(IRType* irType, IRTypeValueType* irTypeValueType, IRGenerator* irGenerator, IRContext* irContext);
public:
    IRType* generate(LiteralTypeSignature* literalTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRInstructionNode* generateTypeValue(IRType* irType, IRGenerator* irGenerator, IRContext* irContext);
};

#endif //JETLANG_LITERAL_TYPE_SIGNATURE_IR_STRATEGY_H
