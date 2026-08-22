//
// Created by Johny Georges on 2024-05-27.
//

#include "while-statement-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace WhileStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTWhileStatementNode> whileStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(whileStatementNode->getCondition(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(whileStatementNode->getBlock(), typeCheckerResult, fileScope);
    }
}