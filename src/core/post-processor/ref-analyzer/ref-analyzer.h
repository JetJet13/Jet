//
// Created by Johny Georges on 2025-03-22.
//

#ifndef JETLANG_REF_ANALYZER_H
#define JETLANG_REF_ANALYZER_H

#include "../../ast/ast-nodes/ast-node.h"
#include "../../ast-lookup-table/ast-lookup-table.h"
#include "../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"
#include "../../ast-traverser/ast-traverser.h"

class RefAnalyzer {
private:
    ASTTraverser _astTraverser;
    void analyze(ASTVariableDeclarationNode* node, ASTLookupTable* scope);
    void analyze(ASTFunctionDeclarationNode* functionNode, ASTLookupTable* scope);
    void analyze(ASTProcedureDeclarationNode* procedureNode, ASTLookupTable* scope);
public:
    RefAnalyzer();
    void analyze(ASTDeclarationNode* node, ASTLookupTable* scope);
};

#endif //JETLANG_REF_ANALYZER_H
