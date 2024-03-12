//
// Created by Johny Georges on 2024-03-12.
//

#include "reduce-to-target-map.h"

#include <utility>


ReduceToTargetMap::ReduceToTargetMap(ASTNodeType target, std::vector<ASTNodeType> map) {
    _target = target;
    _map = std::move(map);
}

ASTNodeType ReduceToTargetMap::getTarget() {
    return _target;
}

bool ReduceToTargetMap::isNodeTypeInMap(ASTNodeType astNodeType) {
    return std::find(_map.begin(), _map.end(), astNodeType) != _map.end();
}