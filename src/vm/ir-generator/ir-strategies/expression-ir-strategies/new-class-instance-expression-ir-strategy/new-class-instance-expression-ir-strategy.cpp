//
// Created by Johny Georges on 2024-12-30.
//

#include "new-class-instance-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

std::shared_ptr<IRNewClassInstanceExpressionNode> NewClassInstanceExpressionIRStrategy::generate(std::shared_ptr<ASTNewClassInstanceExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, std::shared_ptr<IROperation> irOperation) {
    auto arguments = std::vector<std::shared_ptr<IRFunctionArgumentNode>>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = node->getArguments()->getArguments()->at(i);
        arguments.push_back(
                irGenerator->generateFor(
                    argument,
                    i,
                    scope,
                    irContext,
                    std::make_shared<IROperation>(IR_FUNCTION_ARGUMENT_OP),
                    node->getClassInstanceTypeSignature()->getConstructorTypeSignature()
                )
        );
    }

    auto irType = std::dynamic_pointer_cast<IRNewClassInstanceType>(irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext));
    auto allocation = this->generateClassInstanceAllocation(irType, irGenerator, irContext);
    auto pointerAllocation = this->generateClassInstancePointerAllocation(node, irType, irGenerator, irContext, irOperation);
    pointerAllocation->setParentAllocation(allocation);
    return std::make_shared<IRNewClassInstanceExpressionNode>(
            node,
            node->getClassInstanceTypeSignature()->getConstructorId(),
            irType->getIRConstructorType(),
            arguments,
            irType,
            pointerAllocation,
            irGenerator->generateArcAllocation(irContext)
    );
}

std::shared_ptr<IRInstructionNode> NewClassInstanceExpressionIRStrategy::generateClassInstanceAllocation(std::shared_ptr<IRNewClassInstanceType> irNewClassInstanceType, IRGenerator* irGenerator, IRContext* irContext) {
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

std::shared_ptr<IRInstructionNode> NewClassInstanceExpressionIRStrategy::generateClassInstancePointerAllocation(std::shared_ptr<ASTNewClassInstanceExpressionNode> node, std::shared_ptr<IRNewClassInstanceType> irClassInstanceType, IRGenerator* irGenerator, IRContext* irContext, std::shared_ptr<IROperation> irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irClassInstanceType->getIRClassPropertiesType()));
}