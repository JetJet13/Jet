//
// Created by Johny Georges on 2024-08-15.
//

#include "variable-ir-injector-strategy.h"

void VariableIRInjectorStrategy::inject(IRVariableDeclarationNode* irVariableDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    irBlock->getBuilder()->get()->Insert(irVariableDeclaration->getValue(), irVariableDeclaration->getVariableName());
    auto operation = irVariableDeclaration->getGlobalVariable().has_value() ? IR_COPY_GLOBAL_ASSIGNMENT_OP : IR_COPY_ASSIGNMENT_OP;
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irVariableDeclaration->getIRExpression(),
                    operation, irModule, scope);

    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, irVariableDeclaration->getValue());
    if (irVariableDeclaration->getGlobalVariable()) {
        irBlock->getBuilder()->get()->CreateStore(irExpressionValue, irVariableDeclaration->getGlobalVariable().value()->getValue());
    }
    // $ ld ./cmake-build-debug-jet-lang-toolchain/src/jet/main-jet-test-file-output.o -o main-jet.exe  -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
//    if (irVariableDeclaration->getIRExpression()->getIRType()->isIntegerType()) {
//        builder->get()->CreateCall(irModule->getPrintFunction(), { irExpressionValue });
//    }
}