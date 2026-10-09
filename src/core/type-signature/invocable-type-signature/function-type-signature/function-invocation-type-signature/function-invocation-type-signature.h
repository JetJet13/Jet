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
// Created by Johny Georges on 2024-05-16.
//

#ifndef JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H
#define JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H

#include <string>
#include "../../../type-signature.h"
#include "../function-type-signature.h"
#include "../../invocable-type-signature.h"


class FunctionInvocationTypeSignature : public TypeSignature {
private:
    std::shared_ptr<InvocableTypeSignature> _invocableTypeSignature;
public:
    FunctionInvocationTypeSignature();
    FunctionInvocationTypeSignature(std::shared_ptr<InvocableTypeSignature> invocableTypeSignature);
    std::shared_ptr<InvocableTypeSignature> getFunctionType();
    std::shared_ptr<TypeSignature> getReturnType();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSource getTypeTarget() override;
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    std::shared_ptr<TypeSignature> getTargetTypeSignature() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_FUNCTION_INVOCATION_TYPE_SIGNATURE_H
