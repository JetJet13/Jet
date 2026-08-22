//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_WHILE_STATEMENT_TYPE_CHECKER_POLICY_H
#define JETLANG_WHILE_STATEMENT_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace WhileStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTWhileStatementNode> whileStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_WHILE_STATEMENT_TYPE_CHECKER_POLICY_H
