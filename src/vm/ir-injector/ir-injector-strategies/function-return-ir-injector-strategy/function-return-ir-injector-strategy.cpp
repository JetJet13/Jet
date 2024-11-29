//
// Created by Johny Georges on 2024-08-15.
//

#include "function-return-ir-injector-strategy.h"
#include "../../ir-injector-map.h"

void FunctionReturnIRInjectorStrategy::inject(IRFunctionReturnExpressionNode* irFunctionReturnExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule, IRLookupTable* scope) {
    auto returnValue = irInjectorMap->getInjector(irFunctionReturnExpression->getReturnExpression()->getTypeSignature())->inject(irFunctionReturnExpression->getReturnExpression(), builder, irInjectorMap, IR_OPERAND_OP, irModule, scope);
    builder->get()->CreateRet(returnValue);
}