//
// Created by Johny Georges on 2026-02-20.
//

#ifndef JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-class-property-shared-value-assignment-statement-node.h"

class ClassPropertySharedValueAssignmentStatementIRStrategy {
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTClassPropertySharedValueAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
