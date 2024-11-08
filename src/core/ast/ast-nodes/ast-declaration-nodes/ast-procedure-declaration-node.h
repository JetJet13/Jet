//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_PROCEDURE_DECLARATION_NODE_H
#define JETLANG_AST_PROCEDURE_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-identifier-node.h"
#include "../ast-export-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "ast-declaration-node.h"
#include "../ast-procedure-nodes/ast-procedure-node.h"
#include "../../../type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../ast-procedure-nodes/ast-procedure-definition-node.h"

class ASTProcedureDeclarationNode : public ASTDeclarationNode {
private:
    ASTProcedureDefinitionNode* _procedureDefinition;
    ASTFunctionBlockNode* _block;
    std::optional<ASTExportNode*> _exportKeyword = {};
    ProcedureTypeSignature* _typeSignature = new ProcedureTypeSignature();
public:
    explicit ASTProcedureDeclarationNode(ASTProcedureDefinitionNode* _procedureDefinition, ASTFunctionBlockNode* content, std::optional<ASTExportNode*> exportKeyword = {});
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionNameNode* getName();
    ASTFunctionBlockNode* getBlock();
    unsigned long numParameters();
    bool isExportable() override;
    void setTypeSignature(ProcedureTypeSignature* typeSignature);
    ProcedureTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_PROCEDURE_DECLARATION_NODE_H
