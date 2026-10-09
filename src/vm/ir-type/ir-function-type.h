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
// Created by Johny Georges on 2024-08-02.
//

#ifndef JETLANG_IR_FUNCTION_TYPE_H
#define JETLANG_IR_FUNCTION_TYPE_H

#include "ir-struct-type.h"

class IRFunctionType : public IRType {
private:
    llvm::FunctionType* _type;
    bool _requiresScopeArgument;
public:
    IRFunctionType(llvm::FunctionType* type, bool requiresScopeArgument = false);
    bool requiresScopeArgument();
    llvm::FunctionType* getType() override;
    std::shared_ptr<IRType> clone() override;
};

#endif //JETLANG_IR_FUNCTION_TYPE_H
