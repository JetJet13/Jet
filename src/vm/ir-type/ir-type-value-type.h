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
    unsigned int _numTypesIndex;
    unsigned int _allocIndex;
    unsigned int _keyIndex;
    unsigned int _valueIdIndex;
public:
    explicit IRTypeValueType(llvm::StructType* type);
    llvm::StructType* getType() override;
    [[nodiscard]] unsigned int getIdIndex() const;
    [[nodiscard]] unsigned int getSizeInBytesIndex() const;
    [[nodiscard]] unsigned int getNumTypesIndex() const;
    [[nodiscard]] unsigned int getAllocIndex() const;
    [[nodiscard]] unsigned int getKeyIndex() const;
    [[nodiscard]] unsigned int getValueIdIndex() const;
    llvm::PointerType* getAllocType();
    llvm::PointerType* getKeyType();
    llvm::PointerType* getValueIdType();
    uint64_t getSizeInBytes() override;
    IRTypeValueType* clone() override;
    bool isTypeValueType() override;
};

#endif //JETLANG_IR_TYPE_VALUE_TYPE_H
