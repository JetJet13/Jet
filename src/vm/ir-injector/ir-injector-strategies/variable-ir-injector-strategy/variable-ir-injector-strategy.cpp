//
// Created by Johny Georges on 2024-08-15.
//

#include "variable-ir-injector-strategy.h"

void VariableIRInjectorStrategy::inject(IRVariableDeclarationNode* irVariableDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {

    irBlock->getBuilder()->get()->Insert(irVariableDeclaration->getValue(), irVariableDeclaration->getVariableName());
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irVariableDeclaration->getIRExpression(),
                    IR_COPY_ASSIGNMENT_OP, irModule, scope);

    irBlock->getBuilder()->get()->CreateStore(irExpressionValue, irVariableDeclaration->getValue());
    // $ ld ./cmake-build-debug-jet-lang-toolchain/src/jet/main-jet-test-file-output.o -o main-jet.exe  -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
//    if (irVariableDeclaration->getIRExpression()->getIRType()->isIntegerType()) {
//        builder->get()->CreateCall(irModule->getPrintFunction(), { irExpressionValue });
//    }
}