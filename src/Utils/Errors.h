#ifndef ERRORS_H
#define ERRORS_H

#include <QString>

namespace MyNote {

enum class ErrorCode {
    SUCCESS = 0,
    OUT_OF_MEMORY,
    INVALID_ARGUMENT,

    FILE_NOT_FOUND,
    CREATE_FILE_FAILED,
    WRITE_FILE_FAILED,
    OPEN_FILE_FAILED,
    READ_FILE_FAILED,
    HANDLE_FILE_FAILED,

    CONTENT_IS_EMPTY,

    POINT_IS_NULLPTR,

    UNKNOWN_ERROR,
};

struct Error {
    ErrorCode code;
    QString message;

    static Error success() {
        return {ErrorCode::SUCCESS, "Success"};
    }

    bool isSuccess() const {
        return code == ErrorCode::SUCCESS;
    }
};

// QString errorMessage(ErrorCode code) {
//     switch (code) {
//     case ErrorCode::SUCCESS:
//         return "Success";
//     case ErrorCode::OUT_OF_MEMORY:
//         return "Out of memory";
//     case ErrorCode::INVALID_ARGUMENT:
//         return "Invalid argument";
//     case ErrorCode::FILE_NOT_FOUND:
//         return "File not found";
//     case ErrorCode::UNKNOWN_ERROR:
//         return "Unknown error";
//     default:
//         return "Unrecognized error";
//     }
// }

}

#endif // ERRORS_H
