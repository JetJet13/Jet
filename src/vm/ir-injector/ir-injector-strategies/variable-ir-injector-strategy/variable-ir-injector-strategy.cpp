//
// Created by Johny Georges on 2024-08-15.
//

#include "variable-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-node.h"

void VariableIRInjectorStrategy::inject(IRVariableDeclarationNode* irVariableDeclaration, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule) {
    builder->get()->Insert(irVariableDeclaration->getValue(), irVariableDeclaration->getVariableName());
    if (irVariableDeclaration->getIRExpression()->is(IR_LAMBDA_EXPRESSION_NODE)) {
        ((IRLambdaExpressionNode*)irVariableDeclaration->getIRExpression())->getValue()->setName(irVariableDeclaration->getVariableName());
    } else {
        auto irExpressionValue = irInjectorMap->getInjector(irVariableDeclaration->getIRExpression()->getTypeSignature())
                ->inject(
                        irVariableDeclaration->getIRExpression(),
                        builder,
                        irInjectorMap,
                        IR_COPY_ASSIGNMENT_OP, irModule);

        builder->get()->CreateStore(irExpressionValue, irVariableDeclaration->getValue());
    }
    // $ ld ./cmake-build-debug-jet-lang-toolchain/src/jet/main-jet-test-file-output.o -o main-jet.exe  -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
//    if (irVariableDeclaration->getIRExpression()->getIRType()->isIntegerType()) {
//        builder->get()->CreateCall(irModule->getPrintFunction(), { irExpressionValue });
//    }
}