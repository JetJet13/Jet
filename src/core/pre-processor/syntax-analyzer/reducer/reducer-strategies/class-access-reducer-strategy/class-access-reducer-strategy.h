//
// Created by Johny Georges on 2024-04-25.
//

#ifndef JETLANG_CLASS_ACCESS_REDUCER_STRATEGY_H
#define JETLANG_CLASS_ACCESS_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-name-node.h"

class ClassAccessReducerStrategy : public ReducerStrategy {
public:
    ASTNode* execute(std::vector<ASTNode*> nodes) override;
};

#endif //JETLANG_CLASS_ACCESS_REDUCER_STRATEGY_H
