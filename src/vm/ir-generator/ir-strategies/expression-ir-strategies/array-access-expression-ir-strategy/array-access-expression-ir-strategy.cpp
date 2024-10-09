//
// Created by Johny Georges on 2024-06-21.
//

#include "array-access-expression-ir-strategy.h"
#include "../../../ir-util-functions/array-access-ir-function/array-access-ir-function.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRArrayAccessExpressionNode* ArrayAccessExpressionIRStrategy::ArrayAccessExpressionIRStrategy::generate(ASTArrayAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto sourceValue = irGenerator->generateFor(node->getSource(), scope, irModule, IR_OPERAND_OP);
    auto indexValue = irGenerator->generateFor(node->getIndex()->getIndex(), scope, irModule, IR_OPERAND_OP);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
    return new IRArrayAccessExpressionNode(node, sourceValue, indexValue, irType, sourceAllocation);
}