//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_CHAR_LITERAL_IR_STRATEGY_H
#define JETLANG_CHAR_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../../ir-nodes/ir-literal-nodes/ir-char-literal-node.h"
#include "../../../../ir-nodes/ir-context.h"
#include "../../../ir-generator.h"

class CharLiteralIRStrategy {
public:
    std::shared_ptr<IRCharLiteralNode> generate(std::shared_ptr<ASTCharLiteralNode> node, IRGenerator* irGenerator, IRContext* irContext);
};

#endif //JETLANG_CHAR_LITERAL_IR_STRATEGY_H
