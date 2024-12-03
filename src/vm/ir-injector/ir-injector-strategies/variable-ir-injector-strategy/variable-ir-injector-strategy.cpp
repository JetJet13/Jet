//
// Created by Johny Georges on 2024-08-15.
//

#include "variable-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-node.h"

void VariableIRInjectorStrategy::inject(IRVariableDeclarationNode* irVariableDeclaration, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope) {
    auto allocation = builder->get()->Insert(irVariableDeclaration->getValue(), irVariableDeclaration->getVariableName());
    if (irVariableDeclaration->getIRExpression()->isOneOf({ IR_LAMBDA_EXPRESSION_NODE, IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE })) {
        auto irLambdaExpression = (IRLambdaExpressionNode*)irVariableDeclaration->getIRExpression();
        auto zeroIndex = builder->get()->getInt32(0);
        auto functionIndex = builder->get()->getInt32(irLambdaExpression->getIRType()->getLambdaVariableType()->getFunctionIndex());
        auto functionPointer = builder->get()->CreateInBoundsGEP(irVariableDeclaration->getAllocatedType(), allocation, { zeroIndex, functionIndex });
        builder->get()->CreateStore(irLambdaExpression->getValue(), functionPointer);
        if (irLambdaExpression->getIRType()->getLambdaScopeType()) {
            auto irLambdaScopeType = (IRStructType*)irLambdaExpression->getIRType()->getLambdaScopeType().value();
            auto functionArgumentIndex = builder->get()->getInt32(irLambdaExpression->getIRType()->getLambdaVariableType()->getFunctionScopeArgumentIndex());
            auto functionArgumentPointer = builder->get()->CreateInBoundsGEP(irVariableDeclaration->getAllocatedType(), allocation, { zeroIndex, functionArgumentIndex });
            auto lambdaScopeAllocation = builder->get()->CreateAlloca(irLambdaScopeType->getType());
            for (int i = 0; i < irLambdaScopeType->size(); ++i) {
                auto index = builder->get()->getInt32(i);
                auto key = irLambdaScopeType->getKeyForIndex(i);
                auto allocationForKey = scope->find(key).value();
                auto pointer = builder->get()->CreateGEP(irLambdaScopeType->getType(), lambdaScopeAllocation, { zeroIndex, index });
                builder->get()->CreateStore(allocationForKey->getValue(), pointer);
            }
            builder->get()->CreateStore(lambdaScopeAllocation, functionArgumentPointer);
        }

    } else {
        auto irExpressionValue = irInjectorMap->getInjector(irVariableDeclaration->getIRExpression()->getTypeSignature())
                ->inject(
                        irVariableDeclaration->getIRExpression(),
                        builder,
                        irInjectorMap,
                        IR_COPY_ASSIGNMENT_OP, irModule, scope);

        builder->get()->CreateStore(irExpressionValue, irVariableDeclaration->getValue());
    }
    // $ ld ./cmake-build-debug-jet-lang-toolchain/src/jet/main-jet-test-file-output.o -o main-jet.exe  -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem
//    if (irVariableDeclaration->getIRExpression()->getIRType()->isIntegerType()) {
//        builder->get()->CreateCall(irModule->getPrintFunction(), { irExpressionValue });
//    }
}