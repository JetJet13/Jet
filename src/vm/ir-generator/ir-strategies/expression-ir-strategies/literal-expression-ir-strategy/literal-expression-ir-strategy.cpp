//
// Created by Johny Georges on 2024-07-02.
//

#include "literal-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-string-literal-expression-node.h"

IRExpressionNode* LiteralExpressionIRStrategy::generate(ASTLiteralExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto irLiteralNode = irGenerator->generateFor(node->getLiteralNode(), scope, irModule);
    auto irType = irGenerator->generateTypeFor(node->getLiteralNode()->getTypeSignature());
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generatePointerType(irType));
    if (irLiteralNode->is(IR_STRING_LITERAL_NODE)) {
        return new IRStringLiteralExpressionNode(node, (IRStringLiteralNode*)irLiteralNode, (IRPointerType*)irType, sourceAllocation);
    }
    return new IRLiteralExpressionNode(node, irLiteralNode, irType, sourceAllocation);
}