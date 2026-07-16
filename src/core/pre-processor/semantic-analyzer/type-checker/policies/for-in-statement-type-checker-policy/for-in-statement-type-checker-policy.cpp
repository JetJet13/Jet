//
// Created by Johny Georges on 2024-05-27.
//

#include "for-in-statement-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace ForInStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTForInStatementNode> forStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(forStatementNode->getBlock(), typeCheckerResult);
        auto notIterableMessage = TypeCheckerErrorMessageTable::ForInStatementSourceNotIterable(forStatementNode->getSource());

        auto sourceTypeSignature = forStatementNode->getSource()->getTypeSignature();
        if (sourceTypeSignature->typeSourceIs(SHARED_TYPE_SOURCE)) {
            auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature);
            sourceTypeSignature = sharedTypeSignature->getUnderlyingType();
        }
        TypeCheckerRuleProvider::getIterableTypeSignatureTypeCheckerRule()
        ->enforce(
            sourceTypeSignature,
            notIterableMessage,
            typeCheckerResult
        );

    }
}