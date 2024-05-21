//
// Created by Johny Georges on 2024-05-10.
//

#ifndef JETLANG_AST_TRAVERSER_H
#define JETLANG_AST_TRAVERSER_H

#include <stack>
#include <optional>
#include "../../../ast/ast-nodes/ast-node.h"

class ASTTraverser {
private:
    std::stack<ASTNode*> _stack;
    bool _hasMore;
public:
    ASTTraverser();
    void init(ASTNode* startNode);
    void reset();
    std::optional<ASTNode*> next();
    bool hasMore();
};

#endif //JETLANG_AST_TRAVERSER_H
