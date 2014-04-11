#ifndef KD_TREE_H
#define KD_TREE_H

template <class T>
class KD_Point {
    public:
        T x, y;

        KD_Point() {}
        KD_Point(T a, T b): x(a), y(b) {}
};

class KD_Tree {

    public:

        KD_Tree() {
            point_set.resize(0);
        } // should be inline? template is strange
        ~KD_Tree() {
            point_set.clear();
        }

        bool readPoints(const int &mode=READ_MODE);

        void readPointsFromFile();
        void readPointsByInteractive();
        void readPointsFromCMD();

        std::vector< KD_Point<double> > point_set;
        int number;
};

#endif
