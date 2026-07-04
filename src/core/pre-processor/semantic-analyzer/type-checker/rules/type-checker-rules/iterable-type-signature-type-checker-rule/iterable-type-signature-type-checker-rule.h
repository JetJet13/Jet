//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_ITERABLE_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H
#define JETLANG_ITERABLE_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../types/type-checker-error-message-table.h"

class IterableTypeSignatureTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(std::shared_ptr<TypeSignature> typeSignature, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_ITERABLE_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H
