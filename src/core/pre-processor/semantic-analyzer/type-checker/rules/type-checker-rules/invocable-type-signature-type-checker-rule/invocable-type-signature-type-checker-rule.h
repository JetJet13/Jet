//
// Created by Johny Georges on 2025-10-07.
//

#ifndef JETLANG_INVOCABLE_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H
#define JETLANG_INVOCABLE_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../types/type-checker-error-message-table.h"

class InvocableTypeSignatureTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(TypeSignature* typeSignature, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_INVOCABLE_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H
