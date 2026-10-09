// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_NO_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
#define JETLANG_NO_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-try-statement-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"
#include "../../../types/type-checker-error-message-table.h"

class NoReturnExpressionTypeCheckerRule : public TypeCheckerRule {
private:
    void checkNode(std::vector<std::shared_ptr<ASTNode>>* nodes, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
public:
    void enforce(std::shared_ptr<ASTFunctionBlockNode> functionBlockNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<ASTIfStatementNode> ifStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<ASTTryStatementNode> tryStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<ASTForInStatementNode> forStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<ASTWhileStatementNode> whileStatementNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_NO_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
