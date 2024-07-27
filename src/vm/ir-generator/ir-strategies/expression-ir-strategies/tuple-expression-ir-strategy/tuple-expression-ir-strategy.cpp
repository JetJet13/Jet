//
// Created by Johny Georges on 2024-06-25.
//

#include "tuple-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRTupleExpressionNode* TupleExpressionIRStrategy::generate(ASTTupleExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto tupleValues = std::vector<IRExpressionNode*>();
    for (auto tupleItem : node->getTupleList()->getItems()) {
        auto irNode = irGenerator->generateFor(tupleItem->getItem(), scope, irModule);
        tupleValues.push_back(irNode);
    }

    auto tupleAllocation = IRInstructionNodeFactory::create(irType);

    return new IRTupleExpressionNode(
            node,
            tupleAllocation,
            irType,
            tupleValues
    );
}