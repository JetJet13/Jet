//
// Created by Johny Georges on 2024-07-08.
//

#ifndef JETLANG_IR_DECLARATION_NODE_H
#define JETLANG_IR_DECLARATION_NODE_H

#include "../ir-node.h"

class IRDeclarationNode : public IRNode {
public:
    virtual llvm::Value* getValue() = 0;
    bool isDeclaration() override;
};

#endif //JETLANG_IR_DECLARATION_NODE_H
