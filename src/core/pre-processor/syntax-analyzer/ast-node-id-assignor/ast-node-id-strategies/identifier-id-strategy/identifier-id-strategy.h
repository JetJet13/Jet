//
// Created by Johny Georges on 2024-05-20.
//

#ifndef JETLANG_IDENTIFIER_ID_STRATEGY_H
#define JETLANG_IDENTIFIER_ID_STRATEGY_H

#include "../ast-node-id-strategy.h"

class IdentifierIdStrategy : public ASTNodeIdStrategy {
    using ASTNodeIdStrategy::ASTNodeIdStrategy;
public:
    void assign(std::shared_ptr<ASTNode> node) override;
};

#endif //JETLANG_IDENTIFIER_ID_STRATEGY_H
