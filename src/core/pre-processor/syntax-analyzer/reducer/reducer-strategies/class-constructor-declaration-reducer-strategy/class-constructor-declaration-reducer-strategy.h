//
// Created by Johny Georges on 2024-04-21.
//

#ifndef JETLANG_CLASS_CONSTRUCTOR_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_CLASS_CONSTRUCTOR_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class ClassConstructorDeclarationReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_CLASS_CONSTRUCTOR_DECLARATION_REDUCER_STRATEGY_H
