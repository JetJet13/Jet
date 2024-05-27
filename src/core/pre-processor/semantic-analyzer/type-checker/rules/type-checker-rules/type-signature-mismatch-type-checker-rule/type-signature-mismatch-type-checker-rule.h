//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_TYPE_SIGNATURE_MISMATCH_TYPE_CHECKER_RULE_H
#define JETLANG_TYPE_SIGNATURE_MISMATCH_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"

class TypeSignatureMismatchTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(std::optional<ASTNode*> node, std::optional<ASTNode*> otherNode, std::string mismatchMessage, TypeCheckerResult* typeCheckerResult);
    void enforce(TypeSignature* typeSignature, TypeSignature* otherTypeSignature, std::string mismatchMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_TYPE_SIGNATURE_MISMATCH_TYPE_CHECKER_RULE_H
