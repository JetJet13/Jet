//
// Created by Johny Georges on 2024-10-09.
//

#include "tuple-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRTupleAccessExpressionNode* TupleAccessExpressionIRStrategy::generate(ASTTupleAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irModule, irOperationType);
    auto sourceType = (IRStructType*)sourceValue->getIRType()->getSourceType();
    auto targetIndex = node->getIndex()->getIndexValue();
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
    if (irType->isArrayPointerType()) {
        sourceAllocation->setParentAllocation(
                IRInstructionNodeFactory::create(
                        irGenerator->generateIrPointerType(sourceType->getIRTypeByIndex(targetIndex)))
        );
    }
    return new IRTupleAccessExpressionNode(node, sourceValue, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
}