//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H
#define JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../ir-generator.h"
#include "../../../../../../core/type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../../../../../../core/type-signature/invocable-type-signature/lambda-type-signature/function-lambda-type-signature/function-lambda-type-signature.h"
#include "../../../../../../core/type-signature/invocable-type-signature/lambda-type-signature/procedure-lambda-type-signature/procedure-lambda-type-signature.h"
#include "../../../../../ir-type/ir-function-type.h"

class LambdaTypeSignatureIRStrategy {
private:
    std::vector<llvm::Type*> generateParameterTypes(std::vector<TypeSignature*>* parameterTypeSignatures, IRGenerator* irGenerator);
public:
    IRFunctionType* generate(FunctionLambdaTypeSignature* functionLambdaTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
    IRFunctionType* generate(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
    IRFunctionType* generate(ProcedureLambdaTypeSignature* procedureLambdaTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator);
};

#endif //JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H
