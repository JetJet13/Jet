//
// Created by Johny Georges on 2024-06-25.
//

#include "variable-declaration-ir-strategy.h"
#include "../../../utils/address-space-generator/address-space-generator.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

IRVariableDeclarationNode* VariableDeclarationIRStrategy::generate(ASTVariableDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto irExpression = irGenerator->generateFor(node->getInitializerNode(), scope);
    scope->insert(node->getId(), irExpression);
    return new IRVariableDeclarationNode(node, new llvm::AllocaInst(
            irExpression->getIRValue()->getType(),
            AddressSpaceGenerator::generate(irExpression->getIRValue()->getType()),
            nullptr,
            DataAlignmentGenerator::generate(irExpression->getIRValue()->getType()),
            node->getId()
    ), irExpression);
}