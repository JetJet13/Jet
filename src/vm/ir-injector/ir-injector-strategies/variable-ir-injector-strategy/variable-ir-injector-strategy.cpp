//
// Created by Johny Georges on 2024-08-15.
//

#include "variable-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void VariableIRInjectorStrategy::inject(IRVariableDeclarationNode* irVariableDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    InstructionIRInjectorHelper::inject(irVariableDeclaration->getIRValue(), irBlock, irVariableDeclaration->getVariableName());
    auto operation = this->determineOperationType(irVariableDeclaration);
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irVariableDeclaration->getIRExpression(),
                    operation, irModule, scope);

      InstructionIRInjectorHelper::injectStore(irExpressionValue, irVariableDeclaration->getValue(), irBlock, irVariableDeclaration->getAllocatedIRType());
//    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, irVariableDeclaration->getValue());
    if (irVariableDeclaration->getGlobalVariable()) {
        InstructionIRInjectorHelper::injectStore(irExpressionValue, irVariableDeclaration->getGlobalVariable().value()->getValue(), irBlock, irVariableDeclaration->getGlobalVariable().value()->getIRType());
        // irBlock->getBuilder()->get()->CreateStore(irExpressionValue, irVariableDeclaration->getGlobalVariable().value()->getValue());
    }
}

IROperationType VariableIRInjectorStrategy::determineOperationType(IRVariableDeclarationNode* irVariableDeclaration) {
    if (irVariableDeclaration->getGlobalVariable()) {
        return irVariableDeclaration->getIRExpression()->is(IR_REF_EXPRESSION_NODE) ? IR_REF_GLOBAL_ASSIGNMENT_OP : IR_COPY_GLOBAL_ASSIGNMENT_OP;
    }
    return irVariableDeclaration->getIRExpression()->is(IR_REF_EXPRESSION_NODE) ? IR_REF_ASSIGNMENT_OP : IR_COPY_ASSIGNMENT_OP;
}