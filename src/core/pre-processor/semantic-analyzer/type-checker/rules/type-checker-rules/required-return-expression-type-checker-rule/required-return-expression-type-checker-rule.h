//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_REQUIRED_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
#define JETLANG_REQUIRED_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H

#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-try-statement-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"
#include "../../../../../../ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"


class RequiredReturnExpressionTypeCheckerRule : public TypeCheckerRule {
private:
    void checkNode(std::vector<std::shared_ptr<ASTNode>>* nodes, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult);
public:
    void enforce(std::shared_ptr<ASTFunctionBlockNode> functionBlockNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<ASTIfStatementNode> ifStatementNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<ASTTryStatementNode> tryStatementNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<ASTForInStatementNode> forStatementNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult);
    void enforce(std::shared_ptr<ASTWhileStatementNode> whileStatementNode, std::shared_ptr<TypeSignature> returnType, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_REQUIRED_RETURN_EXPRESSION_TYPE_CHECKER_RULE_H
