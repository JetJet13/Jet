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
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_DEFINED_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H
#define JETLANG_DEFINED_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../types/type-checker-error-message-table.h"

class DefinedTypeSignatureTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(std::optional<std::shared_ptr<ASTNode>> node, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, ErrorMessageLambda& voidMessage, TypeCheckerResult* typeCheckerResult);
    void enforce(std::optional<std::shared_ptr<ASTNode>> node, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<TypeSignature> typeSignature, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<TypeSignature> typeSignature, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, ErrorMessageLambda& voidMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_DEFINED_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H
