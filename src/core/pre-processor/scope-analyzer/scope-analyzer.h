//
// Created by Johny Georges on 2025-11-18.
//

#ifndef JETLANG_SCOPE_ANALYZER_H
#define JETLANG_SCOPE_ANALYZER_H

#include "../../ast/ast-nodes/ast-file-node.h"
#include "../../ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../ast/ast-nodes/ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../../ast-lookup-table/ast-lookup-table.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"

class ScopeAnalyzer {
private:
    void traverse(std::shared_ptr<ASTNode> startNode, std::shared_ptr<ASTLookupTable> startScope);
public:
    void process(std::shared_ptr<ASTFileNode> fileNode);
};

#endif //JETLANG_SCOPE_ANALYZER_H
