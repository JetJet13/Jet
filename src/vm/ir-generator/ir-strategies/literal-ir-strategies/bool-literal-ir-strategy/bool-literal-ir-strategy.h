//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_BOOL_LITERAL_IR_STRATEGY_H
#define JETLANG_BOOL_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../../ir-nodes/ir-literal-nodes/ir-bool-literal-node.h"
#include "../../../../ir-nodes/ir-context.h"

class BoolLiteralIRStrategy {
public:
    std::shared_ptr<IRBoolLiteralNode> generate(std::shared_ptr<ASTBooleanLiteralNode> node, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_BOOL_LITERAL_IR_STRATEGY_H
