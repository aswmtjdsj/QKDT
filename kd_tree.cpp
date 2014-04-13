#include "common.h"
#include "kd_tree.h"

using namespace std;

Node::Node():lc(NULL), rc(NULL) {
}

Node::Node(const KD_Point<double> &pt):mark_point(pt), lc(NULL), rc(NULL) {
}

KD_Tree::KD_Tree() {
    point_set.resize(0);
    root = NULL;
} 

KD_Tree::~KD_Tree() {
    point_set.clear();
    // root = NULL;
}

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

bool cmp_x(KD_Point<double> p, KD_Point<double> q) {
    return p.x > q.x;
}

bool cmp_y(KD_Point<double> p, KD_Point<double> q) {
    return p.y > q.y;
}

void KD_Tree::build() {
    root = buildTree(0, point_set.size() - 1, 0);
}

Node * KD_Tree::buildTree(int lp, int rp, int depth) {
    /*
     * lp denotes left pointer in the array of points
     * rp denotes right pointer in the array
     * depth denotes the depth of the tree
     */

    if(lp < rp) {
        int m = (lp + rp) / 2;
        if(depth % 2 == 0) { // even, split into left and right, based on x-cor
            find_median(lp, rp, lp, rp-lp, cmp_x); // 4th param should be offset, so that st_index+offset==end_index, not number of elements in the selected range
        }
        else { // odd
            find_median(lp, rp, lp, rp-lp, cmp_y);
        }

        /*// test
        for(int i = lp; i <= rp; i++) {
            printf("biu [%d]: ", i);
            point_set[i].print();
        }
        KD_Point<double> temp = point_set[m];
        if(depth % 2 == 0) {
            sort(point_set.begin() + lp, point_set.begin() + rp + 1, cmp_x);
            reverse(point_set.begin() + lp, point_set.begin() + rp + 1);
        }
        else {
            sort(point_set.begin() + lp, point_set.begin() + rp + 1, cmp_y);
            reverse(point_set.begin() + lp, point_set.begin() + rp + 1);
        }
        for(int i = lp; i <= rp; i++) {
            printf("test [%d]: ", i);
            point_set[i].print();
        }
        puts("");
        if(!(point_set[m] == temp)) {
            printf("fuck: %d\n", depth);
            exit(1);
        }*/

        Node * cur = new Node(point_set[m]);
        cur->lc = buildTree(lp, m, depth+1);
        cur->rc = buildTree(m + 1, rp, depth+1);
        return cur;
    }
    else {
        // only one point left
        return new Node(point_set[lp]);
    }
}

void KD_Tree::find_median(const int & lp, const int & rp, const int &index, const int &n, bool (cmp)(KD_Point<double>, KD_Point<double>)) {

    if(lp < rp) {
        int m = rand()%(rp-lp+1) + lp;
        swap(point_set[m], point_set[rp]); // random swap
        int j = lp;
        for(int i = lp; i < rp; i++) {
            if(!(cmp(point_set[i], point_set[rp]))) {
                swap(point_set[i], point_set[j]);
                j++;
            }
        }
        swap(point_set[j], point_set[rp]);
        if(j == index + n/2) { // such procedure doesn't start from current lp, nor 0; it starts from the first lp
            /*printf("FUCKKKKK %d j: %d middle: %d\n", m, j, index + n/2);
            for(int i = index; i < index + n; i++) {
                printf("inner [%d]: ", i);
                point_set[i].print();
            }*/
            return ;
        }
        else if(j > index + n/2) {
            find_median(lp, j, index, n, cmp);
        }
        else {
            find_median(j + 1, rp, index, n, cmp);
        }
    }
}
