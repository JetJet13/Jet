//
// Created by Johny Georges on 2024-12-30.
//

#include "new-class-instance-expression-ir-strategy.h"

IRNewClassInstanceExpressionNode* NewClassInstanceExpressionIRStrategy::generate(ASTNewClassInstanceExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irModule, IR_FUNCTION_ARGUMENT_OP));
    }

    auto irClassType = irGenerator->generateTypeFor(node->getTypeSignature()->getClassTypeSignature());
    auto irConstructorType = irClassType->getIRTypeForConstructor(node->getTypeSignature()->getConstructorId());

    auto function = irModule->getModule()->getFunction(node->getTypeSignature()->getConstructorId());
    return new IRNewClassInstanceExpressionNode(node, function, irConstructorType.value(), arguments, irClassType);
}