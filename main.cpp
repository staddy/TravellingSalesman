#include <iostream>
#include <math.h>
#include <set>

#include "csvdocument.h"

std::vector<std::string> tests = {
    "_5",
    "_8",
    "_10",
    "_14",
};

std::vector<size_t> findOptimalPath(const std::vector<std::vector<double> >& matrix) {
    return {};
}

int main(int /*argc*/, char* /*argv*/[]) {
    for (const auto& test : tests) {
        CsvDocument testCsv(';');
        testCsv.load(std::string("test") + test + ".csv");
        std::vector<std::vector<double> > matrix;
        for (size_t i = 0; i < testCsv.size(); ++i) {
            matrix.emplace_back();
            for (size_t j = 0; j < testCsv.size(); ++j) {
                matrix[i].push_back(std::sqrt(std::pow(testCsv[j][0].toDouble()
                                              - testCsv[i][0].toDouble(), 2)
                        + std::pow(testCsv[j][1].toDouble()
                        - testCsv[i][1].toDouble(), 2)));
            }
        }
        auto path = findOptimalPath(matrix);
        CsvDocument resultCsv(';');
        resultCsv.load(std::string("result") + test + ".csv");
        if (path.empty() || (resultCsv.size() > path.size())) {
            std::cout << "test" << test << ": FAIL\n";
            continue;
        }
        std::set<std::pair<size_t, size_t> > edges;
        auto prev = path.back();
        for (size_t i = 0; i < resultCsv.size(); ++i) {
            edges.emplace(prev, path[i]);
            prev = path[i];
        }
        auto ok = true;
        prev = resultCsv[resultCsv.size() - 1][0].toUnsignedLongLong();
        for (size_t i = 0; i < resultCsv.size(); ++i) {
            if (edges.find(std::pair<size_t, size_t>(prev, resultCsv[i][0].toUnsignedLongLong())) == edges.end() &&
                    edges.find(std::pair<size_t, size_t>(resultCsv[i][0].toUnsignedLongLong(), prev)) == edges.end()) {
                std::cout << "test" << test << ": FAIL\n";
                ok = false;
                break;
            }
            prev = resultCsv[i][0].toUnsignedLongLong();
        }
        if (ok) {
            std::cout << "test" << test << ": OK\n";
        }
    }
    return 0;
}
