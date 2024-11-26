//
// Created by Johny Georges on 2024-11-25.
//

#ifndef JETLANG_EXPRESSION_STATEMENT_IR_STRATEGY_H
#define JETLANG_EXPRESSION_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"

class ExpressionStatementIRStrategy {
public:
    IRStatementNode* generate(ASTExpressionStatementNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};

#endif //JETLANG_EXPRESSION_STATEMENT_IR_STRATEGY_H
