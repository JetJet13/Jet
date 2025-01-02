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
    IRStatementNode* generate(ASTClassPropertyAssignmentStatementNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};

#endif //JETLANG_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_IR_STRATEGY_H
