//
// Created by Johny Georges on 2026-02-20.
//

#ifndef JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-class-property-ref-value-assignment-statement-node.h"

class ClassPropertyRefValueAssignmentStatementIRStrategy {
public:
    IRStatementNode* generate(ASTClassPropertyRefValueAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
