//
// Created by Johny Georges on 2024-06-26.
//

#ifndef JETLANG_IDENTIFIER_EXPRESSION_IR_STRATEGY_H
#define JETLANG_IDENTIFIER_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

class IdentifierExpressionIRStrategy {
public:
    IRExpressionNode* generate(ASTIdentifierExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRLookupTable* scope);
};

#endif //JETLANG_IDENTIFIER_EXPRESSION_IR_STRATEGY_H
