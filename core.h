#include <iostream>
#include <map>
#include <vector>
#include <set>

class QuineMcCluskey 
{
private:
    int countOnesInBinaryRepresentation(int x);
    std::string convertToBinary(int x, int n);
    int computeHammingDistance(std::string a, std::string b);
    int findPositionOfDifference(std::string a, std::string b);
    std::vector<int> mergeVectors(std::vector<int> a, std::vector<int> b);

public:
    void groupByOnes(std::vector<int> minterms, int n, std::vector<std::vector<int>> &groupedByOnes);
    void groupImplicants(std::vector<std::vector<int>> groups, int n, std::vector<int> minterms, std::vector<std::string> &binary, std::vector<std::vector<int>> &implicants);
    bool isGrouping(std::vector<std::string> binary);
    void groupAll(std::vector<std::string> &binary, std::vector<std::vector<int>> &implicants, std::vector<std::string> &finalBinary, std::vector<std::vector<int>> &finalImplicants);
    void printGrouping(std::vector<std::string> binary, std::vector<std::vector<int>> implicants);
    void removeDuplicates(std::vector<std::string> binary, std::vector<std::vector<int>> implicants, std::map<std::string, std::vector<int>> &uniqueImplicants);
    void printMap(std::map<std::string, std::vector<int>> map);
    std::vector<std::string> identifyEPI(std::map<std::string, std::vector<int>> implicants, std::vector<int> minterms, int n);
};