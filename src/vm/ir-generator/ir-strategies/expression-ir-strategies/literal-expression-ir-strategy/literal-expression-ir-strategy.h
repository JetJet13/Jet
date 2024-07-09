//
// Created by Johny Georges on 2024-07-02.
//

#ifndef JETLANG_LITERAL_EXPRESSION_IR_STRATEGY_H
#define JETLANG_LITERAL_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"

class LiteralExpressionIRStrategy {
public:
    IRExpressionNode* generate(ASTLiteralExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};

#endif //JETLANG_LITERAL_EXPRESSION_IR_STRATEGY_H
