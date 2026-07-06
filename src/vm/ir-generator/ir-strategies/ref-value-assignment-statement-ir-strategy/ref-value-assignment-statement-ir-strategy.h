//
// Created by Johny Georges on 2026-02-20.
//

#ifndef JETLANG_REF_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_REF_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-ref-value-assignment-statement-node.h"

class RefValueAssignmentStatementIRStrategy {
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTRefValueAssignmentStatementNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
};

#endif //JETLANG_REF_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
