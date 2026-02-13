//
// Created by Johny Georges on 2024-12-30.
//

#include "new-class-instance-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRNewClassInstanceExpressionNode* NewClassInstanceExpressionIRStrategy::generate(ASTNewClassInstanceExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRFunctionArgumentNode*>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = node->getArguments()->getArguments()->at(i);
        arguments.push_back(
                irGenerator->generateFor(
                    argument,
                    i,
                    scope,
                    irContext,
                    new IROperation(IR_FUNCTION_ARGUMENT_OP),
                    node->getTypeSignature()->getConstructorTypeSignature()
                )
        );
    }

    auto irType = (IRNewClassInstanceType*)irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto allocation = this->generateClassInstanceAllocation(irType, irGenerator, irContext);
    auto pointerAllocation = this->generateClassInstancePointerAllocation(node, irType, irGenerator, irContext, irOperation);
    pointerAllocation->setParentAllocation(allocation);
    return new IRNewClassInstanceExpressionNode(
            node,
            node->getTypeSignature()->getConstructorId(),
            irType->getIRConstructorType(),
            arguments,
            irType,
            pointerAllocation,
            irGenerator->generateArcAllocation(irContext)
    );
}

IRInstructionNode* NewClassInstanceExpressionIRStrategy::generateClassInstanceAllocation(IRNewClassInstanceType* irNewClassInstanceType, IRGenerator* irGenerator, IRContext* irContext) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(1),
                irGenerator->generateInt64Constant(irNewClassInstanceType->getIRClassPropertiesType()->getStructIRType()->getSizeInBytes())
            },
            ""
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irNewClassInstanceType->getIRClassPropertiesType()->getStructIRType())
    );
}

IRInstructionNode* NewClassInstanceExpressionIRStrategy::generateClassInstancePointerAllocation(ASTNewClassInstanceExpressionNode* node, IRNewClassInstanceType* irClassInstanceType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    if (node->isReferenced() || irOperation->isCopyGlobal() || irOperation->isRefGlobalAssignment()) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction(),
                {
                    irGenerator->generateInt64Constant(1),
                    irGenerator->generateInt64Constant(irClassInstanceType->getIRClassPropertiesType()->getStructIRType()->getSizeInBytes())
                }
        );
        return IRInstructionNodeFactory::create(
                malloc,
                irGenerator->generateIrPointerType(irClassInstanceType->getIRClassPropertiesType())
        );
    }
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irClassInstanceType->getIRClassPropertiesType()));
}