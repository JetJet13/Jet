// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
