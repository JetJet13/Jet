//
// Created by Johny Georges on 2024-03-23.
//

#ifndef JETLANG_ENUM_KEY_VALUE_REDUCER_STRATEGY_H
#define JETLANG_ENUM_KEY_VALUE_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-node.h"

class EnumKeyValueReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_ENUM_KEY_VALUE_REDUCER_STRATEGY_H
