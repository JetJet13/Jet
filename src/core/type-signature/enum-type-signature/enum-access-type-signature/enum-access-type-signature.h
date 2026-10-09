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
// Created by Johny Georges on 2024-05-17.
//

#ifndef JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_H
#define JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_H

#include "../../type-signature.h"
#include "../enum-type-signature.h"

class EnumAccessTypeSignature : public TypeSignature {
private:
    std::shared_ptr<EnumTypeSignature> _enum;
    std::string _key;
public:
    EnumAccessTypeSignature(std::shared_ptr<EnumTypeSignature> enumTypeSignature, std::string key);
    std::shared_ptr<EnumTypeSignature> getEnum();
    std::string getKey();
    std::shared_ptr<TypeSignature> convertToVariableTypeSignature() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    TypeSource getTypeTarget() override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_ENUM_ACCESS_TYPE_SIGNATURE_H
