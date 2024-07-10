//
// Created by Johny Georges on 2024-07-10.
//

#ifndef JETLANG_LITERAL_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_LITERAL_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"

class LiteralTypeSignatureIRStrategy {
public:
    IRType* generate(LiteralTypeSignature* literalTypeSignature, std::unique_ptr<llvm::LLVMContext>* context);
};

#endif //JETLANG_LITERAL_TYPE_SIGNATURE_IR_STRATEGY_H
