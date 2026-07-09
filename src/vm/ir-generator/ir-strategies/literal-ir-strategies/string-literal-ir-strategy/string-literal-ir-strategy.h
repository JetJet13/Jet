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
    std::shared_ptr<IRStringLiteralNode> generate(std::shared_ptr<ASTStringLiteralNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext);
    llvm::Constant* generateIRString(std::string rawString, std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context);
};

#endif //JETLANG_STRING_LITERAL_IR_STRATEGY_H
