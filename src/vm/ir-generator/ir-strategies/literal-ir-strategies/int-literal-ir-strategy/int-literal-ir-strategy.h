//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_INT_LITERAL_IR_STRATEGY_H
#define JETLANG_INT_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../ir-nodes/ir-literal-nodes/ir-int-literal-node.h"
#include "../../../../ir-nodes/ir-context.h"

class IntLiteralIRStrategy {
public:
    IRIntLiteralNode* generate(ASTIntLiteralNode* node, IRContext* irContext);
};

#endif //JETLANG_INT_LITERAL_IR_STRATEGY_H
