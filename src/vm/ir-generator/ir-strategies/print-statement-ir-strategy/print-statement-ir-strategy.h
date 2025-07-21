//
// Created by Johny Georges on 2025-07-21.
//

#ifndef JETLANG_PRINT_STATEMENT_IR_STRATEGY_H
#define JETLANG_PRINT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-print-statement-node.h"

class PrintStatementIRStrategy {
public:
    IRStatementNode* generate(ASTPrintStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_PRINT_STATEMENT_IR_STRATEGY_H
