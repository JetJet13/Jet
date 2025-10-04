//
// Created by Johny Georges on 2024-12-30.
//

#include "new-class-instance-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRNewClassInstanceExpressionNode* NewClassInstanceExpressionIRStrategy::generate(ASTNewClassInstanceExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, new IROperation(IR_FUNCTION_ARGUMENT_OP)));
    }
    auto irClassType = (IRClassType*)scope->findType(node->getClassName()->getId()).value();
    auto irConstructorType = irClassType->getIRTypeForConstructor(node->getTypeSignature()->getConstructorId());

    auto function = irContext->getModule()->getFunction(node->getTypeSignature()->getConstructorId());
    return new IRNewClassInstanceExpressionNode(
            node,
            function,
            irConstructorType.value(),
            arguments,
            irClassType,
            this->generateClassInstanceAllocation(node, irClassType, irGenerator, irContext, irOperation)
    );
}

IRInstructionNode* NewClassInstanceExpressionIRStrategy::generateClassInstanceAllocation(ASTNewClassInstanceExpressionNode* node, IRClassType* irClassType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    if (node->isReferenced() || irOperation->isCopyGlobal() || irOperation->isRefGlobalAssignment()) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateInt64Constant(irClassType->getClassProperties()->getSizeInBytes()) },
                ""
        );
        return IRInstructionNodeFactory::create(
                malloc,
                irGenerator->generateIrPointerType(irClassType)
        );
    }
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irClassType));
}