// Contains constants for error codes in application

#ifndef ERROR_ENUM_H
#define ERROR_ENUM_H

enum ErrorCodes{
    libsodiumFail = -1000,
    fileError,
    encryptionError,
    decryptionError,
    integrityError
};

#endif // ERROR_ENUM_H