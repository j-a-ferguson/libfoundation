// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#ifndef ASSERTIONS_HPP_
#define ASSERTIONS_HPP_

namespace foundation {
namespace core {


#define ERR_FILE2_m std::string(__FILE__)
#define ERR_FILE_m ERR_FILE2_m
#define ERR_LINE2_m std::to_string(__LINE__)
#define ERR_LINE_m ERR_LINE2_m

#define ERR_ASSERT_THROW_m(cond, exception, msg)\
if(!(cond)) {throw exception("\nError in " + ERR_FILE_m + ":" + ERR_LINE_m + "\nMessage: " + msg);}    

#define ERR_ASSERT_THROW_INVARG_m(cond, msg) ERR_ASSERT_THROW_m(cond, std::invalid_argument, msg)
#define ERR_ASSERT_THROW_LENGTH_m(cond, msg) ERR_ASSERT_THROW_m(cond, std::length_error, msg)
#define ERR_ASSERT_THROW_RANGE_m(cond, msg)  ERR_ASSERT_THROW_m(cond, std::out_of_range, msg)
}
}


#endif