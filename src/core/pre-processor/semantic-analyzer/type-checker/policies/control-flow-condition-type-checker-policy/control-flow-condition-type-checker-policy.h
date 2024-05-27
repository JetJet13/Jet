//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_CONTROL_FLOW_CONDITION_TYPE_CHECKER_POLICY_H
#define JETLANG_CONTROL_FLOW_CONDITION_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-control-flow-condition-node.h"


namespace ControlFlowConditionTypeCheckerPolicy {
    void apply(ASTControlFlowConditionNode* controlFlowConditionNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_CONTROL_FLOW_CONDITION_TYPE_CHECKER_POLICY_H
