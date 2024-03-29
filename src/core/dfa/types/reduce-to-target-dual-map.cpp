//
// Created by Johny Georges on 2024-03-28.
//

#include "reduce-to-target-dual-map.h"
#include <utility>


ReduceToTargetDualMap::ReduceToTargetDualMap(ASTNodeType target, std::vector<ASTNodeType> firstMap,std::vector<ASTNodeType> secondMap) {
    _target = target;
    _firstMap = std::move(firstMap);
    _secondMap = std::move(secondMap);
}

ASTNodeType ReduceToTargetDualMap::getTarget() {
    return _target;
}

bool ReduceToTargetDualMap::isNodeTypeInMap(ASTNodeType firstNodeType, ASTNodeType secondNodeType) {
    return std::find(_firstMap.begin(), _firstMap.end(), firstNodeType) != _firstMap.end() &&
           std::find(_secondMap.begin(), _secondMap.end(), secondNodeType) != _secondMap.end();
}