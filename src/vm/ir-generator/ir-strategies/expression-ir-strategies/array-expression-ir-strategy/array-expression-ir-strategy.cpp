//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../ir-type/ir-type.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"


IRArrayExpressionNode* ArrayExpressionIRStrategy::generate(ASTArrayExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto arrayType = this->generateArrayType(node, irGenerator, scope);
    auto elementValues = std::vector<llvm::Constant*>();
    for (auto element : *node->getElements()) {
        elementValues.push_back(irGenerator->generateFor(element, scope)->getConstantIRValue());
    }
    return new IRArrayExpressionNode(node, llvm::ConstantArray::get(arrayType, elementValues));
}

llvm::ArrayType* ArrayExpressionIRStrategy::generateArrayType(ASTArrayExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope) {
    if (node->size() == 0) {
        auto arrayElementType = irGenerator->generateTypeFor(node->getTypeSignature()->getElementType());
        return llvm::ArrayType::get(arrayElementType, 0);
    }

    auto elementValues = std::vector<llvm::Value*>();
    for (auto element : *node->getElements()) {
        elementValues.push_back(irGenerator->generateFor(element, scope)->getIRValue());
    }

    return llvm::ArrayType::get(irGenerator->determineBestFitType(elementValues), node->size());
}