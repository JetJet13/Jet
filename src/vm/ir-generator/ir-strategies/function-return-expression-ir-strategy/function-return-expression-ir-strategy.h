//
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_FUNCTION_RETURN_EXPRESSION_IR_STRATEGY_H
#define JETLANG_FUNCTION_RETURN_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-return-expression-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-function-return-expression-node.h"


class FunctionReturnExpressionIRStrategy {
public:
    IRFunctionReturnExpressionNode* generate(ASTFunctionReturnExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};

#endif //JETLANG_FUNCTION_RETURN_EXPRESSION_IR_STRATEGY_H
