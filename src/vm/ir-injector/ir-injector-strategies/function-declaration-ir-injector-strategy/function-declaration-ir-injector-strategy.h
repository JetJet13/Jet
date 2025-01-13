//
// Created by Johny Georges on 2025-01-11.
//

#ifndef JETLANG_FUNCTION_DECLARATION_IR_INJECTOR_STRATEGY_H
#define JETLANG_FUNCTION_DECLARATION_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../ir-injector.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-declaration-node.h"

class FunctionDeclarationIRInjectorStrategy {
public:
    void inject(IRFunctionDeclarationNode* irFunctionDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope);
};

#endif //JETLANG_FUNCTION_DECLARATION_IR_INJECTOR_STRATEGY_H
