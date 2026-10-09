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