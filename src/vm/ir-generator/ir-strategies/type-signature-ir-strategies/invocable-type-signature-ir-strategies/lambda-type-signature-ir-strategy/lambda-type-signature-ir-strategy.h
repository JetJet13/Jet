// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    std::shared_ptr<IRInvocableParameterListType> generateParameterTypes(std::vector<std::shared_ptr<TypeSignature>>* parameterTypeSignatures, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::optional<std::shared_ptr<IRType>> lambdaScopeParameter = {});
    std::shared_ptr<IRTypeValueInstructionNode> generateTypeValue(std::shared_ptr<IRInvocableType> irInvocableType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext);
public:
    std::shared_ptr<IRInvocableType> generate(std::shared_ptr<LambdaTypeSignature> lambdaTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
    std::shared_ptr<IRLambdaType> generate(std::shared_ptr<LambdaExpressionTypeSignature> lambdaExpressionTypeSignature,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_LAMBDA_TYPE_SIGNATURE_IR_STRATEGY_H
