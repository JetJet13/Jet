//
// Created by Johny Georges on 2025-02-17.
//

#ifndef JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-array-access-assignment-statement-node.h"

class ArrayAccessAssignmentStatementIRStrategy {
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTArrayAccessAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
