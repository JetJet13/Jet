//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_RETURN_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H
#define JETLANG_RETURN_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../types/type-checker-error-message-table.h"

class ReturnTypeSignatureTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(std::optional<ASTNode*> node, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult);
    void enforce(TypeSignature* typeSignature, ErrorMessageLambda& unknownMessage, ErrorMessageLambda& invalidMessage, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_RETURN_TYPE_SIGNATURE_TYPE_CHECKER_RULE_H
