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
// Created by Johny Georges on 2024-05-29.
//

#include "return-type-signature-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ReturnTypeSignatureTypeCheckerRule::enforce(std::optional<std::shared_ptr<ASTNode>> node, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (node) {
        this->enforce(node.value()->getTypeSignature(), unknownMessage, invalidMessage, typeCheckerResult);
    }
}

void ReturnTypeSignatureTypeCheckerRule::enforce(std::shared_ptr<TypeSignature> typeSignature, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult) {
    if (typeSignature->isUnknown()) {
        typeCheckerResult->addError(unknownMessage());
    } else if (typeSignature->isInvalid()) {
        typeCheckerResult->addError(invalidMessage());
    }
}

TypeCheckerRuleType ReturnTypeSignatureTypeCheckerRule::getType() {
    return RETURN_TYPE_SIGNATURE_TCR;
}

std::string ReturnTypeSignatureTypeCheckerRule::toString() {
    return "RETURN_TYPE_SIGNATURE";
}

bool ReturnTypeSignatureTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void ReturnTypeSignatureTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}