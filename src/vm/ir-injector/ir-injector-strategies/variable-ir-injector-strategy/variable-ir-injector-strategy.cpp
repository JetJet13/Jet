//
// Created by Johny Georges on 2024-08-15.
//

#include "llvm/IR/IntrinsicInst.h"
#include "variable-ir-injector-strategy.h"
#include "../../ir-injector-map.h"

void VariableIRInjectorStrategy::inject(IRVariableDeclarationNode* irVariableDeclaration, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule) {
    builder->get()->Insert(irVariableDeclaration->getValue(), irVariableDeclaration->getVariableName());
    auto irExpressionValue = irInjectorMap->getInjector(irVariableDeclaration->getIRExpression()->getTypeSignature())
            ->inject(
                    irVariableDeclaration->getIRExpression(),
                    builder,
                    irInjectorMap,
                    IR_COPY_ASSIGNMENT_OP, irModule);

    builder->get()->CreateStore(irExpressionValue, irVariableDeclaration->getValue());
    // this print function call will cause a segmentation fault since the first param
    // of the print function is an i8 ptr so add support for a built-in function: 'print' that handles this.
    // for ref: https://cplusplus.com/reference/cstdio/printf/
    // $ ld ./cmake-build-debug-jet-lang-toolchain/src/jet/main-jet-test-file-output.o -o main-jet.exe  -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
    builder->get()->CreateCall(irModule->getPrintFunction(), { irExpressionValue });
}