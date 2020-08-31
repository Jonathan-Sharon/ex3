#include "ErrorCode.h"
#include "MatrixErrorCode.hpp"
#include <exception>

MatrixErrorCode::MatrixErrorCode(ErrorCode err){

    m_err = err;
}

const char* MatrixErrorCode::what() const noexcept{

    return error_getErrorMessage(m_err);
}
