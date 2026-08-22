//
// Created by Johny Georges on 2024-05-27.
//

#include "control-flow-condition-type-checker-policy.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../../../../type-signature/literal-type-signature/bool-literal-type-signature.h"


namespace ControlFlowConditionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTControlFlowConditionNode> controlFlowConditionNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
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