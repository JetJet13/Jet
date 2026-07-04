//
// Created by Johny Georges on 2024-04-26.
//

#ifndef JETLANG_AST_NEW_CLASS_INSTANCE_EXPRESSION_H
#define JETLANG_AST_NEW_CLASS_INSTANCE_EXPRESSION_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-function-nodes/ast-function-call-node.h"
#include "ast-callable-expression-node.h"
#include "../ast-class-nodes/ast-class-name-node.h"
#include "../ast-class-nodes/ast-new-node.h"
#include "../../../type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "ast-module-access-expression-node.h"

class ASTNewClassInstanceExpressionNode : public ASTCallableExpressionNode {
private:
    std::shared_ptr<ASTNewNode> _new;
    std::optional<std::shared_ptr<ASTClassNameNode>> _className;
    std::optional<std::shared_ptr<ASTModuleAccessExpressionNode>> _moduleAccessExpression;
    std::shared_ptr<ASTFunctionArgumentListNode> _arguments;
    NewClassInstanceTypeSignature* _typeSignature = new NewClassInstanceTypeSignature();
public:
    explicit ASTNewClassInstanceExpressionNode(std::shared_ptr<ASTNewNode> newKeywordNode, std::shared_ptr<ASTClassNameNode> className, std::shared_ptr<ASTFunctionArgumentListNode> arguments);
    explicit ASTNewClassInstanceExpressionNode(std::shared_ptr<ASTNewNode> newKeywordNode, std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpressionNode, std::shared_ptr<ASTFunctionArgumentListNode> arguments);
    std::shared_ptr<ASTFunctionArgumentListNode> getArguments();
    std::string getClassName();
    std::optional<std::string> getModuleName();
    unsigned long numArguments();
    NewClassInstanceTypeSignature* getTypeSignature() override;
    void setTypeSignature(NewClassInstanceTypeSignature* typeSignature);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_NEW_CLASS_INSTANCE_EXPRESSION_H
