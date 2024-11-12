//
// Created by Johny Georges on 2024-11-11.
//

#ifndef JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H
#define JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H

#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"

class IRInjectorMap;

class LambdaIRInjectorStrategy {
public:
    void inject(IRDeclarationNode* irModuleDeclaration, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule);
};

#endif //JETLANG_LAMBDA_IR_INJECTOR_STRATEGY_H
