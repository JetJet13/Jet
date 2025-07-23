//
// Created by Johny Georges on 2025-07-21.
//

#include "print-statement-ir-injector-strategy.h"

void PrintStatementIRInjectorStrategy::inject(IRPrintStatementNode* irPrintStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irPrintStatement->getIRArguments()) {
        auto value = irInjector->inject(irBlock, argument, IR_FUNCTION_ARGUMENT_OP, irModule, scope);
        if (argument->getIRType()->isIntegerType()) {
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getPrintIntFunction()->getFunctionType(),
                    irModule->getPrintIntFunction(),
                    { value }
            );
        } else if (argument->getIRType()->isFloatType()) {
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getPrintFloatFunction()->getFunctionType(),
                    irModule->getPrintFloatFunction(),
                    { value }
            );
        } else if (argument->getIRType()->isCharType()) {
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getPrintCharFunction()->getFunctionType(),
                    irModule->getPrintCharFunction(),
                    { value }
            );
        } else if (argument->getIRType()->isBoolType()) {
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getPrintBoolFunction()->getFunctionType(),
                    irModule->getPrintBoolFunction(),
                    { value }
            );
        } else {
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getPrintStringFunction()->getFunctionType(),
                    irModule->getPrintStringFunction(),
                    { value }
            );
        }
    }
}