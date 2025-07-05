//
// Created by Johny Georges on 2025-07-04.
//

#ifndef JETLANG_IR_TYPE_DECLARATION_NODE_H
#define JETLANG_IR_TYPE_DECLARATION_NODE_H

#include "../ir-node.h"

class IRTypeDeclarationNode : public IRNode {
public:
    bool isTypeDeclaration() override;
};

#endif //JETLANG_IR_TYPE_DECLARATION_NODE_H
