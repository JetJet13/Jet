//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_REF_VALUE_ASSIGNMENT_TYPE_CHECKER_RULE_H
#define JETLANG_REF_VALUE_ASSIGNMENT_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"
#include "../../../types/type-checker-error-message-table.h"

class RefValueAssignmentTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(TypeSignature* typeSignature, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult);
    void enforce(RefTypeSignature* sourceTypeSignature, TypeSignature* valueTypeSignature, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_REF_VALUE_ASSIGNMENT_TYPE_CHECKER_RULE_H
