//
// Created by Johny Georges on 2025-01-02.
//

#ifndef JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-class-property-assignment-statement-node.h"

class ClassPropertyAssignmentStatementIRStrategy {
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTClassPropertyAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
