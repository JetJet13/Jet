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

#ifndef JETLANG_ENUM_TYPE_SIGNATURE_H
#define JETLANG_ENUM_TYPE_SIGNATURE_H

#include "../literal-type-signature/types/literal-type.h"
#include "../../lexeme/lexeme.h"
#include "../types/type-signature-map/type-signature-map.h"
#include "../literal-type-signature/literal-type-signature.h"
#include "../aggregate-type-signature.h"

class EnumTypeSignature : public AggregateTypeSignature<LiteralTypeSignature> {
private:
    std::shared_ptr<LiteralTypeSignature> _type;
protected:
    TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>> _keyValuePairs;
public:
    EnumTypeSignature();
    explicit EnumTypeSignature(std::shared_ptr<LiteralTypeSignature> type);
    EnumTypeSignature(std::shared_ptr<LiteralTypeSignature> type, TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>> keyValuePairs);
    std::shared_ptr<TypeSignature> setKeyId(std::string id) override;
    TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>>* getKeyValuePairs() override;
    std::shared_ptr<LiteralTypeSignature> getTypeSignatureForKey(std::string key) override;
    std::shared_ptr<LiteralTypeSignature> getTypeSignatureAtIndex(uint64_t index) override;
    std::shared_ptr<LiteralTypeSignature> getType();
    void setType(std::shared_ptr<LiteralTypeSignature> type);
    bool hasKey(std::string key);
    void addKey(std::string key);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void copyFrom(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_ENUM_TYPE_SIGNATURE_H
