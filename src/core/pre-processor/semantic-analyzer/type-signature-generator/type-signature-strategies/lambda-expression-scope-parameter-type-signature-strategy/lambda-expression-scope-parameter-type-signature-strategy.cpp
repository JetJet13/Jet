//
// Created by Johny Georges on 2024-11-11.
//

#include "lambda-expression-scope-parameter-type-signature-strategy.h"
#include "../../../../../../shared/utils/logger/logger.h"

ParameterListItemTypeSignature* LambdaExpressionScopeParameterTypeSignatureStrategy::create(TypeSignatureLookupTable* captureVariableTypeSignatureMap) {
    // todo - switch out StructTypeSignature with a new TypeSignature since the captured variables
    // can have unknown type signatures if the lambda is defined inside an aggregate type like array or struct.
    // e.g. const structWithLambda = { mars: () => 20, bar: 100 };
    // technically, structWithLambda is a captured variable of the mars lambda, but since the logic is setup
    // so that the structWithLambda type-signature is generated after all its fields are generated, the type-signature
    // of structWithLambda is unknown at the time of generating the lambda expression scope parameter type signature.
    auto scopeParameterTypeSignature = new StructTypeSignature();
    for (auto keyValue : captureVariableTypeSignatureMap->getLookupTable()) {
        Logger::log("scopeParameterTypeSignature->addKeyValuePair", keyValue.first, keyValue.second->toString());
        scopeParameterTypeSignature->addKeyValuePair(keyValue.first, new PointerTypeSignature());
    }
    return ParameterListItemTypeSignature::createScopeParameter(scopeParameterTypeSignature);
}