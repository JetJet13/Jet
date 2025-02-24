//
// Created by Johny Georges on 2024-07-02.
//

#include "literal-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-string-literal-expression-node.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

IRExpressionNode* LiteralExpressionIRStrategy::generate(ASTLiteralExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irLiteralNode = irGenerator->generateFor(node->getLiteralNode(), scope, irContext);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    if (irLiteralNode->is(IR_STRING_LITERAL_NODE)) {
        auto stringLiteral = (IRStringLiteralNode*)irLiteralNode;
        auto arrayAllocation = new IRInstructionNode(
                    new llvm::AllocaInst(
                        irLiteralNode->getIRType()->getType(),
                        AddressSpaceGenerator::generate(stringLiteral->getIRType()->getElementType()),
                        nullptr,
                        DataAlignmentGenerator::generate(stringLiteral->getIRType()->getElementType())
                    ),
                    irGenerator->generateIrPointerType(irLiteralNode->getIRType())
               );
        auto arrayPointerAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), arrayAllocation);
        return new IRStringLiteralExpressionNode(node, (IRStringLiteralNode*)irLiteralNode, (IRArrayPointerType*)irType, arrayAllocation, arrayPointerAllocation);
    }
    return new IRLiteralExpressionNode(node, irLiteralNode, irType);
}