//
// Created by Johny Georges on 2024-11-09.
//

#include "function-invocation-ir-injector-helper.h"
#include "../../../../../shared/utils/logger/logger.h"

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRFunctionInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        Logger::log("!!---!!");
        irExpression->getTypeSignature()->print();
        Logger::log("FunctionInvocationIRInjectorHelper", argument->toString());
        arguments.push_back(
                irInjectorMap->getInjector(argument->getTypeSignature())->inject(argument, builder, irInjectorMap, IR_FUNCTION_ARGUMENT_OP, irModule)
        );
    }
    return builder->get()->CreateCall(irExpression->getValue(), arguments);
}