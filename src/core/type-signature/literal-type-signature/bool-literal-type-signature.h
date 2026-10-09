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
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_BOOL_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_BOOL_LITERAL_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "types/literal-type.h"
#include "literal-type-signature.h"

class BoolLiteralTypeSignature : public LiteralTypeSignature {
public:
    std::shared_ptr<LiteralTypeSignature> clone() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
};

#endif //JETLANG_BOOL_LITERAL_TYPE_SIGNATURE_H
