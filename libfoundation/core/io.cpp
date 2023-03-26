// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include <libfoundation/core/io.hpp>
#include <fstream>

namespace foundation {
namespace core {

Json loadJson(const std::string& filename) {
    // create filestream
    std::ifstream file_stream(filename);
    // stream into json object
    Json json_obj;
    file_stream >> json_obj;    
    return json_obj;
}

void saveJson(const Json& json, const std::string& filename) {
    std::ofstream ostream(filename);
    ostream << json;
}

}  // namespace io
}  // namespace libhedral