#ifndef GOL_SRC_UTIL_H_
#define GOL_SRC_UTIL_H_

#include <cstdint>
#include <string>
#include <tuple>

namespace gol {
// Describe input file
void aboutInputFile();
// Print CLI usage 
void cliUsage();
// Parse CLI inputs
std::tuple<std::string, std::int64_t, std::uint8_t> parseCliArgs(int, char **);

} // namespace gol

#endif

