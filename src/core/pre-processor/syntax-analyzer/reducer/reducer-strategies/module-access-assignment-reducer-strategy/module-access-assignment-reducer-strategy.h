//
// Created by Johny Georges on 2026-04-02.
//

#ifndef JETLANG_MODULE_ACCESS_ASSIGNMENT_REDUCER_STRATEGY_H
#define JETLANG_MODULE_ACCESS_ASSIGNMENT_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ModuleAccessAssignmentReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_MODULE_ACCESS_ASSIGNMENT_REDUCER_STRATEGY_H
