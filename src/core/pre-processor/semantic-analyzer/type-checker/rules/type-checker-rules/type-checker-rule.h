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
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RULE_H
#define JETLANG_TYPE_CHECKER_RULE_H

#include <string>
#include "../types/type-checker-rule-type.h"

class TypeCheckerRule {
public:
    bool hasType(TypeCheckerRuleType type);
    virtual TypeCheckerRuleType getType() = 0;
    virtual std::string toString() = 0;
    virtual bool isEqualTo(TypeCheckerRule* other) = 0;
    virtual void print() = 0;
};

#endif //JETLANG_TYPE_CHECKER_RULE_H
