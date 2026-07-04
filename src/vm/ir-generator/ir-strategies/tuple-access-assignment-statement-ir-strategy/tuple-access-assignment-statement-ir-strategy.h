//
// Created by Johny Georges on 2025-10-16.
//

#ifndef JETLANG_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-tuple-access-assignment-statement-node.h"

class TupleAccessAssignmentStatementIRStrategy {
public:
    IRStatementNode* generate(std::shared_ptr<ASTTupleAccessAssignmentStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
