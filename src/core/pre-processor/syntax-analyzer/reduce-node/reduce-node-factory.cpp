//
// Created by Johny Georges on 2024-02-24.
//

#include "reduce-node-factory.h"
#include "../../../ast/ast-nodes/ast-node-utils/ast-node-utils.h"


ReduceNode* ReduceNodeFactory::create(Handle handle, int numNodesToReduce, ASTNodeType targetAstNodeType) {
    auto lastNode = handle.at(numNodesToReduce - 1).value();
//    if (lastNode->getNodeType() == AST_TERMINATOR_NODE) {
//        auto firstNode = handle.at(0).value();
//        if (numNodesToReduce == 2 && ASTNodeUtils::isDeclarationNode(firstNode)) {
//            return new ReduceNode(numNodesToReduce, targetAstNodeType);
//        }
//        return new ReduceNode(numNodesToReduce - 1, targetAstNodeType);
//    }

    return new ReduceNode(numNodesToReduce, targetAstNodeType);
}