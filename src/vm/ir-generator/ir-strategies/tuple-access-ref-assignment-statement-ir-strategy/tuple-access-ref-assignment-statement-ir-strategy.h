//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-tuple-access-ref-assignment-statement-node.h"

class TupleAccessRefAssignmentStatementIRStrategy {
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTTupleAccessRefAssignmentStatementNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
