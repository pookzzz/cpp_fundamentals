#include <iostream>

using namespace std;

int main()
{
    int planetCount = 8;

    bool extraPlanet = true;

    if (extraPlanet){
        planetCount++;
    }

    cout << "Greetings all " << planetCount << " Planets" << endl;
    return 0;
}
