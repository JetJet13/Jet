//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"

IRArrayExpressionNode* ArrayExpressionIRStrategy::generate(ASTArrayExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto elementValues = std::vector<IRExpressionNode*>();
    for (auto element : *node->getElements()) {
        elementValues.push_back(irGenerator->generateFor(element, scope, irModule));
    }
    auto arrayElementIrType = irGenerator->generateTypeFor(node->getTypeSignature()->getElementType());
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto arrayType = llvm::ArrayType::get(arrayElementIrType->getType(), elementValues.size());
    irType->setSourceType(new IRType(arrayType));
    auto arrayAllocation = new IRInstructionNode(
        new llvm::AllocaInst(
            arrayType,
            AddressSpaceGenerator::generate(arrayElementIrType),
            nullptr,
            DataAlignmentGenerator::generate(arrayElementIrType)),
            irType
    );
    return new IRArrayExpressionNode(node, arrayAllocation, elementValues, irType);
}