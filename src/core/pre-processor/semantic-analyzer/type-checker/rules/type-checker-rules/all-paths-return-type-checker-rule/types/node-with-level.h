//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_NODE_WITH_LEVEL_H
#define JETLANG_NODE_WITH_LEVEL_H

#include "../../../../../../../ast/ast-nodes/ast-node.h"

struct NodeWithLevel {
    ASTNode* node;
    unsigned long level;
};

#endif //JETLANG_NODE_WITH_LEVEL_H
