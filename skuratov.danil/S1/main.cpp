#include <iostream>
#include <sstream>
#include <vector>
#include <numeric>
#include "sequence.hpp"
#include "list.hpp"

int main()
{
    using namespace skuratov;
    std::vector<Sequence> sequences;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (!line.empty())
        {
            std::istringstream iss(line);
            std::string name;
            iss >> name;
            Sequence sequence(name);
            int num = {};
            while (iss >> num)
            {
                sequence.numbers().push_back(num);
            }
            sequences.push_back(sequence);
        }
    }

    for (const auto& seq : sequences)
    {
        std::cout << seq.name() << " ";
    }
    std::cout << '\n';

    size_t maxSize = 0;
    for (const auto& seq : sequences)
    {
        maxSize = std::max(maxSize, seq.numbers().size());
    }

    // ������� ������������������ �� ��������
    for (size_t i = 0; i < maxSize; ++i) {
        // ��� ������� ������� ������� �������� �� ���� �������������������
        for (const auto& seq : sequences) {
            const auto& numbers = seq.numbers();
            if (i < numbers.size()) {
                std::cout << numbers[i] << " ";
            }
        }
        std::cout << '\n';
    }


    // ������, �������� ����� ��������� �� ��������
    std::vector<int> column_sums(maxSize, 0);

    // ��������� �������� �� ��������
    for (size_t i = 0; i < maxSize; ++i)
    {
        for (const auto& seq : sequences)
        {
            const auto& numbers = seq.numbers();
            if (i < numbers.size())
            {
                column_sums[i] += numbers[i];
            }
        }
    }

    // ������� ����� ��������� �� ��������
    for (const auto& sum : column_sums)
    {
        std::cout << sum << " ";
    }
    std::cout << '\n';

    return 0;
}
