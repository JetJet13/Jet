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
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H
#define JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H

#include <vector>
#include "../../type-signature.h"
#include "../../parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../void-type-signature/void-type-signature.h"
#include "../../invocable-type-signature/invocable-type-signature.h"

class ClassConstructorTypeSignature : public InvocableTypeSignature {
private:
    std::shared_ptr<ParameterListTypeSignature> _parameterList;
    std::shared_ptr<VoidTypeSignature> _returnTypeSignature = std::make_shared<VoidTypeSignature>();
public:
    explicit ClassConstructorTypeSignature();
    explicit ClassConstructorTypeSignature(std::shared_ptr<ParameterListTypeSignature> parameterList);
    std::shared_ptr<ParameterListTypeSignature> getParameterList();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool matchArguments(std::vector<std::shared_ptr<TypeSignature>>* argumentTypeSignatures);
    std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes() override;
    bool doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) override;
    std::shared_ptr<TypeSignature> getReturnType() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_CONSTRUCTOR_TYPE_SIGNATURE_H
