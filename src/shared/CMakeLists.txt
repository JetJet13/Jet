add_library(jet-shared
        ./hash-table/hash-table.h
        ./hash-table/hash-table.cpp

        ./types/exit-status.enum.h

        ./utils/file-io/file-io.h
        ./utils/file-io/file-io.cpp

        ./utils/logger/logger.h
        ./utils/logger/logger.cpp

        ./utils/to-string/to-string.h
        ./utils/to-string/to-string.cpp
        types/null-type.h
        types/basic-character-type.h
)