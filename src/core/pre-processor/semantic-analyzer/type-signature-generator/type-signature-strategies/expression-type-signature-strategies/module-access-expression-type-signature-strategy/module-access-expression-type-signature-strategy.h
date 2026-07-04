//
// Created by Johny Georges on 2024-11-07.
//

#ifndef JETLANG_MODULE_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_MODULE_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-module-access-expression-node.h"

class ModuleAccessExpressionTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_MODULE_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
