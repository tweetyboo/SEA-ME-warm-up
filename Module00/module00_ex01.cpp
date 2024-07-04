#include <iostream>
#include <string>
using namespace std;

class StringConverter
{
public:
    void ToUpperCase(const string& s)
    {
        for (auto &x : s)
            cout << (char)toupper(x);
    }
    void ToLowerCase(const string& s)
    {
        for (auto &x : s)
            cout << (char)tolower(x);
    }
};

int main(int argc, char **argv)
{

    StringConverter str;
    
    // Check whether the input parameters are atleast 3
    if (argc < 3)
    {
        cout << "Input required as output_file {command} {string}" << endl;
        return 1;
    }

    string command = argv[1];
    int i = 2;

    for (i = 2; i < argc; ++i)
    {
        string input = argv[i];
        if (command == "up")
            str.ToUpperCase(input);
        else if (command == "down")
            str.ToLowerCase(input);
        else
        {
            cout << "Expected Commands Up or down" << endl;
            break;
        }
        if (i < argc - 1) // Add space only between words
            cout << " ";
    }
    cout << '\n'; // New line denoting end of the string
    return 0;
}
