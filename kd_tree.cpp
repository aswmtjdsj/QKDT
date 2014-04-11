#include "common.h"
#include "kd_tree.h"

using namespace std;

bool KD_Tree::readPoints(const int &mode) {

    switch(mode) {
        case FILE_READ_MODE:
            readPointsFromFile();
            break;

        case INTERACTIVE_READ_MODE:
            readPointsByInteractive();
            break;

        case CMD_READ_MODE:
            readPointsFromCMD();
            break;
    }
    return true;
}

void KD_Tree::readPointsFromFile() {
    cout << "FILE_READ MODE" << endl;
    if(true) {
        string file_name;
        cout << "Input the name of data file>";
        cin >> file_name;
        FILE * fp = fopen(file_name.c_str(), "r");
        if(fp != NULL) {
            fscanf(fp, " %d", &number);
            printf("Number of Points: %d.\n", number);
            point_set.resize(number);
            for(int i = 0; i < number; i++) {
                fscanf(fp, " %lf %lf", &point_set[i].x, &point_set[i].y);
            }
            for(int i = 0; i < number; i++) {
                printf("Point [%d]: (%f, %f).\n", i, point_set[i].x, point_set[i].y);
            }
        }
        else {
            cout << "No such file: " << file_name << endl;
            exit(1);
        }
    }
}

void KD_Tree::readPointsByInteractive() {
    cout << "INTER_READ MODE" << endl;
}

void KD_Tree::readPointsFromCMD() {
    cout << "CMD_READ MODE" << endl;
    if(true) { // need modification
        /*fprintf(stdout, "Number of Points>\n");
        fflush(stdout);
        fscanf(stdin, " %d", &number);
        fprintf(stdout, "Points: %d\n", number);
        fflush(stdout);*/
        cout << "Number of Points>";
        cin >> number;
        point_set.resize(number);
        for(int i = 0; i < number; i++) {
            cin >> point_set[i].x >> point_set[i].y;
        }
        for(int i = 0; i < number; i++) {
            cout << "Point [" << i << "]: (" << point_set[i].x << ", " << point_set[i].y << ").\n";
        }
    }
}
