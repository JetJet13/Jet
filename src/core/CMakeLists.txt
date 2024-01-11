add_library(jet-core
        ./lexeme/lexeme.h
        ./lexeme/lexeme.cpp

        ./symbol/symbol.h
        ./symbol/symbol.cpp

        symbol/symbol-factory.cpp
        symbol/symbol-factory.h
        token/token.cpp
        token/token.h
        token/token-factory.cpp
        token/token-factory.h
        symbol/types/symbol-type.h
        file-reader/file-reader.cpp
        file-reader/file-reader.h
        reserved-keywords/reserved-keywords.cpp
        reserved-keywords/reserved-keywords.h
        pre-processor/lexical-analyzer/lexical-analyzer.cpp
        pre-processor/lexical-analyzer/lexical-analyzer.h
        token/token-table.cpp
        token/token-table.h
        char-table/char-table.cpp
        char-table/char-table.h

)

target_link_libraries(jet-core
        PRIVATE jet-shared
)