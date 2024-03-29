//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_REDUCE_TO_TARGET_DUAL_MAP_H
#define JETLANG_REDUCE_TO_TARGET_DUAL_MAP_H

#include <vector>
#include "../../ast/types/ast-node-type.h"

class ReduceToTargetDualMap {
private:
    ASTNodeType _target;
    std::vector<ASTNodeType> _firstMap;
    std::vector<ASTNodeType> _secondMap;
public:
    ReduceToTargetDualMap(ASTNodeType target, std::vector<ASTNodeType> firstMap,std::vector<ASTNodeType> secondMap);
    ASTNodeType getTarget();
    bool isNodeTypeInMap(ASTNodeType firstNodeType, ASTNodeType secondNodeType);
};

#endif //JETLANG_REDUCE_TO_TARGET_DUAL_MAP_H
