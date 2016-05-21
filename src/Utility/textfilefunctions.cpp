#include "textfilefunctions.h"
#include <SDL_rwops.h>
namespace androidText
{


void loadTextFileToString(string filename, string& destString)
   {
       SDL_RWops* ooops =SDL_RWFromFile(filename.c_str(),"rt");


       if (ooops != nullptr)
       {
           size_t file_length = SDL_RWseek(ooops, 0, SEEK_END);
           char* destination = new char[file_length + 1];
            SDL_RWseek(ooops, 0, SEEK_SET);
           int bytes =SDL_RWread(ooops, (destination), 1, file_length);
           destination[file_length] ='\0';


           destString.assign(destination);

           delete[] destination;
       }
       SDL_RWclose(ooops);
   }
}
