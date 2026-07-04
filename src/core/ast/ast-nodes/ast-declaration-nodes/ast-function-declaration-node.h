//
// Created by Johny Georges on 2024-03-18.
//

#ifndef JETLANG_AST_FUNCTION_DECLARATION_NODE_H
#define JETLANG_AST_FUNCTION_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-identifier-node.h"
#include "../ast-export-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "ast-declaration-node.h"
#include "../ast-function-nodes/ast-function-node.h"
#include "../../../type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"
#include "../ast-function-nodes/ast-function-definition-node.h"

class ASTFunctionDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTFunctionDefinitionNode> _functionDefinition;
    std::shared_ptr<ASTFunctionBlockNode> _block;
    std::optional<std::shared_ptr<ASTExportNode>> _exportKeyword = {};
    std::shared_ptr<FunctionTypeSignature> _typeSignature = std::make_shared<FunctionTypeSignature>();
public:
    explicit ASTFunctionDeclarationNode(std::shared_ptr<ASTFunctionDefinitionNode> functionDefinition, std::shared_ptr<ASTFunctionBlockNode> content, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword = {});
    std::shared_ptr<ASTFunctionParameterListNode> getParameters();
    std::shared_ptr<ASTFunctionNameNode> getName();
    std::shared_ptr<ASTTypeNode> getReturnType();
    std::shared_ptr<ASTFunctionBlockNode> getBlock();
    std::shared_ptr<ASTFunctionDefinitionNode> getDefinition();
    unsigned long numParameters();
    bool isExportable() override;
    void setTypeSignature(std::shared_ptr<FunctionTypeSignature> typeSignature);
    std::shared_ptr<FunctionTypeSignature> getFunctionTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_DECLARATION_NODE_H
