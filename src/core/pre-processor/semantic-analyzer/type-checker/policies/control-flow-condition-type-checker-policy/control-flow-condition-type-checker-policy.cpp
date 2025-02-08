//
// Created by Johny Georges on 2024-05-27.
//

#include "control-flow-condition-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"
#include "../../../../../../shared/utils/logger/logger.h"

namespace ControlFlowConditionTypeCheckerPolicy {
    void apply(ASTControlFlowConditionNode* controlFlowConditionNode, TypeCheckerResult* typeCheckerResult) {
        Logger::log("controlFlowConditionNode", controlFlowConditionNode->getTypeSignature()->toString());
        controlFlowConditionNode->getTypeSignature()->print();
        TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule()
        ->enforce(
            controlFlowConditionNode->getTypeSignature(),
            new BoolLiteralTypeSignature(),
            TypeCheckerErrorMessageTable::ControlFlowConditionNotBool(controlFlowConditionNode),
            typeCheckerResult
        );
    }
}