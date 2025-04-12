//
// Created by Johny Georges on 2025-04-12.
//

#ifndef JETLANG_IR_TYPE_VALUE_TYPE_H
#define JETLANG_IR_TYPE_VALUE_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"

class IRTypeValueType : public IRType {
private:
    llvm::StructType* _type;
    unsigned int _idIndex;
    unsigned int _sizeInBytesIndex;
    unsigned int _numElementsIndex;
    unsigned int _allocIndex;
public:
    explicit IRTypeValueType(llvm::StructType* type);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getIdIndex() const;
    [[nodiscard]] unsigned int getSizeInBytesIndex() const;
    [[nodiscard]] unsigned int getNumElementsIndex() const;
    [[nodiscard]] unsigned int getAllocIndex() const;
    llvm::PointerType* getAllocType();
    uint64_t getSizeInBytes() override;
    bool isTypeValueType() override;
};

#endif //JETLANG_IR_TYPE_VALUE_TYPE_H
