#include <iostream>
#include <string>

int main()

{
    double d;
    std::string s = "1.6";
    d= std::stod(s);
    std::cout << "The double value is: " << d << std::endl;

    try
    {
        d=std::stod(s);
    }
    catch(const std::exception& e)
    {
       
    }
            std::cout << "d:"<< d << std::endl;
}


int main()
{
    std::string s ="Anshu";
    std::cout<<"length of string is: " << s.length() << std::endl;
    s="Something else";
    std::cout<<"length of string is: " << s.length() << std::endl;

    std::stod("10");
    
}