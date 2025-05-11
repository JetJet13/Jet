//
// Created by Johny Georges on 2025-02-08.
//

#ifndef JETLANG_REF_TYPE_CHECKER_RULE_H
#define JETLANG_REF_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

class RefTypeSignatureTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(RefTypeSignature* typeSignature, std::string invalidMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_REF_TYPE_CHECKER_RULE_H
