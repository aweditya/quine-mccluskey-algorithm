#include <iostream>
#include <vector>
#include <map>

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

void groupImplicants(std::vector<int> groups[], int n)
{
    std::vector<std::string> binary;
    std::vector<std::vector<int>> implicants;
    // groups has 5 rows: 0, 1, 2, 3, 4
    for (int i = 0; i < n; i++)
    {
        for (auto x : groups[i])
        {
            bool used = false;
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
                    std::vector<int> pair;
                    pair.push_back(x);
                    pair.push_back(y);
                    implicants.push_back(pair);

                    used = true;
                }
            }
            if (!used)
            {
                binary.push_back(convertToBinary(x, n));
                std::vector<int> implicant(1, x); 
                implicants.push_back(implicant);
            }
        }
    }

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
    int n = 4, mintermCount = 8;
    int minterms[] = {4, 8, 9, 10, 11, 12, 14, 15};
    // int minterms[] = {0, 3, 4, 15};

    std::vector<int> groupedByOnes[5];
    for (int i = 0; i < mintermCount; i++)
    {
        int ones = countOnesInBinaryRepresentation(minterms[i]);
        groupedByOnes[ones].push_back(minterms[i]);
    }

    groupImplicants(groupedByOnes, n);
}