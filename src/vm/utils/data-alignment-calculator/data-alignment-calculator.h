//
// Created by Johny Georges on 2024-06-20.
//

#ifndef JETLANG_DATA_ALIGNMENT_CALCULATOR_H
#define JETLANG_DATA_ALIGNMENT_CALCULATOR_H

#include <llvm/Support/Alignment.h>
#include "../../ir-type/ir-type.h"

class DataAlignmentCalculator {
public:
    llvm::Align static calculate(IRType* type);
};

#endif //JETLANG_DATA_ALIGNMENT_CALCULATOR_H
