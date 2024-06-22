//
// Created by Johny Georges on 2024-06-20.
//

#ifndef JETLANG_DATA_ALIGNMENT_GENERATOR_H
#define JETLANG_DATA_ALIGNMENT_GENERATOR_H

#include <llvm/Support/Alignment.h>
#include "../../ir-type/ir-type.h"

class DataAlignmentGenerator {
public:
    llvm::Align static generate(llvm::Type* type);
    llvm::Align static generate(IRType* type);
};

#endif //JETLANG_DATA_ALIGNMENT_GENERATOR_H
