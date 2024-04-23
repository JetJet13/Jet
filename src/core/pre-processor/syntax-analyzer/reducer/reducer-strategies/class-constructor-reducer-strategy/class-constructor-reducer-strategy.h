//
// Created by Johny Georges on 2024-04-21.
//

#ifndef JETLANG_CLASS_CONSTRUCTOR_REDUCER_STRATEGY_H
#define JETLANG_CLASS_CONSTRUCTOR_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ClassConstructorReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_CLASS_CONSTRUCTOR_REDUCER_STRATEGY_H
