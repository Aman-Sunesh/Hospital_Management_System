#ifndef GENERATEACCOUNT_H
#define GENERATEACCOUNT_H

#include <string>
#include <vector>

using namespace std;

class GenerateAccount
{
private:
    static vector<int> IDList;
    static vector<string> passwordList;

public:

    // Function to generate a unique ID
    static int generateUniqueID();

    // Function to generate a random password
    static string generatePassword();
};

#endif // GENERATEACCOUNT_H