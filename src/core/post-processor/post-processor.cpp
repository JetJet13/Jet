//
// Created by Johny Georges on 2025-03-22.
//

#include "post-processor.h"

PostProcessor::PostProcessor() {
    _refAnalyzer = RefAnalyzer();
}

void PostProcessor::process(JetFile* file) {
    auto scope = new ASTLookupTable();
    for (auto node : *file->getFile()->getBody()) {
        if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
            auto globalVariable = (ASTDeclarationNode*)node;
            scope->insertGlobalVariable(node->getId(), globalVariable);
            _refAnalyzer.analyze(globalVariable, scope);
        } else if (node->isOneOf({ AST_FUNCTION_DECLARATION_NODE, AST_PROCEDURE_DECLARATION_NODE })) {
            auto childScope = new ASTLookupTable();
            childScope->inherit(scope);
            scope->insertChildScope(node->getId(), childScope);
            _refAnalyzer.analyze((ASTDeclarationNode*)node, childScope);
        }
    }
}