#include "common.h"
#include "kd_tree.h"

using namespace std;

int main(int argc, char ** argv) {
    KD_Tree kdt;
    if(argc > 1) {
        int opt = atoi(argv[1]);
        kdt.readPoints(opt);
    }
    else {
        kdt.readPoints();
    }
    cout << "Point Set Read!" << endl;
    kdt.build();
    cout << "KD-tree built!" << endl;

    cout << "Test Begin!" << endl;
    kdt.search_test();

    return 0;
}
