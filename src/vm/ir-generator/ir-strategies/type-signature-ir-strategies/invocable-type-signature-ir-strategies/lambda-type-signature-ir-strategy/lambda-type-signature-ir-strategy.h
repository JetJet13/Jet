//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-generator.h"
#include "../../../../../../core/type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../../../../../ir-type/ir-lambda-type.h"
#include "../../../../../ir-type/ir-function-parameter-type.h"
#include "../../../../../../core/type-signature/invocable-type-signature/lambda-type-signature/lambda-type-signature.h"

class LambdaTypeSignatureIRStrategy {
private:
    std::vector<llvm::Type*> generateParameterTypes(std::vector<TypeSignature*>* parameterTypeSignatures, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, std::optional<IRType*> lambdaScopeParameter = {});
public:
    IRFunctionParameterType* generate(LambdaTypeSignature* lambdaTypeSignature,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRLambdaType* generate(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H
