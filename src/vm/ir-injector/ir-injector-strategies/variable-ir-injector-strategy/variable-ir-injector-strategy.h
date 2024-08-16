//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_VARIABLE_IR_INJECTOR_STRATEGY_H
#define JETLANG_VARIABLE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-nodes/ir-declaration-nodes/ir-variable-declaration-node.h"

class VariableIRInjectorStrategy {
public:
    void inject(IRVariableDeclarationNode* irVariableDeclaration, std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_VARIABLE_IR_INJECTOR_STRATEGY_H
