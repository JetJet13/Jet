//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-generator.h"
#include "../../../../../../core/type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../../../../../ir-type/ir-lambda-type.h"
#include "../../../../../ir-type/ir-invocable-type.h"
#include "../../../../../../core/type-signature/invocable-type-signature/lambda-type-signature/lambda-type-signature.h"
#include "../../../../../ir-type/ir-invocable-parameter-list-type.h"

class LambdaTypeSignatureIRStrategy {
private:
    IRInvocableParameterListType* generateParameterTypes(std::vector<TypeSignature*>* parameterTypeSignatures, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, std::optional<IRType*> lambdaScopeParameter = {});
    IRTypeValueInstructionNode* generateTypeValue(IRInvocableType* irInvocableType, IRGenerator* irGenerator, IRContext* irContext);
public:
    IRInvocableType* generate(LambdaTypeSignature* lambdaTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
    IRLambdaType* generate(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H
