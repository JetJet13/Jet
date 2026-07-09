//
// Created by Johny Georges on 2025-08-30.
//

#ifndef JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-object-access-assignment-statement-node.h"

class ObjectAccessAssignmentStatementIRStrategy {
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTObjectAccessAssignmentStatementNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
