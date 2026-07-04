//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_CONTROL_FLOW_BLOCK_TYPE_CHECKER_POLICY_H
#define JETLANG_CONTROL_FLOW_BLOCK_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-control-flow-block-node.h"

namespace ControlFlowBlockTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTControlFlowBlockNode> controlFlowBlockNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_CONTROL_FLOW_BLOCK_TYPE_CHECKER_POLICY_H
