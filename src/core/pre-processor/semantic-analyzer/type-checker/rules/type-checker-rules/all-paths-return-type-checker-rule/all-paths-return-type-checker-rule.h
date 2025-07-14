//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_ALL_PATHS_RETURN_TYPE_CHECKER_RULE_H
#define JETLANG_ALL_PATHS_RETURN_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-try-statement-node.h"
#include "../../../types/type-checker-error-message-table.h"


class AllPathsReturnTypeCheckerRule : public TypeCheckerRule {
private:
    bool verifyAllIfStatementPathsReturn(ASTIfStatementNode* ifStatementNode);
    bool verifyAllTryStatementPathsReturn(ASTTryStatementNode* tryStatementNode);
    bool verifyAllBlockPathsReturn(std::vector<ASTNode*>* blockContents);
    bool verifyAllPathsReturn(std::vector<bool>* allPathsReturnResults);
public:
    void enforce(ASTFunctionBlockNode* functionBlockNode, ErrorMessageLambda& message, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_ALL_PATHS_RETURN_TYPE_CHECKER_RULE_H
