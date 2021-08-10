#include<iostream>
#include<ctime>
#include <string>

#include "functions.h"


using namespace std;


int main()
{
    ShowInstructions();

    if (ConfigurePlayers() == false)
    {
        //Program ends if number of players is not ok
        return 1;
    }

    do{
        Round();
        ShowPlayersScore();
    } while(EndGameQuestion() == false);

    system("pause");
}



















