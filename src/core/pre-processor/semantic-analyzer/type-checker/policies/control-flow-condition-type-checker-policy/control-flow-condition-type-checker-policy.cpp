//
// Created by Johny Georges on 2024-05-27.
//

#include "control-flow-condition-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../../../../shared/utils/logger/logger.h"

namespace ControlFlowConditionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTControlFlowConditionNode> controlFlowConditionNode, TypeCheckerResult* typeCheckerResult) {
        auto mismatchMessage = TypeCheckerErrorMessageTable::ControlFlowConditionNotBool(controlFlowConditionNode);
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            controlFlowConditionNode->getTypeSignature(),
            std::make_shared<BoolLiteralTypeSignature>(),
            mismatchMessage,
            typeCheckerResult
        );
    }
}