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
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H
#define JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H

#include <vector>
#include "../type-signature.h"
#include "../literal-type-signature/types/literal-type.h"
#include "parameter-list-item-type-signature/parameter-list-item-type-signature.h"
#include "../argument-list-type-signature/argument-list-type-signature.h"


class ParameterListTypeSignature : public TypeSignature {
private:
    std::vector<std::shared_ptr<ParameterListItemTypeSignature>> _parameters;
    std::vector<std::shared_ptr<TypeSignature>> _parameterTypes;
    bool _isVariableLength = false;
    uint64_t _variableLengthStartIndex = -1;
    std::optional<std::shared_ptr<ParameterListItemTypeSignature>> _variableLengthTypeSignature;
public:
    ParameterListTypeSignature();
    ParameterListTypeSignature(std::vector<std::shared_ptr<ParameterListItemTypeSignature>> parameters);
    std::vector<std::shared_ptr<ParameterListItemTypeSignature>>* getParameters();
    std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes();
    std::string getId();
    uint64_t numParameters();
    void markAsVariableLength(uint64_t startIndex, std::shared_ptr<ParameterListItemTypeSignature> typeSignature);
    [[nodiscard]] bool isVariableLength() const;
    [[nodiscard]] uint64_t getVariableLengthStartIndex() const;
    std::shared_ptr<ParameterListItemTypeSignature> getVariableLengthTypeSignature();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool matchesWithArgumentList(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature);
    void print() override;
};

#endif //JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H
