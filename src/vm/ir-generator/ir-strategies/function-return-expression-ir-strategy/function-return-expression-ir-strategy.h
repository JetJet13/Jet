//
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_FUNCTION_RETURN_EXPRESSION_IR_STRATEGY_H
#define JETLANG_FUNCTION_RETURN_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-return-expression-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-function-return-expression-node.h"


class FunctionReturnExpressionIRStrategy {
public:
    std::shared_ptr<IRFunctionReturnExpressionNode> generate(std::shared_ptr<ASTFunctionReturnExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
};

#endif //JETLANG_FUNCTION_RETURN_EXPRESSION_IR_STRATEGY_H
