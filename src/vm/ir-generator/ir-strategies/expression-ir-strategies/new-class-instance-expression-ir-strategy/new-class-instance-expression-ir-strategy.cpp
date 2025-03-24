//
// Created by Johny Georges on 2024-12-30.
//

#include "new-class-instance-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRNewClassInstanceExpressionNode* NewClassInstanceExpressionIRStrategy::generate(ASTNewClassInstanceExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, IR_FUNCTION_ARGUMENT_OP));
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
            this->generateClassInstanceAllocation(node, irClassType, irGenerator, irContext, irOperationType)
    );
}

IRInstructionNode* NewClassInstanceExpressionIRStrategy::generateClassInstanceAllocation(ASTNewClassInstanceExpressionNode* node, IRClassType* irClassType, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    auto irType = irClassType->getClassProperties();
    if (node->isReferenced() || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP || irOperationType == IR_REF_GLOBAL_ASSIGNMENT_OP) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateIntConstant(irType->getSizeInBytes()) },
                ""
        );
        return IRInstructionNodeFactory::create(
                new llvm::BitCastInst(malloc, irType->getType()),
                irGenerator->generateIrPointerType(irType),
                { malloc }
        );
    }
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}