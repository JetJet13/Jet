//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../ir-type/ir-type.h"
#include "../../../../utils/address-space-calculator/address-space-calculator.h"
#include "../../../../utils/data-alignment-calculator/data-alignment-calculator.h"


llvm::Value* ArrayExpressionIRStrategy::generate(ASTArrayExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto arrayType = this->generateArrayType(node, irGenerator, scope);
    auto irArrayType = new IRType(arrayType);
    return new llvm::AllocaInst(
            this->generateArrayType(node, irGenerator, scope),
            AddressSpaceCalculator::calculate(irArrayType),
            nullptr,
            DataAlignmentCalculator::calculate(irArrayType));
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