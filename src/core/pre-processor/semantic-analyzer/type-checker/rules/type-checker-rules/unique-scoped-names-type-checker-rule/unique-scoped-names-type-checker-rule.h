//
// Created by Johny Georges on 2024-05-28.
//

#ifndef JETLANG_UNIQUE_SCOPED_NAMES_TYPE_CHECKER_RULE_H
#define JETLANG_UNIQUE_SCOPED_NAMES_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../../../../ast/ast-nodes/ast-identifier-node.h"

class UniqueScopedNamesTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(std::vector<ASTIdentifierNode*>* names, std::string nonUniqueMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_UNIQUE_SCOPED_NAMES_TYPE_CHECKER_RULE_H
