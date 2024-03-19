//
// Created by Johny Georges on 2024-03-18.
//

#ifndef JETLANG_FUNCTION_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_FUNCTION_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class FunctionDeclarationReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_FUNCTION_DECLARATION_REDUCER_STRATEGY_H
