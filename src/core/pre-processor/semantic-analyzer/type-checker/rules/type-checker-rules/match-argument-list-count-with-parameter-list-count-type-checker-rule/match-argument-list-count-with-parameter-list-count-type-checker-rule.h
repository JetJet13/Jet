//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_MATCH_ARGUMENT_LIST_COUNT_WITH_PARAMETER_LIST_COUNT_TYPE_CHECKER_RULE_H
#define JETLANG_MATCH_ARGUMENT_LIST_COUNT_WITH_PARAMETER_LIST_COUNT_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../types/type-checker-error-message-table.h"

class MatchArgumentListCountWithParameterListCountTypeCheckerRule : public TypeCheckerRule {
public:
    bool enforce(uint64_t numParameters, uint64_t numArguments, bool isVariableLength, ErrorMessageLambda& notEnoughArgumentsMessage, ErrorMessageLambda& tooManyArgumentsMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_MATCH_ARGUMENT_LIST_COUNT_WITH_PARAMETER_LIST_COUNT_TYPE_CHECKER_RULE_H
