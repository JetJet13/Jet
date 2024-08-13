//
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_IR_STATEMENT_NODE_H
#define JETLANG_IR_STATEMENT_NODE_H

#include "../ir-node.h"
#include "../../ir-injector/ir-injector-map.h"

class IRStatementNode : public IRNode {
public:
    virtual void insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *injectorMap) = 0;
};

#endif //JETLANG_IR_STATEMENT_NODE_H
