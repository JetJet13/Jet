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
    IRStatementNode* generate(ASTTupleAccessRefAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
