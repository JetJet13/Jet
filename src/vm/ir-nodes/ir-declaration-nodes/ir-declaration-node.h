//
// Created by Johny Georges on 2024-07-08.
//

#ifndef JETLANG_IR_DECLARATION_NODE_H
#define JETLANG_IR_DECLARATION_NODE_H

#include "../ir-node.h"

class IRDeclarationNode : public IRNode {
public:
    virtual llvm::Value* insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) = 0;
    virtual llvm::Value* getIRValue() = 0;
};

#endif //JETLANG_IR_DECLARATION_NODE_H
