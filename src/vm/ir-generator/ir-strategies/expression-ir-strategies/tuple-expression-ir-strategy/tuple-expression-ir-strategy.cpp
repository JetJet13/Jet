//
// Created by Johny Georges on 2024-06-25.
//

#include "tuple-expression-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

IRTupleExpressionNode* TupleExpressionIRStrategy::generate(ASTTupleExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {

    auto structValueTypes = std::vector<llvm::Type*>();
    auto structValues = std::vector<IRExpressionNode*>();
    for (auto tupleItem : node->getTupleList()->getItems()) {
        auto irNode = irGenerator->generateFor(tupleItem->getItem(), scope, irModule);
        structValueTypes.push_back(irNode->getIRType());
        structValues.push_back(irNode);
    }
    auto tupleType = llvm::StructType::get(**context, structValueTypes);
    auto allocation = new llvm::AllocaInst(
            tupleType,
            AddressSpaceGenerator::generate(tupleType),
            nullptr,
            DataAlignmentGenerator::generate(tupleType));
    auto irTuplePointer = llvm::GetElementPtrInst::Create(tupleType, allocation, irGenerator->generateZeroConstant());
    return new IRTupleExpressionNode(node, allocation, structValues, irTuplePointer);
}