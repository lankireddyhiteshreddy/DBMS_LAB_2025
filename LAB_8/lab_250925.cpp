// Simple, easy-to-type C++ version of the original FD / key finder
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct FD
{
    string left;
    string right;
};

string attributes; // e.g. "ABC"
vector<FD> fds;    // list of functional dependencies

// compute closure of a set (subset) under fds
string closure(const string &subset)
{
    string res = subset; // start with given attributes
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (const auto &fd : fds)
        {
            // check if all chars of fd.left are in res
            bool lhs_in = true;
            for (char a : fd.left)
                if (res.find(a) == string::npos)
                {
                    lhs_in = false;
                    break;
                }
            if (lhs_in)
            {
                for (char b : fd.right)
                {
                    if (res.find(b) == string::npos)
                    {
                        res.push_back(b);
                        changed = true;
                    }
                }
            }
        }
    }
    return res;
}

// check if subset is a superkey (closure contains all attributes)
bool isSuperKey(const string &subset)
{
    string c = closure(subset);
    for (char a : attributes)
        if (c.find(a) == string::npos)
            return false;
    return true;
}

// find and print superkeys and candidate keys
void findKeys()
{
    int n = (int)attributes.size();
    int total = 1 << n;
    vector<string> superKeys;

    cout << "\nSuper Keys:\n";
    for (int mask = 1; mask < total; ++mask)
    {
        string subset;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                subset.push_back(attributes[i]);
        if (isSuperKey(subset))
        {
            cout << subset << ' ';
            superKeys.push_back(subset);
        }
    }

    cout << "\n\nCandidate Keys:\n";
    for (size_t i = 0; i < superKeys.size(); ++i)
    {
        bool minimal = true;
        for (size_t j = 0; j < superKeys.size(); ++j)
        {
            if (i == j)
                continue;
            if (superKeys[j].size() < superKeys[i].size())
            {
                // check if superKeys[j] is subset of superKeys[i]
                bool allIn = true;
                for (char c : superKeys[j])
                    if (superKeys[i].find(c) == string::npos)
                    {
                        allIn = false;
                        break;
                    }
                if (allIn)
                {
                    minimal = false;
                    break;
                }
            }
        }
        if (minimal)
            cout << superKeys[i] << ' ';
    }
    cout << '\n';
}

int main()
{
    // Example 1
    cout << "Example 1:\n";
    attributes = "XYZW";
    fds.clear();
    fds.push_back({"XYZ", "W"});
    fds.push_back({"XY", "ZW"});
    fds.push_back({"X", "YZW"});
    findKeys();

    // Example 2
    cout << "\nExample 2:\n";
    attributes = "XYZW";
    fds.clear();
    fds.push_back({"X", "Y"});
    fds.push_back({"Y", "Z"});
    fds.push_back({"Z", "X"});
    findKeys();

    return 0;
}
