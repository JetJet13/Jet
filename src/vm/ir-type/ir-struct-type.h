//
// Created by Johny Georges on 2024-07-16.
//

#ifndef JETLANG_IR_STRUCT_TYPE_H
#define JETLANG_IR_STRUCT_TYPE_H

#include "ir-type.h"

class IRStructType : public IRType {
private:
    llvm::StructType* _type;
public:
    IRStructType(llvm::StructType *type);
    llvm::StructType* getType() override;
};

#endif //JETLANG_IR_STRUCT_TYPE_H
