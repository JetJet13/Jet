//
// Created by Johny Georges on 2025-11-21.
//

#ifndef JETLANG_LAMBDA_SCOPE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_LAMBDA_SCOPE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"

class LambdaScopeTypeSignatureIRStrategy {
public:
    std::shared_ptr<IRStructType> generate(std::shared_ptr<LambdaScopeTypeSignature> lambdaScopeTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
    std::shared_ptr<IRTypeValueInstructionNode> generateTypeValue(std::shared_ptr<IRCapturedVariableType> irType, IRGenerator* irGenerator, IRContext* irContext);
};

#endif //JETLANG_LAMBDA_SCOPE_TYPE_SIGNATURE_IR_STRATEGY_H
