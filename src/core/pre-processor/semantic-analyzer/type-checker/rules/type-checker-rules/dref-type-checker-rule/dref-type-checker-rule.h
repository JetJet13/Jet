//
// Created by Johny Georges on 2025-02-08.
//

#ifndef JETLANG_DREF_TYPE_CHECKER_RULE_H
#define JETLANG_DREF_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"

class DrefTypeSignatureTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(TypeSignature* typeSignature, std::string invalidMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_DREF_TYPE_CHECKER_RULE_H
