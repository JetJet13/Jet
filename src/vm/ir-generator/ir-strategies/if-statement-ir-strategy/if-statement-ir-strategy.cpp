//
// Created by Johny Georges on 2025-01-08.
//

#include "if-statement-ir-strategy.h"

IRStatementNode* IfStatementIRStrategy::generate(ASTIfStatementNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
        auto ifConditionIRExpression = irGenerator->generateFor(node->getIfBlock()->getCondition()->getCondition(), scope, irModule, IR_OPERAND_OP);
        auto ifConditionBlock = irGenerator->generateIfBlock();
        auto thenBlock = irGenerator->generateIfThenBlock();
        auto elseBlock = irGenerator->generateIfElseBlock();
}