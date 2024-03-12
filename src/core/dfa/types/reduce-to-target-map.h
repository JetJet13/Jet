//
// Created by Johny Georges on 2024-03-12.
//

#ifndef JETLANG_REDUCE_TO_TARGET_MAP_H
#define JETLANG_REDUCE_TO_TARGET_MAP_H

#include <vector>
#include "../../ast/types/ast-node-type.h"

class ReduceToTargetMap {
private:
    ASTNodeType _target;
    std::vector<ASTNodeType> _map;
public:
    ReduceToTargetMap(ASTNodeType target, std::vector<ASTNodeType> map);
    ASTNodeType getTarget();
    bool isNodeTypeInMap(ASTNodeType astNodeType);
};

#endif //JETLANG_REDUCE_TO_TARGET_MAP_H
