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
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_IR_PARAMETER_LIST_TYPE_H
#define JETLANG_IR_PARAMETER_LIST_TYPE_H

#include <llvm/IR/Type.h>
#include "ir-parameter-type.h"

class IRParameterListType {
private:
    std::vector<std::shared_ptr<IRParameterType>> _parameters;
public:
    explicit IRParameterListType(std::vector<std::shared_ptr<IRParameterType>> parameters);
    std::vector<std::shared_ptr<IRParameterType>>* getParameters();
    std::vector<llvm::Type*> getParameterTypes();
    std::shared_ptr<IRParameterListType> clone();
};

#endif //JETLANG_IR_PARAMETER_LIST_TYPE_H
