//
// Created by Johny Georges on 2024-05-25.
//

#include "procedure-declaration-type-checker-policy.h"
#include "../../types/type-checker-result-factory.h"
#include "../../types/type-checker-error-message-table.h"

TypeCheckerResult ProcedureDeclarationTypeCheckerPolicy::verify(ASTProcedureDeclarationNode* procedureDeclarationNode) {
    auto errors = std::vector<std::string>();
    for (auto statement : *procedureDeclarationNode->getContent()->getContents()) {
        if (statement->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
            errors.push_back(TypeCheckerErrorMessageTable::ProcedureHasReturnExpression);
        }
    }

    if (errors.empty()) {
        return TypeCheckerResultFactory::createOkResult();
    }
    return TypeCheckerResultFactory::createErrorResult(errors);
}