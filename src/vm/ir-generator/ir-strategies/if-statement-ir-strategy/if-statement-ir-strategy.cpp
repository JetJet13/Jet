//
// Created by Johny Georges on 2025-01-08.
//

#include "if-statement-ir-strategy.h"
#include "../../../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-else-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-statement-node.h"

IRStatementNode* IfStatementIRStrategy::generate(ASTIfStatementNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto ifConditionIRExpression = irGenerator->generateFor(node->getIfBlock()->getCondition()->getCondition(), scope, irModule, IR_OPERAND_OP);

    auto endBlock = irGenerator->generateIfEndBlock();

    auto thenBlock = irGenerator->generateIfThenBlock();
    this->setupBlock(thenBlock, node->getIfBlock()->getBlock(), context, irGenerator, scope, irModule, endBlock);

    auto elseBlock = irGenerator->generateIfElseBlock();
    if (node->getElseBlock()) {
        this->setupBlock(elseBlock, node->getElseBlock().value()->getBlock(), context, irGenerator, scope, irModule, endBlock);
    }

    auto ifNode = new IRIfElseNode(ifConditionIRExpression, thenBlock, elseBlock, endBlock);
    auto currentIfNode = ifNode;
    for (auto elseIf : *node->getElseIfBlocks()) {
        auto elseIfConditionIRExpression = irGenerator->generateFor(elseIf->getCondition()->getCondition(), scope, irModule, IR_OPERAND_OP);
        auto elseIfNode = new IRIfElseNode(
            elseIfConditionIRExpression,
            this->setupBlock(irGenerator->generateIfThenBlock(), elseIf->getBlock(), context, irGenerator, scope, irModule, endBlock),
            irGenerator->generateIfElseBlock(),
            endBlock
        );
        currentIfNode->setNext(elseIfNode);
        currentIfNode = elseIfNode;
    }
    return new IRIfStatementNode(node, ifNode);
}

IRBlockNode* IfStatementIRStrategy::setupBlock(IRBlockNode* irBlockNode, ASTControlFlowBlockNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IRBlockNode* irEndBlockNode) {
    auto blockScope = new IRLookupTable(scope);
    for (auto statement : *node->getContents()) {
        irBlockNode->insert(irGenerator->generateFor(statement, blockScope, irModule));
    }
    return irBlockNode;
}