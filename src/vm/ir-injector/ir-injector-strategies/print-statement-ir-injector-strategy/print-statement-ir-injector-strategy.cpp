//
// Created by Johny Georges on 2025-07-21.
//

#include "print-statement-ir-injector-strategy.h"

void PrintStatementIRInjectorStrategy::inject(IRPrintStatementNode* irPrintStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (unsigned long i = 0; i < irPrintStatement->getIRArguments()->size(); ++i) {
        if (i > 0) {
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getPrintCharFunction()->getFunctionType(),
                    irModule->getPrintCharFunction(),
                    { irPrintStatement->getWhitespace() }
            );
        }
        auto argument = irPrintStatement->getIRArguments()->at(i);
        auto value = irInjector->inject(irBlock, argument, new IROperation(IR_FUNCTION_ARGUMENT_OP), irModule, scope);
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
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getPrintCharFunction()->getFunctionType(),
            irModule->getPrintCharFunction(),
            { irPrintStatement->getNewLine() }
    );
}