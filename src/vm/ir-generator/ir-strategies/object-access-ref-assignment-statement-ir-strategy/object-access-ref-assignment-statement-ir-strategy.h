//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-object-access-ref-assignment-statement-node.h"

class ObjectAccessRefAssignmentStatementIRStrategy {
public:
    IRStatementNode* generate(std::shared_ptr<ASTObjectAccessRefAssignmentStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
