//
// Created by Johny Georges on 2025-01-01.
//

#include "new-class-instance-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../../shared/utils/logger/logger.h"

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRExpressionNode *irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE)) {
        return this->inject((IRNewClassInstanceExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule, scope);
    }
    throw std::logic_error("NewClassInstanceIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* NewClassInstanceIRInjectorStrategy::inject(IRNewClassInstanceExpressionNode* irNewClassInstanceExpressionNode, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode* irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irNewClassInstanceExpressionNode->getIRArguments()) {
        arguments.push_back(irInjectorMap->getInjector(argument->getTypeSignature())->inject(argument, builder, irInjectorMap, IR_FUNCTION_ARGUMENT_OP, irModule, scope));
    }
    auto classInstanceAllocation = builder->get()->CreateAlloca(irNewClassInstanceExpressionNode->getIRType()->getClassProperties()->getType());
    arguments.push_back(classInstanceAllocation);

    builder->get()->CreateCall(
            irNewClassInstanceExpressionNode->getConstructorIRType()->getType(),
            irNewClassInstanceExpressionNode->getConstructorFunction(),
            arguments
    );

    return builder->get()->CreateLoad(classInstanceAllocation->getAllocatedType(), classInstanceAllocation);
}