//
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_SHARE_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_SHARE_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class ShareExpressionReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_SHARE_EXPRESSION_REDUCER_STRATEGY_H
