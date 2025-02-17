//
// Created by Johny Georges on 2024-06-17.
//

#include "array-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../ir-type/ir-array-type.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRArrayExpressionNode* ArrayExpressionIRStrategy::generate(ASTArrayExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto elementValues = std::vector<IRExpressionNode*>();
    auto elementValueSourceAllocations = std::vector<IRInstructionNode*>();
    for (auto element : *node->getElements()) {
        auto elementIrExpression = irGenerator->generateFor(element, scope, irContext, irOperationType);
        elementValues.push_back(elementIrExpression);
        if (elementIrExpression->getSourceAllocation()) {
            elementValueSourceAllocations.push_back(elementIrExpression->getSourceAllocation().value());
        }
    }
    auto arrayElementIrType = irGenerator->generateTypeFor(node->getTypeSignature()->getElementType(), scope, irContext);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto arrayType = new IRArrayType(llvm::ArrayType::get(arrayElementIrType->getType(), elementValues.size()), arrayElementIrType);
    auto arrayAllocation = node->isGlobal()
            ? new IRInstructionNode(
                new llvm::GlobalVariable(
                    *irContext->getModule(),
                    arrayType->getType(),
                    true,
                    llvm::GlobalValue::InternalLinkage,
                    nullptr
                ),
                irGenerator->generateIrPointerType(arrayType),
                elementValueSourceAllocations
            )
            : new IRInstructionNode(
                new llvm::AllocaInst(
                    arrayType->getType(),
                    AddressSpaceGenerator::generate(arrayElementIrType),
                    nullptr,
                    DataAlignmentGenerator::generate(arrayElementIrType)
                ),
                irGenerator->generateIrPointerType(arrayType),
                elementValueSourceAllocations
        );
    auto arrayPointerAllocation = node->isGlobal()
            ? new IRInstructionNode(
                new llvm::GlobalVariable(
                        *irContext->getModule(),
                        irType->getType(),
                        true,
                        llvm::GlobalValue::InternalLinkage,
                        nullptr
                ),
                irGenerator->generateIrPointerType(irType),
                arrayAllocation
            )
            : IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), arrayAllocation);
    return new IRArrayExpressionNode(node, arrayAllocation, arrayPointerAllocation, elementValues, irType);
}