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
    void inject(std::shared_ptr<IRFunctionDeclarationNode> irFunctionDeclaration, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_FUNCTION_DECLARATION_IR_INJECTOR_STRATEGY_H
