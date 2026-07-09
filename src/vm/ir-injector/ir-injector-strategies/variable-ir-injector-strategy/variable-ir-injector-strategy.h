//
// Created by Johny Georges on 2024-08-15.
//

#ifndef JETLANG_VARIABLE_IR_INJECTOR_STRATEGY_H
#define JETLANG_VARIABLE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-variable-declaration-node.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../ir-injector.h"


class VariableIRInjectorStrategy {
private:
    std::shared_ptr<IROperation> determineOperationType(std::shared_ptr<IRVariableDeclarationNode> irVariableDeclaration);
public:
    void inject(std::shared_ptr<IRVariableDeclarationNode> irVariableDeclaration, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_VARIABLE_IR_INJECTOR_STRATEGY_H
