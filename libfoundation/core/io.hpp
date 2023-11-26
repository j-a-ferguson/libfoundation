// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#ifndef IO_JSON_HPP_
#define IO_JSON_HPP_

#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <fmt/format.h>
#include <string>

namespace foundation {
namespace core {

using Json = nlohmann::json;
using namespace fmt;

/** @brief Reads Json from file
    @param filename The name of the file
    @return A Json object with contents of file.
*/
Json loadJson(const std::string& filename);

/** @brief Writes Json object to file.
    @param json A Json object to save.
    @param filename Name of the file to which to write.
*/
void saveJson(const Json& json, const std::string& filename);


template <typename T>
concept HasToJson = requires(const T& a, Json& json)
{
    {a.toJson(json)} -> std::same_as<void>;
};

template <typename T>
concept HasFromJson = requires(T& a, const Json& json)
{
    {a.toJson(json)} -> std::same_as<void>;
};



}  // namespace io
}  // namespace foundation

#endif  // IO_JSON_HPP_