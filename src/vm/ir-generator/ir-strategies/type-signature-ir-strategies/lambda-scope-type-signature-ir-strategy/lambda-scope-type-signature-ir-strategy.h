//
// Created by Johny Georges on 2025-11-21.
//

#ifndef JETLANG_LAMBDA_SCOPE_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_LAMBDA_SCOPE_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"

class LambdaScopeTypeSignatureIRStrategy {
public:
    IRStructType* generate(LambdaScopeTypeSignature* lambdaScopeTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRTypeValueInstructionNode* generateTypeValue(IRCapturedVariableType* irType, IRGenerator* irGenerator, IRContext* irContext);
};

#endif //JETLANG_LAMBDA_SCOPE_TYPE_SIGNATURE_IR_STRATEGY_H
