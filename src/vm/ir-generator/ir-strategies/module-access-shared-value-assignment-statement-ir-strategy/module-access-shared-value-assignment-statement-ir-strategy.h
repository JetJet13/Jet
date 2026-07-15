//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-module-access-shared-value-assignment-statement-node.h"

class ModuleAccessSharedValueAssignmentStatementIRStrategy {
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTModuleAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
