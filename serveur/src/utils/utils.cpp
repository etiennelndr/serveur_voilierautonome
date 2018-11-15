#include "utils.h"

/**
 * METHOD
 *
 * @brief split : split a string into multiple strings
 * @param data
 * @param delimiter
 * @return
 */
vector<string> split(string data, string delimiter) {
    vector<string> tokens;
    size_t pos = 0;
    while ((pos = data.find(delimiter)) != string::npos) {
        tokens.push_back(data.substr(0, pos));
        data.erase(0, pos + delimiter.length());
    }
    return tokens;
}
