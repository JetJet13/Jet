//
// Created by Johny Georges on 2024-06-25.
//

#include "tuple-expression-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

IRTupleExpressionNode* TupleExpressionIRStrategy::generate(ASTTupleExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {

    auto structValueTypes = std::vector<llvm::Type*>();
    auto structValues = std::vector<llvm::Constant*>();
    for (auto tupleItem : node->getTupleList()->getItems()) {
        auto irNode = irGenerator->generateFor(tupleItem->getItem(), scope);
        structValueTypes.push_back(irNode->getIRValue()->getType());
        structValues.push_back(irNode->getConstantIRValue());
    }

    auto structType = llvm::StructType::get(**context, structValueTypes);
    return new IRTupleExpressionNode(node, llvm::ConstantStruct::get(structType, structValues));
}