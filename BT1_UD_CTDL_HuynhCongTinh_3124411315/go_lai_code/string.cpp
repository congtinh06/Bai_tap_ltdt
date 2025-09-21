#include <iostream>
#include <string>
using namespace std;

int main() {
    string a = "acm icpc world";

    cout << a.size() << " ";               // 14
    cout << !a.empty() << " ";             // 1

    a += " final";                         // "acm icpc world final"
    a.push_back('.');                      // "acm icpc world final."

    cout << a.find("icpc") << " ";         // 4
    cout << (a.find("acm", 5) == string::npos) << " "; // 1
    cout << a.find_first_of("ijk") << " "; // 4
    cout << a.find_first_not_of("abcde") << " "; // 2
    cout << a.find_first_of(' ', 4) << " ";       // 8

    string b = a.substr(4, 4);             // "icpc"
    string c = a.substr(15);               // "final."

    a.insert(a.size() - 1, " 2010");       // "acm icpc world final 2010."
    a.erase(14);                           // "acm icpc world final"
    a.replace(9, a.size() - 9, "WF");      // "acm icpc WF"
    a.erase(3);                            // "acm"

    printf("%s\n", a.c_str());

    return 0;
}

