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
// Created by Johny Georges on 2026-08-22.
//

#ifndef JETLANG_VARIABLE_CONTEXT_H
#define JETLANG_VARIABLE_CONTEXT_H

#include <memory>

class VariableContext {
private:
    bool _isConstant = false;
public:
    VariableContext();
    void markAsConstant();
    bool isConstant();
};

#endif //JETLANG_VARIABLE_CONTEXT_H
