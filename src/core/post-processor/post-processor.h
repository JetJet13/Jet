//
// Created by Johny Georges on 2025-03-22.
//

#ifndef JETLANG_POST_PROCESSOR_H
#define JETLANG_POST_PROCESSOR_H

#include "../jet-file/jet-file.h"
#include "ref-analyzer/ref-analyzer.h"

class PostProcessor {
private:
    RefAnalyzer _refAnalyzer;
public:
    PostProcessor();
    void process(JetFile* file);
};

#endif //JETLANG_POST_PROCESSOR_H
