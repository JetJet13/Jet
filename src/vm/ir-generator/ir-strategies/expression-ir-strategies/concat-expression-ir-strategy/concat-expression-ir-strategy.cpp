//
// Created by Johny Georges on 2025-06-09.
//

#include "concat-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRConcatExpressionNode* ConcatExpressionIRStrategy::generate(ASTConcatExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto leftExpressionIr = irGenerator->generateFor(node->getLeftNode(), scope, irContext, irOperation);
    auto rightExpressionIr = irGenerator->generateFor(node->getRightNode(), scope, irContext, irOperation);
    auto irType = (IRArrayPointerType*)irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto depth = irGenerator->generateIntConstant(irType->getDepth());
    auto sizeInBytes = irGenerator->generateIntConstant(irType->getElementIRType()->getSizeInBytes());
    auto concatCall = llvm::CallInst::Create(
            irContext->getIRModule()->getArrayConcatFunction()->getFunctionType(),
            irContext->getIRModule()->getArrayConcatFunction(),
            {
                    leftExpressionIr->getSourceAllocation().value()->getValue(),
                    rightExpressionIr->getSourceAllocation().value()->getValue(),
                    sizeInBytes,
                    depth
            }
    );
    return new IRConcatExpressionNode(
            node,
            IRInstructionNodeFactory::create(concatCall, irGenerator->generateIrPointerType(irType)),
            leftExpressionIr,
            rightExpressionIr,
            irType
    );
}