//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_STRUCT_EXPRESSION_REDUCER_STRATEGY_H
#define JETLANG_STRUCT_EXPRESSION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class StructExpressionReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};


#endif //JETLANG_STRUCT_EXPRESSION_REDUCER_STRATEGY_H
