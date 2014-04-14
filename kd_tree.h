#ifndef KD_TREE_H
#define KD_TREE_H

template <class T>
class KD_Point {
    public:
        T x, y;

        KD_Point() {}
        KD_Point(T a, T b): x(a), y(b) {}
        KD_Point(const KD_Point &p) { *this = p; }
        
        KD_Point & operator =(const KD_Point &p) { 
            x = p.x;
            y = p.y;
            return *this; 
        }

        bool operator ==(const KD_Point &p) {
            return fabs(x - p.x) < EPSILON && fabs(y - p.y) < EPSILON;
        }

        void print() const{
            std::cout << "(" << x << ", " << y << ")." << std::endl;
        }

        /*friend bool cmp_x(KD_Point p, KD_Point q) {
            return p.x > q.x;
        }

        friend bool cmp_y(KD_Point p, KD_Point q) {
            return p.y > q.y;
        }*/
};

class Node {

    public:
        Node();
        Node(const KD_Point<double> &);

        KD_Point<double> mark_point; // maintain the split point
        Node * lc, * rc; // maintain the children
        int depth; // maintain the depth
        KD_Point<double> tl, br;// maintain the region
        int size; // number of points in the region
};

class KD_Tree {

    public:

        KD_Tree();
        ~KD_Tree();

        bool readPoints(const int &mode=READ_MODE);

        void readPointsFromFile();
        void readPointsByInteractive();
        void readPointsFromCMD();

        void build();
        Node * buildTree(int, int, int, KD_Point<double> &, KD_Point<double> &);
        void find_median(const int &, const int &, const int &, const int &, bool (cmp)(KD_Point<double>, KD_Point<double>));

        std::vector< KD_Point<double> > search(const KD_Point<double> &, const KD_Point<double> &) const;
        void searchTree(const Node *, std::vector< KD_Point<double> > &, const KD_Point<double> &, const KD_Point<double> &) const;
        void reportSubTree(const Node *, std::vector< KD_Point<double> > &) const;

        void search_test();
        void traverse_test(const Node *);

        std::vector< KD_Point<double> > point_set;
        int number;
        Node * root;
        KD_Point<double> tl, br;// region, the tree contains
};

#endif
