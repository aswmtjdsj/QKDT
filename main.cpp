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
    kdt.build();

    return 0;
}
