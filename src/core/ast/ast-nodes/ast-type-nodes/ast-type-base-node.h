//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_TYPE_BASE_NODE_H
#define JETLANG_AST_TYPE_BASE_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "types/base-type.h"

class ASTTypeBaseNode : public ASTNode {
public:
    virtual BaseType* getType() = 0;
};

#endif //JETLANG_AST_TYPE_BASE_NODE_H
