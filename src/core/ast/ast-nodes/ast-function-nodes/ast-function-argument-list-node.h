//
// Created by Johny Georges on 2024-03-25.
//

#ifndef JETLANG_AST_FUNCTION_ARGUMENT_LIST_NODE_H
#define JETLANG_AST_FUNCTION_ARGUMENT_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-function-parameter-node.h"
#include "ast-function-argument-node.h"
#include "ast-function-argument-list-start-node.h"
#include "ast-function-argument-list-end-node.h"
#include "../ast-comma-node.h"
#include "../../../type-signature/argument-list-type-signature/argument-list-type-signature.h"

class ASTFunctionArgumentListNode : public ASTNode {
private:
    std::shared_ptr<ASTFunctionArgumentListStartNode> _functionArgumentListStartNode;
    std::shared_ptr<ASTFunctionArgumentListEndNode> _functionArgumentListEndNode;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTFunctionArgumentNode>> _arguments;
    std::shared_ptr<ArgumentListTypeSignature> _typeSignature;
public:
    ASTFunctionArgumentListNode(std::shared_ptr<ASTFunctionArgumentListStartNode> functionArgumentListStartNode, std::shared_ptr<ASTFunctionArgumentListEndNode> functionArgumentListEndNode);
    ASTFunctionArgumentListNode(std::shared_ptr<ASTFunctionArgumentListStartNode> functionArgumentListStartNode, std::vector<std::shared_ptr<ASTFunctionArgumentNode>> arguments, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTFunctionArgumentListEndNode> functionArgumentListEndNode);
    std::vector<std::shared_ptr<ASTFunctionArgumentNode>>* getArguments();
    unsigned long numArguments();
    std::shared_ptr<ASTFunctionArgumentListNode> addArgument(std::shared_ptr<ASTFunctionArgumentNode> argument);
    std::shared_ptr<ASTFunctionArgumentListNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    void setTypeSignature(std::shared_ptr<ArgumentListTypeSignature> typeSignature);
    std::shared_ptr<ArgumentListTypeSignature> getArgumentListTypeSignature();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_ARGUMENT_LIST_NODE_H
