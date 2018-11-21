#include "utils.h"
#include <windows.h>

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
    // Don't forget to add the last element
    tokens.push_back(data);
    // Return the vector which contains the split string
    return tokens;
}

/**
 * METHOD
 *
 * @brief exePath : return the exe path
 * @return
 */
string exePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    return string(buffer).substr(0, pos);
}
