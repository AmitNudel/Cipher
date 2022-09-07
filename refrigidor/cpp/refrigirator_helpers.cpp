#include <iostream>
#include <string>
#include <unistd.h>
void SettingEnd();

int UserPrompt()
{
    std::string answer;
    std::cout << "Hello dear user, would you like to change the light manually or automatically?"<<std::endl;
    std::cin >> answer;
    return "manually" == answer ? 0 : 1;
}

void ManualLightSpeedChange()
{
    std::string answer;
    std::cout<<"Please tell me at what speed you want to set the settings to:"<<std::endl;
    std::cin >> answer;
    SettingEnd();

}

void AutomaticLightSpeedChange()
{
    std::string answer;
    std::cout<<"Please look at the flickering light"<<std::endl;
    do
    {
        std::cout<<"Flick flick..."<<std::endl;
        std::cout<<"Was it fast or slow?"<<std::endl;
        std::cin >> answer;
    } while ( "ok" != answer);
    
    SettingEnd();
    
}

void SettingEnd()
{
    std::cout<<"Setting the wanted speed"<<std::endl;
    sleep(1);
    std::cout<<"Setting complete"<<std::endl;
} 