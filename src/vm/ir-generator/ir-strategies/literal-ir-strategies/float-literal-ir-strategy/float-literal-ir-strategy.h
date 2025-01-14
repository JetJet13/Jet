//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_FLOAT_LITERAL_IR_STRATEGY_H
#define JETLANG_FLOAT_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../../ir-nodes/ir-literal-nodes/ir-float-literal-node.h"
#include "../../../../ir-nodes/ir-module-node.h"
#include "../../../../ir-nodes/ir-context.h"

class FloatLiteralIRStrategy {
public:
    IRFloatLiteralNode* generate(ASTFloatLiteralNode* node, IRContext* irContext);
};

#endif //JETLANG_FLOAT_LITERAL_IR_STRATEGY_H
