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
// Created by Johny Georges on 2025-07-12.
//

#ifndef JETLANG_LAMBDA_TYPE_SIGNATURE_H
#define JETLANG_LAMBDA_TYPE_SIGNATURE_H

#include <optional>
#include "../../type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../invocable-type-signature.h"
#include "../../struct-type-signature/struct-type-signature.h"
#include "../../void-type-signature/void-type-signature.h"

class LambdaTypeSignature : public InvocableTypeSignature {
private:
    std::vector<std::shared_ptr<TypeSignature>> _parameterTypes;
    std::shared_ptr<TypeSignature> _returnType;
public:
    LambdaTypeSignature();
    LambdaTypeSignature(std::vector<std::shared_ptr<TypeSignature>> parameterTypes, std::optional<std::shared_ptr<TypeSignature>> returnType = {});
    int numParameters();
    std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes() override;
    bool hasScopeArgument() override;
    bool doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) override;
    std::shared_ptr<TypeSignature> getReturnType() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_LAMBDA_TYPE_SIGNATURE_H
