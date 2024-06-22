//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../ir-type/ir-type.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"


llvm::Value* ArrayExpressionIRStrategy::generate(ASTArrayExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto arrayType = this->generateArrayType(node, irGenerator, scope);
    return new llvm::AllocaInst(
            this->generateArrayType(node, irGenerator, scope),
            AddressSpaceGenerator::generate(arrayType),
            nullptr,
            DataAlignmentGenerator::generate(arrayType));
}

llvm::Type* ArrayExpressionIRStrategy::generateArrayType(ASTArrayExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope) {
    if (node->size() == 0) {
        return irGenerator->generateTypeFor(node->getTypeSignature());
    }

    auto elementValues = std::vector<llvm::Value*>();
    for (auto element : *node->getElements()) {
        elementValues.push_back(irGenerator->generateFor(element, scope));
    }

    return llvm::ArrayType::get(irGenerator->determineBestFitType(elementValues), node->size());
}