#include <iostream>
#include <vector>
#include <map>
#include <set>

/**
 * @brief Return the number of ones in the binary representation
 * of an integer using Brian-Kernighan's algorithm
 *
 * @param x
 * @return int
 */
int countOnesInBinaryRepresentation(int x)
{
    if (x < 0)
    {
        return -1;
    }
    else
    {
        int ones = 0;
        while (x != 0)
        {
            x &= (x - 1);
            ones++;
        }
        return ones;
    }
}

/**
 * @brief Convert an integer into its binary representation
 * of fixed length n
 *
 * @param x
 * @param n
 * @param fixedWidthBinaryRepresentation
 */
std::string convertToBinary(int x, int n)
{
    std::string fixedWidthBinaryRepresentation = "";
    for (int i = 0; i < n; i++)
    {
        if (x != 0)
        {
            if (x % 2 == 1)
            {
                fixedWidthBinaryRepresentation = '1' + fixedWidthBinaryRepresentation;
            }
            else
            {
                fixedWidthBinaryRepresentation = '0' + fixedWidthBinaryRepresentation;
            }
            x /= 2;
        }
        else
        {
            fixedWidthBinaryRepresentation = '0' + fixedWidthBinaryRepresentation;
        }
    }
    return fixedWidthBinaryRepresentation;
}

/**
 * @brief Compute the Hamming distance between two strings
 * of the same length
 *
 * @param a
 * @param b
 * @param n
 * @return int
 */
int computeHammingDistance(std::string a, std::string b)
{
    int hammingDistance = 0;
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] != b[i])
        {
            hammingDistance++;
        }
    }
    return hammingDistance;
}

/**
 * @brief Find the position at which two character
 * sequences differ. This intended use of this
 * function is with bit strings differing by a
 * single character. If used in general, it will
 * return the first position of difference
 *
 * @param a
 * @param b
 * @return int
 */
int findPositionOfDifference(std::string a, std::string b)
{
    int index = 0;
    while (a[index] == b[index])
    {
        index++;
    }
    return index;
}

std::vector<int> mergeVectors(std::vector<int> a, std::vector<int> b)
{
    std::vector<int> c;
    for (auto x : a) 
    {
        c.push_back(x);
    }
    for (auto x : b)
    {
        c.push_back(x);
    }
    return c;
}

void groupImplicants(std::vector<int> groups[], int n, int minterms[], int mintermCount, std::vector<std::string> &binary, std::vector<std::vector<int>>& implicants)
{
    std::set<int> used;
    for (int i = 0; i < n; i++)
    {
        for (auto x : groups[i])
        {
            for (auto y : groups[i + 1])
            {
                std::string xBinary = convertToBinary(x, n);
                std::string yBinary = convertToBinary(y, n);
                int hamming = computeHammingDistance(xBinary, yBinary);
                if (hamming == 1)
                {
                    int index = findPositionOfDifference(xBinary, yBinary);
                    std::string key = xBinary;
                    key[index] = '-';
                    binary.push_back(key);
                    std::vector<int> a(1, x);
                    std::vector<int> b(1, y);
                    implicants.push_back(mergeVectors(a, b));
                    used.insert(x);
                    used.insert(y);
                }
            }
        }
    }

    // Add minterms that have not been grouped
    for (int i = 0; i < mintermCount; i++)
    {
        if (used.find(minterms[i]) == used.end()) 
        {
            binary.push_back(convertToBinary(minterms[i], n));
            std::vector<int> a(1, minterms[i]);
            implicants.push_back(a);
        }
    }
}

bool isGrouping(std::vector<std::string> binary)
{
    for (int i = 0; i < binary.size(); i++)
    {
        for (int j = 0; j < binary.size() && j != i; j++)
        {
            int hamming = computeHammingDistance(binary[i], binary[j]);
            if (hamming == 1)
            {
                return true;
            }
        }
    }
    return false;
}

void groupAll(std::vector<std::string> &binary, std::vector<std::vector<int>> &implicants, std::vector<std::string> &finalBinary, std::vector<std::vector<int>> &finalImplicants)
{
    std::set<int> used;
    while (isGrouping(binary))
    {
        for (int i = 0; i < binary.size(); i++)
        {
            for (int j = 0; j < binary.size() && j != i; j++)
            {
                int hamming = computeHammingDistance(binary[i], binary[j]);
                if (hamming == 1)
                {
                    int index = findPositionOfDifference(binary[i], binary[j]);
                    std::string key = binary[i];
                    key[index] = '-';
                    finalBinary.push_back(key);
                    finalImplicants.push_back(mergeVectors(implicants[i], implicants[j]));
                    used.insert(i);
                    used.insert(j);
                }
            }
        }
        for (int i = 0; i < binary.size(); i++)
        {
            if (used.find(i) == used.end())
            {
                finalBinary.push_back(binary[i]);
                finalImplicants.push_back(implicants[i]);
            }
        }
        used.clear();
        binary.clear();
        implicants.clear();
        binary = finalBinary;
        for (int i = 0; i < implicants.size(); i++)
        {
            implicants[i] = finalImplicants[i];
        }
    }
}

void printGrouping(std::vector<std::string> binary, std::vector<std::vector<int>> implicants)
{
    for (int i = 0; i < binary.size(); i++)
    {
        std::cout << binary[i] << ": ";
        for (auto x : implicants[i])
        {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}

int main(int argc, char **argv)
{
    int n = 4, mintermCount = 10;
    // int minterms[] = {4, 8, 9, 10, 11, 12, 14, 15};
    // int minterms[] = {0, 3, 4, 15};
    int minterms[] = {0, 1, 2, 3, 6, 7, 8, 12, 13, 15};

    std::vector<int> groupedByOnes[5];
    for (int i = 0; i < mintermCount; i++)
    {
        int ones = countOnesInBinaryRepresentation(minterms[i]);
        groupedByOnes[ones].push_back(minterms[i]);
    }

    std::vector<std::vector<int>> implicants;
    std::vector<std::string> binary;
    groupImplicants(groupedByOnes, n, minterms, mintermCount, binary, implicants);
    // printGrouping(binary, implicants);

    std::vector<std::vector<int>> finalImplicants;
    std::vector<std::string> finalBinary;
    groupAll(binary, implicants, finalBinary, finalImplicants);
    printGrouping(finalBinary, finalImplicants);
}