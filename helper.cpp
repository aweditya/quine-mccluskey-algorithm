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
 * @brief Compute the Hamming distance between two character
 * sequences of the same length
 * 
 * @param a 
 * @param b 
 * @param n 
 * @return int 
 */
int computeHammingDistance(char* a, char* b, int n)
{
    int hammingDistance = 0;
    std::cout << a << "\t" << b << "\n";
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
        {
            hammingDistance++;
        }
    }
    return hammingDistance;
}

/**
 * @brief Convert an integer into its binary representation
 * of fixed length n
 * 
 * @param x 
 * @param n 
 * @param fixedWidthBinaryRepresentation 
 */
void convertToBinary(int x, int n, char fixedWidthBinaryRepresentation[])
{
    for (int i = n - 1; i >= 0; i--)
    {
        if (x != 0)
        {
            if (x % 2 == 1)
            {
                fixedWidthBinaryRepresentation[i] = '1';
            }
            else 
            {
                fixedWidthBinaryRepresentation[i] = '0';
            }
            x /= 2;
        }
        else 
        {
            fixedWidthBinaryRepresentation[i] = '0';
        }
    }
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
int positionOfDifference(char* a, char* b)
{
    int index = 0;
    while(a[index] == b[index])
    {
        index++;
    }
    return index;
}

std::map<std::string, std::vector<int> > groupImplicants(std::vector <int> groups[], int n)
{
    std::map<std::string, std::vector<int> > groupedImplicants;
    return groupedImplicants;
}

int main(int argc, char** argv)
{
    int n = 4;
    int minterms[] = {4, 8, 9, 10, 11, 12, 14, 15};

    std::cout << "Minterms: ";
    for (int i = 0; i < 8; i++)
    {
        std::cout << minterms[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Testing convertToBinary():\n";
    char binaryOf4[5], binaryOf6[5];
    convertToBinary(4, 4, binaryOf4);
    convertToBinary(6, 4, binaryOf6);
    std::cout << "Binary representation of 4: " << binaryOf4 << "\n";

    std::cout << "Testing computeHammingDistance()\n";
    std::cout << "Hamming distance between 4 and 6: " << computeHammingDistance(binaryOf4, binaryOf6, 4) << "\n";

    std::cout << "Testing positionOfDifference()\n";
    std::cout << "Position of difference for 4 and 6: " << positionOfDifference(binaryOf4, binaryOf6) << "\n";

    std::cout << "Testing grouping by number of ones in binary representation:\n";
    std::vector<int> groupedByOnes[5];
    for (int i = 0; i < 8; i++)
    {
        int ones = countOnesInBinaryRepresentation(minterms[i]);
        groupedByOnes[ones].push_back(minterms[i]);
    }

    std::cout << "Grouping minterms by number of ones in bitstring:\n";
    for (int i = 0; i <= n; i++)
    {
        std::cout << i << ": ";
        for (auto x : groupedByOnes[i])
        {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}