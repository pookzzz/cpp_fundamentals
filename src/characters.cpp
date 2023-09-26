#include <iostream>

using namespace std;

int main()
{
    char myChar = 65;
    for (int i = 0; i < 256; i++)
    {
        myChar = (char)i;
        cout << "The character for " << i << " is " << myChar << endl;
    }

    return 0;
}