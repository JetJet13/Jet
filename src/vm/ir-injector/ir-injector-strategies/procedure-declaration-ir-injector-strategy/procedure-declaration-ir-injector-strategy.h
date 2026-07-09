//
// Created by Johny Georges on 2025-01-11.
//

#ifndef JETLANG_PROCEDURE_DECLARATION_IR_INJECTOR_STRATEGY_H
#define JETLANG_PROCEDURE_DECLARATION_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-procedure-declaration-node.h"
#include "../../ir-injector.h"

class ProcedureDeclarationIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRProcedureDeclarationNode> irProcedureDeclaration, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_PROCEDURE_DECLARATION_IR_INJECTOR_STRATEGY_H
