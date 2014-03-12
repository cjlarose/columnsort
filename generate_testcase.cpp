#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);

    for (int i = 0; i < n; ++i)
        std::cout << random() << "\n";
    return 0;
}
