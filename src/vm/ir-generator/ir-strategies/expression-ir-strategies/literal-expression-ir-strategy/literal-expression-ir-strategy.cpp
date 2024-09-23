//
// Created by Johny Georges on 2024-07-02.
//

#include "literal-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-string-literal-expression-node.h"

IRExpressionNode* LiteralExpressionIRStrategy::generate(ASTLiteralExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto irLiteralNode = irGenerator->generateFor(node->getLiteralNode(), scope, irModule);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    if (irLiteralNode->is(IR_STRING_LITERAL_NODE)) {
        auto sourceAllocation = IRInstructionNodeFactory::create(
                irGenerator->generateIrPointerType(irLiteralNode->getIRType()));
        auto arrayPointerSourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), sourceAllocation);
        return new IRStringLiteralExpressionNode(node, (IRStringLiteralNode*)irLiteralNode, (IRArrayPointerType*)irType,  sourceAllocation, arrayPointerSourceAllocation);
    }
    return new IRLiteralExpressionNode(node, irLiteralNode, irType);
}