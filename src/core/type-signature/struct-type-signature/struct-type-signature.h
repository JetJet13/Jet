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

#ifndef JETLANG_STRUCT_TYPE_SIGNATURE_H
#define JETLANG_STRUCT_TYPE_SIGNATURE_H

#include "../types/type-signature-map/type-signature-map.h"
#include "../aggregate-type-signature.h"

class StructTypeSignature : public AggregateTypeSignature<TypeSignature> {
private:
    TypeSignatureMap<std::shared_ptr<TypeSignature>> _keyValuePairs;
public:
    StructTypeSignature();
    StructTypeSignature(TypeSignatureMap<std::shared_ptr<TypeSignature>> keyValuePairs);
    bool isEmpty();
    TypeSignatureMap<std::shared_ptr<TypeSignature>>* getKeyValuePairs() override;
    std::shared_ptr<TypeSignature> getTypeSignatureForKey(std::string key) override;
    std::shared_ptr<TypeSignature> getTypeSignatureAtIndex(uint64_t index) override;
    void addKeyValuePair(std::string key, std::shared_ptr<TypeSignature> typeSignature);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_STRUCT_TYPE_SIGNATURE_H
