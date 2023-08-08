#include <fstream>
#include <string>
#include <windows.h>
#include "MovingPictures.h"
using namespace std;

auto readFile(std::string_view path) -> std::string 
{
    constexpr auto read_size = std::size_t(4096);
    auto stream = std::ifstream(path.data());
    stream.exceptions(std::ios_base::badbit);

    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(& buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}
  
void clearScreen() 
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
    
}


void images(vector<string> imagesArray)
{
  
  for (int i = 0; i < imagesArray.size(); i++)
  {
    clearScreen();
    cout << imagesArray[i] << endl;
    cout << "Can you see me?" << endl;
    _sleep(100);
  }

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  
  SetConsoleTextAttribute(hConsole,
    FOREGROUND_RED);
  printf("red text\n");

  SetConsoleTextAttribute(hConsole,
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
  printf("white text\n");

}

