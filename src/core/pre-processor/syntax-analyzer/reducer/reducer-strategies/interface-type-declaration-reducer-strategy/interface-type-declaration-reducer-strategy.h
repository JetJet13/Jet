//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_INTERFACE_TYPE_DECLARATION_REDUCER_STRATEGY_H
#define JETLANG_INTERFACE_TYPE_DECLARATION_REDUCER_STRATEGY_H

#include <vector>
#include "../reducer-strategy.h"

class InterfaceTypeDeclarationReducerStrategy : public ReducerStrategy {
public:
    std::shared_ptr<ASTNode> execute(std::vector<std::shared_ptr<ASTNode>> nodes) override;
};

#endif //JETLANG_INTERFACE_TYPE_DECLARATION_REDUCER_STRATEGY_H
