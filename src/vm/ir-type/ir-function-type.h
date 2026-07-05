//
// Created by Johny Georges on 2024-08-02.
//

#ifndef JETLANG_IR_FUNCTION_TYPE_H
#define JETLANG_IR_FUNCTION_TYPE_H

#include "ir-struct-type.h"

class IRFunctionType : public IRType {
private:
    llvm::FunctionType* _type;
    bool _requiresScopeArgument;
public:
    IRFunctionType(llvm::FunctionType* type, bool requiresScopeArgument = false);
    bool requiresScopeArgument();
    llvm::FunctionType* getType() override;
    std::shared_ptr<IRType> clone() override;
};

#endif //JETLANG_IR_FUNCTION_TYPE_H
