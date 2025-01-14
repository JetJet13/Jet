//
// Created by Johny Georges on 2024-06-25.
//

#include "tuple-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRTupleExpressionNode* TupleExpressionIRStrategy::generate(ASTTupleExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto tupleValues = std::vector<IRExpressionNode*>();
    for (auto tupleItem : node->getTupleList()->getItems()) {
        auto irNode = irGenerator->generateFor(tupleItem->getItem(), scope, irContext, irOperationType);
        tupleValues.push_back(irNode);
    }

    auto tupleAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));

    return new IRTupleExpressionNode(
            node,
            tupleAllocation,
            irType,
            tupleValues
    );
}