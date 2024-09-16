//
// Created by Johny Georges on 2024-08-01.
//

#ifndef JETLANG_IR_ENUM_TYPE_H
#define JETLANG_IR_ENUM_TYPE_H

#include "ir-struct-type.h"

class IREnumType : public IRStructType {
    using IRStructType::IRStructType;
public:
    llvm::Type* getValueType();
    bool isEnumType() override;
};

#endif //JETLANG_IR_ENUM_TYPE_H
