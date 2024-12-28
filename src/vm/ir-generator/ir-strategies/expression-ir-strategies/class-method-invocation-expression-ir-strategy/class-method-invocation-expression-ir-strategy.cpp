//
// Created by Johny Georges on 2024-12-27.
//

#include "class-method-invocation-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassMethodInvocationExpressionNode* ClassMethodInvocationExpressionIRStrategy::generate(ASTClassMethodInvocationExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        argument->print();
        arguments.push_back(irGenerator->generateFor(argument, scope, irModule, IR_FUNCTION_ARGUMENT_OP));
    }

    auto irFunctionType = irGenerator->generateTypeFor(node->getName()->getTypeSignature());
    auto irReturnType = irGenerator->generateTypeFor(node->getName()->getTypeSignature()->getReturnType());
    auto function = irModule->getModule()->getFunction(node->getName()->getId());
    return new IRClassMethodInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, scope->getClassScope().value());
}