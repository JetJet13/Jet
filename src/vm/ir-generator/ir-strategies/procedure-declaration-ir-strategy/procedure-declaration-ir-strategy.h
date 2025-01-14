//
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_PROCEDURE_DECLARATION_IR_STRATEGY_H
#define JETLANG_PROCEDURE_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-procedure-declaration-node.h"

class ProcedureDeclarationIRStrategy {
public:
    IRProcedureDeclarationNode* generate(ASTProcedureDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_PROCEDURE_DECLARATION_IR_STRATEGY_H
