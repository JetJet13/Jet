//
// Created by Johny Georges on 2024-07-02.
//

#ifndef JETLANG_IR_EXPRESSION_NODE_H
#define JETLANG_IR_EXPRESSION_NODE_H

#include "../ir-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../../../core/type-signature/type-signature.h"
#include "../../../core/lexeme/types/position.h"

class IRExpressionNode : public IRNode {
protected:
    bool _isGlobal = false;
    bool _isAssigned = false;
public:
    virtual void markAsGlobal();
    bool isGlobal();
    virtual bool isReferenced();
    virtual bool isAssigned();
    void markAsAssigned();
    bool needsToBeFreed();
    bool hasArc();
    IRType* getUnderlyingIRType();
    virtual TypeSource getInjectorTypeSource();
    virtual std::optional<IRInstructionNode*> getSourceAllocation();
    virtual std::optional<IRInstructionNode*> getArc();
    virtual llvm::Type* getType();
    virtual llvm::Type* getTypeAtIndex(unsigned long index);
    virtual llvm::Value* getValue() = 0;
    virtual IRType* getIRType() = 0;
    virtual TypeSignature* getTypeSignature() = 0;
    virtual Position* getStartPosition() = 0;
    virtual Position* getEndPosition() = 0;
    bool isExpression() override;
};

#endif //JETLANG_IR_EXPRESSION_NODE_H
