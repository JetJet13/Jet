//
// Created by Johny Georges on 2024-06-25.
//

#include "tuple-expression-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

llvm::Value* TupleExpressionIRStrategy::generate(ASTTupleExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto structType = this->generateTupleType(node, context, irGenerator, scope);
    return new llvm::AllocaInst(
            structType,
            AddressSpaceGenerator::generate(structType),
            nullptr,
            DataAlignmentGenerator::generate(structType));
}

llvm::StructType* TupleExpressionIRStrategy::generateTupleType(ASTTupleExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {

    auto structValueTypes = std::vector<llvm::Type*>();
    for (auto tupleItem : node->getTupleList()->getItems()) {
        structValueTypes.push_back(irGenerator->generateFor(tupleItem->getItem(), scope)->getType());
    }

    return llvm::StructType::get(**context, structValueTypes);
}