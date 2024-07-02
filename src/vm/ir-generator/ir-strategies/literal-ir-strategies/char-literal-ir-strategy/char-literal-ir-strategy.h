//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_CHAR_LITERAL_IR_STRATEGY_H
#define JETLANG_CHAR_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../../ir-nodes/ir-literal-nodes/ir-char-literal-node.h"

class CharLiteralIRStrategy {
public:
    IRCharLiteralNode* generate(ASTCharLiteralNode* node, std::unique_ptr<llvm::LLVMContext>*);
};

#endif //JETLANG_CHAR_LITERAL_IR_STRATEGY_H
