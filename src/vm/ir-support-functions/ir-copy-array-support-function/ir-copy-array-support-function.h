//
// Created by Johny Georges on 2024-08-07.
//

#ifndef JETLANG_IR_COPY_ARRAY_SUPPORT_FUNCTION_H
#define JETLANG_IR_COPY_ARRAY_SUPPORT_FUNCTION_H

#include <llvm/IR/IRBuilder.h>
#include <utility>

class IRCopyArraySupportFunction {
public:
    void insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder);
};

#endif //JETLANG_IR_COPY_ARRAY_SUPPORT_FUNCTION_H
