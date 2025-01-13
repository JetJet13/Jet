//
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_IR_STATEMENT_NODE_H
#define JETLANG_IR_STATEMENT_NODE_H

#include "../ir-node.h"

class IRStatementNode : public IRNode {
public:
    bool isStatement() override;
};

#endif //JETLANG_IR_STATEMENT_NODE_H
