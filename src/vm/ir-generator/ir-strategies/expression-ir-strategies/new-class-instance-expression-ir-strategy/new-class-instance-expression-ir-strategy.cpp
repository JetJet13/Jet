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

    auto function = irContext->getModule()->getFunction(node->getTypeSignature()->getConstructorId());
    auto irType = (IRClassInstanceType*)irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto allocation = this->generateClassInstanceAllocation(irType, irGenerator, irContext);
    auto pointerAllocation = this->generateClassInstancePointerAllocation(node, irType, irGenerator, irContext, irOperation);
    pointerAllocation->setParentAllocation(allocation);
    return new IRNewClassInstanceExpressionNode(
            node,
            function,
            irType->getIRConstructorType(),
            arguments,
            irType,
            pointerAllocation
    );
}

IRInstructionNode* NewClassInstanceExpressionIRStrategy::generateClassInstanceAllocation(IRClassInstanceType* irClassInstanceType, IRGenerator* irGenerator, IRContext* irContext) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { irGenerator->generateInt64Constant(irClassInstanceType->getIRClassPropertiesType()->getStructIRType()->getSizeInBytes()) },
            ""
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irClassInstanceType->getIRClassPropertiesType()->getStructIRType())
    );
}

IRInstructionNode* NewClassInstanceExpressionIRStrategy::generateClassInstancePointerAllocation(ASTNewClassInstanceExpressionNode* node, IRClassInstanceType* irClassInstanceType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    if (node->isReferenced() || irOperation->isCopyGlobal() || irOperation->isRefGlobalAssignment()) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateInt64Constant(irClassInstanceType->getIRClassPropertiesType()->getStructIRType()->getSizeInBytes()) }
        );
        return IRInstructionNodeFactory::create(
                malloc,
                irGenerator->generateIrPointerType(irClassInstanceType->getIRClassPropertiesType())
        );
    }
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irClassInstanceType->getIRClassPropertiesType()));
}