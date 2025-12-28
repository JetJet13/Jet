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

class ASTNewClassInstanceExpressionNode : public ASTCallableExpressionNode {
private:
    ASTNewNode* _new;
    ASTClassNameNode* _className;
    ASTFunctionArgumentListNode* _arguments;
    NewClassInstanceTypeSignature* _typeSignature = new NewClassInstanceTypeSignature();
public:
    explicit ASTNewClassInstanceExpressionNode(ASTNewNode* newKeywordNode, ASTClassNameNode* className, ASTFunctionArgumentListNode* arguments);
    ASTFunctionArgumentListNode* getArguments();
    ASTClassNameNode* getClassName();
    unsigned long numArguments();
    NewClassInstanceTypeSignature* getTypeSignature() override;
    void setTypeSignature(NewClassInstanceTypeSignature* typeSignature);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_NEW_CLASS_INSTANCE_EXPRESSION_H
