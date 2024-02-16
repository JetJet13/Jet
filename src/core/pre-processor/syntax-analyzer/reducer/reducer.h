//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_REDUCER_H
#define JETLANG_REDUCER_H

#include <vector>
#include "../../../lexeme/lexeme.h"
#include "../../../ast/ast-nodes/ast-node.h"
#include "../handle/handle.h"
#include "../reduce-node/reduce-node.h"

// This class will be responsible
// for reducing handles (i.e. determine what to reduce the handle to)
class Reducer {
private:
    ASTNodeType determineReducedAstNodeType(std::vector<ASTNode*> nodes);
    ASTNode* generateASTNode(ASTNodeType astNodeType, std::vector<ASTNode*> nodes);
public:
    ASTNode* reduce(Handle handle, ReduceNode* reduceNode);
};
#endif //JETLANG_REDUCER_H
