// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#ifndef IO_JSON_HPP_
#define IO_JSON_HPP_

#include <nlohmann/json.hpp>
#include <string>

namespace foundation {
namespace core {

using Json = nlohmann::json;

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

}  // namespace io
}  // namespace foundation

#endif  // IO_JSON_HPP_