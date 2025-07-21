//
// Created by Johny Georges on 2025-07-21.
//

#include "print-statement-ir-injector-strategy.h"

void PrintStatementIRInjectorStrategy::inject(IRPrintStatementNode* irPrintStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irPrintStatement->getIRArguments()) {
        arguments.push_back(
                irInjector->inject(irBlock, argument, IR_FUNCTION_ARGUMENT_OP, irModule, scope)
        );
    }
    irBlock->getBuilder()->get()->CreateCall(
        irModule->getPrintFunction()->getFunctionType(),
        irModule->getPrintFunction(),
        arguments
    );
}