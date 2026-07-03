//
// Created by Johny Georges on 2024-05-02.
//

#include "ast-node-id-strategy.h"

ASTNodeIdStrategy::ASTNodeIdStrategy(std::shared_ptr<TokenTable> tokenTable) {
    _tokenTable = tokenTable;
}