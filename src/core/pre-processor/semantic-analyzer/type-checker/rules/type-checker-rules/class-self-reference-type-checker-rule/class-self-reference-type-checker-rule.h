//
// Created by Johny Georges on 2026-06-24.
//

#ifndef JETLANG_CLASS_SELF_REFERENCE_TYPE_CHECKER_RULE_H
#define JETLANG_CLASS_SELF_REFERENCE_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../../../../type-signature/class-type-signature/class-type-signature.h"

class ClassSelfReferenceTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(ClassTypeSignature* classTypeSignature, ClassPropertyTypeSignature* classPropertyTypeSignature, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_CLASS_SELF_REFERENCE_TYPE_CHECKER_RULE_H
