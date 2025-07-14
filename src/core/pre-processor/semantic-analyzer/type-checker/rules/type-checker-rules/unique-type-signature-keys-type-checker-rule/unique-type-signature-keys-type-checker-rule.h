//
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_UNIQUE_TYPE_SIGNATURE_KEYS_TYPE_CHECKER_RULE_H
#define JETLANG_UNIQUE_TYPE_SIGNATURE_KEYS_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../types/type-checker-error-message-table.h"

class UniqueTypeSignatureKeysTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(std::vector<std::string>* keys, ErrorMessageLambda& nonUniqueMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_UNIQUE_TYPE_SIGNATURE_KEYS_TYPE_CHECKER_RULE_H
