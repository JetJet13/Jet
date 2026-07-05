//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_IR_MODULE_TYPE_H
#define JETLANG_IR_MODULE_TYPE_H

#include "ir-struct-type.h"

class IRModuleType : public IRStructType {
    using IRStructType::IRStructType;
public:
    llvm::Type* getValueType();
    bool isModuleType() override;
    std::shared_ptr<IRType> clone() override;
};

#endif //JETLANG_IR_MODULE_TYPE_H
