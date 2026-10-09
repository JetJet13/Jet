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
// Created by Johny Georges on 2024-12-31.
//

#ifndef JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_H
#define JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_H

#include <vector>
#include "../type-signature.h"
#include "../literal-type-signature/types/literal-type.h"

class ArgumentListTypeSignature : public TypeSignature {
private:
    std::vector<std::shared_ptr<TypeSignature>> _argumentTypes;
public:
    ArgumentListTypeSignature();
    ArgumentListTypeSignature(std::vector<std::shared_ptr<TypeSignature>> argumentTypes);
    std::vector<std::shared_ptr<TypeSignature>>* getArgumentTypes();
    uint64_t numParameters();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_H
