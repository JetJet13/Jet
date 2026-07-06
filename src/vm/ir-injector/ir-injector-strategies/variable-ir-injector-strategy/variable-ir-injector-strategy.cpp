//
// Created by Johny Georges on 2024-08-15.
//

#include "variable-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"

void VariableIRInjectorStrategy::inject(std::shared_ptr<IRVariableDeclarationNode> irVariableDeclaration, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    InstructionIRInjectorHelper::inject(irVariableDeclaration->getIRValue(), irBlock, irVariableDeclaration->getVariableName());
    auto operation = this->determineOperationType(irVariableDeclaration);
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irVariableDeclaration->getIRExpression(),
                    operation, irModule, scope);

    InstructionIRInjectorHelper::injectStore(irExpressionValue, irVariableDeclaration->getValue(), irBlock, irVariableDeclaration->getAllocatedIRType());
    if (irVariableDeclaration->getGlobalVariable()) {
        InstructionIRInjectorHelper::injectStore(irExpressionValue, irVariableDeclaration->getGlobalVariable().value()->getValue(), irBlock, irVariableDeclaration->getGlobalVariable().value()->getIRType());

        // we need to increment the ref count for global variables because they need
        // the extra ref increment on initialization to prevent them from being freed after first use
        if (irVariableDeclaration->getAllocatedIRType()->requiresArc()) {
            irVariableDeclaration->getAllocatedIRType()->isInvocableType()
            ? irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementLambdaRefCountFunction(), { irVariableDeclaration->getGlobalVariable().value()->getValue() })
            : irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irVariableDeclaration->getGlobalVariable().value()->getValue() });
        }
    }
    if (irVariableDeclaration->getArc()) {
        InstructionIRInjectorHelper::inject(irVariableDeclaration->getArc().value(), irBlock, irVariableDeclaration->getVariableName() + ".arc");
    }
    if (irVariableDeclaration->toBeFreedDirectly()) {
        Logger::log("found variable to free!", irVariableDeclaration->getVariableName());
        irBlock->addVariableToFree(irVariableDeclaration);
    } else if (irVariableDeclaration->isLambdaVariable()) {
        irBlock->addLambdaVariableToFree(irVariableDeclaration);
    }
}

IROperation* VariableIRInjectorStrategy::determineOperationType(std::shared_ptr<IRVariableDeclarationNode> irVariableDeclaration) {
    auto operation = irVariableDeclaration->getIRExpression()->is(IR_REF_EXPRESSION_NODE)
            ? new IROperation(IR_REF_ASSIGNMENT_OP)
            : new IROperation(IR_COPY_ASSIGNMENT_OP);
    if (irVariableDeclaration->getGlobalVariable()) {
        operation->markAsGlobal();
    }
    return operation;
}