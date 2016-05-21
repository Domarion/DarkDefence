#pragma once

#include <string>

using std::string;


namespace androidText
{
    extern void setRelativePath(string& filename);
    extern void loadTextFileToString(string filename, string& destString);


}
