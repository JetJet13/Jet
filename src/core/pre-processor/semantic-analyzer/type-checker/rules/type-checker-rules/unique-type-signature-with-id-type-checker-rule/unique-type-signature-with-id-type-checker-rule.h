//
// Created by Johny Georges on 2024-05-28.
//

#ifndef JETLANG_UNIQUE_TYPE_SIGNATURE_WITH_ID_TYPE_CHECKER_RULE_H
#define JETLANG_UNIQUE_TYPE_SIGNATURE_WITH_ID_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"

class UniqueTypeSignatureWithIdTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(std::vector<std::pair<std::string, TypeSignature*>>* pairs, std::string nonUniqueMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};


#endif //JETLANG_UNIQUE_TYPE_SIGNATURE_WITH_ID_TYPE_CHECKER_RULE_H
