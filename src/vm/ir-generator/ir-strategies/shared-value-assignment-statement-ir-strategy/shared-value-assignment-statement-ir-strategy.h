//
// Created by Johny Georges on 2026-02-20.
//

#ifndef JETLANG_SHARED_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_SHARED_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-shared-value-assignment-statement-node.h"

class SharedValueAssignmentStatementIRStrategy {
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTSharedValueAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_SHARED_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
