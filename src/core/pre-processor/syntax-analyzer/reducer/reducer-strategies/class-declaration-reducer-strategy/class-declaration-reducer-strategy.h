//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_CLASS_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_CLASS_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ClassDeclarationReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_CLASS_DECLARATION_REDUCER_STRATEGY_H
