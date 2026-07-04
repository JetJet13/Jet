//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_MISMATCH_TYPE_CHECKER_RULE_H
#define JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_MISMATCH_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../../../../type-signature/parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-node.h"
#include "../../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"
#include "../../../types/type-checker-error-message-table.h"

class ArgumentListTypeSignatureMismatchTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(std::vector<TypeSignature*>* parameterList, std::shared_ptr<ASTFunctionArgumentListNode> argumentList,  ErrorMessageLambda& mismatchMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_MISMATCH_TYPE_CHECKER_RULE_H
