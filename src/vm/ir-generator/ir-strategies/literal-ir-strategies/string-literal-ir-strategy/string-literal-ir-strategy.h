//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_STRING_LITERAL_IR_STRATEGY_H
#define JETLANG_STRING_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../../../ir-nodes/ir-literal-nodes/ir-string-literal-node.h"
#include "../../../ir-generator.h"

class StringLiteralIRStrategy {
public:
    IRStringLiteralNode* generate(ASTStringLiteralNode* node, IRGenerator* irGenerator, IRContext* irContext);
};

#endif //JETLANG_STRING_LITERAL_IR_STRATEGY_H
