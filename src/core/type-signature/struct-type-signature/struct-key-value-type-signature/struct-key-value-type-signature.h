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
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_STRUCT_KEY_VALUE_TYPE_SIGNATURE_H
#define JETLANG_STRUCT_KEY_VALUE_TYPE_SIGNATURE_H

#include <string>
#include "../../type-signature.h"

class StructKeyValueTypeSignature : public TypeSignature {
private:
    std::string _key;
    std::shared_ptr<TypeSignature> _value;
public:
    StructKeyValueTypeSignature(std::string key, std::shared_ptr<TypeSignature> value);
    std::string getKey();
    std::shared_ptr<TypeSignature> getValue();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_STRUCT_KEY_VALUE_TYPE_SIGNATURE_H
