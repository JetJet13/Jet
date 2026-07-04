//
// Created by Johny Georges on 2026-06-27.
//

#ifndef JETLANG_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
#define JETLANG_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-module-access-ref-assignment-statement-node.h"

class ModuleAccessRefAssignmentStatementIRStrategy {
public:
    IRStatementNode* generate(std::shared_ptr<ASTModuleAccessRefAssignmentStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
