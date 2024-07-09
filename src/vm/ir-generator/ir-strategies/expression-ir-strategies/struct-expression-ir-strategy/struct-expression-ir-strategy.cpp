//
// Created by Johny Georges on 2024-06-21.
//

#include "struct-expression-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

IRStructExpressionNode* StructExpressionIRStrategy::generate(ASTStructExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto structValueTypes = std::vector<llvm::Type*>();
    auto structValues = std::vector<IRExpressionNode*>();
    for (auto keyValuePair : node->getKeyValuePairs()) {
        auto irNode = irGenerator->generateFor(keyValuePair->getValue(), scope, irModule);
        structValues.push_back(irNode);
        structValueTypes.push_back(irNode->getIRType());
    }

    auto structType = llvm::StructType::get(**context, structValueTypes);
    auto allocation = new llvm::AllocaInst(
            structType,
            AddressSpaceGenerator::generate(structType),
            nullptr,
            DataAlignmentGenerator::generate(structType));
    auto irStructPointer = llvm::GetElementPtrInst::Create(structType, allocation, irGenerator->generateZeroConstant());

    auto constantStruct = llvm::ConstantStruct::get(structType);

    auto irStruct = new IRStructExpressionNode(node, allocation, structValues, irStructPointer);

    return irStruct;
}