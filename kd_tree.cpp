
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
    for(int i = 0; i < number; i++) {
        if(i == 0) {
            tl = point_set[i];
            br = point_set[i];
        }
        else {
            tl.x = min(tl.x, point_set[i].x);
            tl.y = min(tl.y, point_set[i].y);
            br.x = max(br.x, point_set[i].x);
            br.y = max(br.y, point_set[i].y);
        }
    }
    cout << "Region for this point set: X[" << tl.x << ":" << br.x << "] x Y[" << tl.y << ":" << br.y << "]." << endl;
    return true;
}

void KD_Tree::readPointsFromFile() {
    /*cout << "FILE_READ MODE" << endl;
    if(true) {
        string file_name;
        cout << "Input the name of data file>";
        cin >> file_name;
        file_name = "./data/" + file_name;
        FILE * fp = fopen(file_name.c_str(), "r");
        if(fp != NULL) {
            fscanf(fp, " %d", &number);
            printf("Number of Points: %d.\n", number);
            point_set.resize(number);
            for(int i = 0; i < number; i++) {
                fscanf(fp, " %lf %lf", &point_set[i].x, &point_set[i].y);
            }
#ifdef DEBUG
            for(int i = 0; i < number; i++) {
                printf("Point [%d]: (%f, %f).\n", i, point_set[i].x, point_set[i].y);
            }
#endif
        }
        else {
            cout << "No such file: " << file_name << endl;
            exit(1);
        }
    }*/
}

void KD_Tree::readPointsByInteractive() {
    cout << "INTER_READ MODE" << endl;
    // incomplete
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

void KD_Tree::randomPoints(const int &random_total) {
	number = random_total;
	point_set.resize(number);
	std::default_random_engine generator(time(NULL));
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	for(int i = 0; i < number; i++) {
		point_set[i].x = distribution(generator);
		point_set[i].y = distribution(generator);
		point_set[i].index = i;
	}
}

bool cmp_x(KD_Point<double> p, KD_Point<double> q) {
    return p.x < q.x;
}

bool cmp_y(KD_Point<double> p, KD_Point<double> q) {
    return p.y < q.y;
}

void KD_Tree::build() {
    clock_t start = clock(), end;

    root = buildTree(0, point_set.size() - 1, 0, tl, br);
    root->tl = tl;
    root->br = br;

    end = clock();
    cout << "KD-tree build time: " << (end - start) * 1000. / CLOCKS_PER_SEC << "ms." << endl;
	build_time = (end - start) * 1000. /  CLOCKS_PER_SEC;
}

Node * KD_Tree::buildTree(int lp, int rp, int depth, KD_Point<double> &left_top, KD_Point<double> & right_bottom) {
    /*
     * lp denotes left pointer in the array of points
     * rp denotes right pointer in the array
     * depth denotes the depth of the tree
     */
#ifdef DEBUG
    printf("lp: %d, rp: %d\n", lp, rp);
    cout << "depth: " << depth << endl;
    printf("left_top & right_bottom>\n");
    left_top.print();
    right_bottom.print();
#endif

    if(lp < rp) {
        int m = (lp + rp) / 2;
#ifdef DEBUG
    cout << "Find Median!" << endl;
#endif
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

#ifdef DEBUG
        cout << "kaka" << endl; 
#endif
        Node * cur = new Node(point_set[m]);
#ifdef DEBUG
        cout << "biubiu" << endl; 
#endif

        KD_Point<double> split[2];
        if(depth%2==0) {
            // x-split
            /*
             ---------
             |   |   |
             |   |   |
             |   |   |
             |   |   |
             ---------
             */
            split[0].x = point_set[m].x;
            split[0].y = right_bottom.y;
			split[0].index = point_set[m].index;
            split[1].x = point_set[m].x;
            split[1].y = left_top.y;
			split[1].index = point_set[m].index;
        }
        else {
            // y-split
            /*
             -------
             |     |
             |     |
             -------
             |     |
             |     |
             -------
             */
            split[0].x = right_bottom.x;
            split[0].y = point_set[m].y;
			split[0].index = point_set[m].index;
            split[1].x = left_top.x;
            split[1].y = point_set[m].y;
			split[1].index = point_set[m].index;
        }

        cur->lc = buildTree(lp, m, depth+1, left_top, split[0]);
        cur->rc = buildTree(m + 1, rp, depth+1, split[1], right_bottom);

        // region split
        cur->lc->tl = left_top;
        cur->lc->br = split[0];

        cur->rc->tl = split[1];
        cur->rc->br = right_bottom;

        cur->depth = depth; // depth % 0 == 0 means x-split, otherwise y-split
        cur->size = rp - lp + 1;
        return cur;
    }
    else {
        // only one point left->leaf
        Node * cur = new Node(point_set[lp]);
        cur->depth = depth;
        cur->size = 1;
        return cur;
    }
}

void KD_Tree::find_median(const int & lp, const int & rp, const int &index, const int &n, bool (cmp)(KD_Point<double>, KD_Point<double>)) {

#ifdef DEBUG
    printf("FIND lp:%d, rp:%d\n", lp, rp);
    printf("MEDIAN %d\n", index + n / 2);
    if(rp - lp == 1) {
        for(int i = lp; i <= rp; i++) {
            point_set[i].print();
        }
    }
#endif
    if(lp < rp) {
        int m = rand()%(rp-lp+1) + lp;
        //swap(point_set[m], point_set[rp]); // random swap
		KD_Point<double> temp;
		temp.x = point_set[m].x;
		temp.y = point_set[m].y;
		temp.index = point_set[m].index;
		point_set[m].x = point_set[rp].x;
		point_set[m].y = point_set[rp].y;
		point_set[m].index = point_set[rp].index;
		point_set[rp].x = temp.x;
		point_set[rp].y = temp.y;
		point_set[rp].index = temp.index;
        int j = lp;
        for(int i = lp; i < rp; i++) {
            if((cmp(point_set[i], point_set[rp]))) { // using "<=" cannot deal with points having same coors
                swap(point_set[i], point_set[j]);
                j++;
            }
        }
        //swap(point_set[j], point_set[rp]);
		temp.x = point_set[j].x;
		temp.y = point_set[j].y;
		temp.index = point_set[j].index;
		point_set[j].x = point_set[rp].x;
		point_set[j].y = point_set[rp].y;
		point_set[j].index = point_set[rp].index;
		point_set[rp].x = temp.x;
		point_set[rp].y = temp.y;
		point_set[rp].index = temp.index;

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

vector< KD_Point<double> > KD_Tree::search(const KD_Point<double> &p, const KD_Point<double> &q) {
    vector< KD_Point<double> > result;
    clock_t start = clock(), end;
    searchTree(root, result, p, q);
    end = clock();
	query_time = (end - start) * 1000. / CLOCKS_PER_SEC;
    return result;
}

bool regionContain(const KD_Point<double> &p, const KD_Point<double> &q,
        const KD_Point<double> &a, const KD_Point<double> &b) {
        return (p.x <= a.x && a.x <= q.x
                    &&p.y <= a.y && a.y <= q.y)
                &&
                (p.x <= b.x && b.x <= q.x
                    &&p.y <= b.y && b.y <= q.y);
}

bool regionIntersect(const KD_Point<double> &p, const KD_Point<double> &q,
        const KD_Point<double> &a, const KD_Point<double> &b) {
    KD_Point<double> tp, tq;
    tp.x = max(p.x, a.x);
    tp.y = max(p.y, a.y);
    tq.x = min(q.x, b.x);
    tq.y = min(q.y, b.y);
    return !(tp.x > tq.x || tp.y > tq.y);
}

void KD_Tree::searchTree(const Node *cur, std::vector< KD_Point<double> > &ans_set, const KD_Point<double> &p, const KD_Point<double> &q) {
    if(cur->size == 1) { // leaf
        if(regionContain(p, q, cur->mark_point, cur->mark_point)) { // test in R
            /*puts("insert");
            printf("Node Region: X[%f:%f] x Y[%f:%f].\n", cur->tl.x, cur->br.x, cur->tl.y, cur->br.y);
            printf("Depth %d: %s with size: %d ", cur->depth, cur->depth%2==0?"X-split":"Y-split", cur->size);
            printf("Split Point: ");
            (cur->mark_point).print();
            printf("Query Region: X[%f:%f] x Y[%f:%f].\n", p.x, q.x, q.y, q.y);*/
            ans_set.push_back(cur->mark_point);
        }
    }
    else {
        // intersection judgement
        if(regionContain(p, q, cur->lc->tl, cur->lc->br)) {
            // region of left child contained totally in R(p, q)
            reportSubTree(cur->lc, ans_set);
        }
        else if(regionIntersect(p, q, cur->lc->tl, cur->lc->br)) {
            // region of left child intersected with R(p, q)
            searchTree(cur->lc, ans_set, p, q);
        }

        if(regionContain(p, q, cur->rc->tl, cur->rc->br)) { 
            // region of right child contained totally in R(p, q)
            reportSubTree(cur->rc, ans_set);
        }
        else if(regionIntersect(p, q, cur->rc->tl, cur->rc->br)) {
            // region of right child intersected with R(p, q)
            searchTree(cur->rc, ans_set, p, q);
        }
    }
}

void KD_Tree::reportSubTree(const Node *cur, std::vector< KD_Point<double> > &node_set) {
    /*puts("Report");
    printf("Node Region: X[%f:%f] x Y[%f:%f].\n", cur->tl.x, cur->br.x, cur->tl.y, cur->br.y);
    printf("Depth %d: %s with size: %d ", cur->depth, cur->depth%2==0?"X-split":"Y-split", cur->size);
    printf("Split Point: ");
    (cur->mark_point).print();*/
    if(cur->size == 1) {
        node_set.push_back(cur->mark_point);
    }
	else if(cur->size == 0) {
	}
    else {
        reportSubTree(cur->lc, node_set);
        reportSubTree(cur->rc, node_set);
    }
}

void KD_Tree::search_test() {
    // traverse test
    if(0) {
        traverse_test(root);
    }

    // query test
    KD_Point<double> p(1., 1., 0), q(8., 8., 1);
    vector< KD_Point<double> > ans;

    clock_t start = clock(), end;
    // for 1000 times
    for(int i = 0; i < 1000; i++) {
        ans = search(p, q);
    }
    end = clock();
    cout << "KD-tree query time: " << (end - start) * 1000. / CLOCKS_PER_SEC << "ms." << endl;

    // brute force query
    start = clock();
    vector< KD_Point<double> > test_ans;
    for(int j = 0; j < 1000; j++) {
        vector< KD_Point<double> > test_ans;
        for(int i = 0; i < number; i++) {
            if(p.x <= point_set[i].x  && point_set[i].x <= q.x &&
                    p.y <= point_set[i].y && point_set[i].y <= q.y) {
                test_ans.push_back(point_set[i]);
            }
        }
    }
    end = clock();
    cout << "brute force query time: " << (end - start) * 1000. / CLOCKS_PER_SEC << "ms." << endl;

    // verification
    int n = static_cast<int>(ans.size()),
        m = static_cast<int>(test_ans.size());
    if(n != m) {
        printf("Wrong Size: s %d b %d\n", n, m);
    }

    sort(ans.begin(), ans.end(), cmp_x);
    sort(test_ans.begin(), test_ans.end(), cmp_x);
    for(int i = 0; i < n; i++) {
        if(ans[i].x != test_ans[i].x || ans[i].y != test_ans[i].y) {
            printf("Wrong!\n");
            printf("ans[%d]: ", i);
            ans[i].print();
            printf("test_ans[%d]: ", i);
            test_ans[i].print();
            exit(1);
        }
    }
    printf("Test OK!\n");
#ifdef DEBUG
    printf("Query: X[%f:%f] x Y[%f:%f].\n", p.x, q.x, q.y, q.y);
    printf("result:\n");
    for(int i = 0; i < n; i++) {
        ans[i].print();
    }
#endif
}

bool KD_Tree::search_compare(const int div, std::vector<float> &time_compared) {

    // query test
    KD_Point<double> p(1., 1., 0), q(8., 8., 1);
    vector< KD_Point<double> > ans;

    clock_t start = clock(), end;
    // for 1000 times
	int total = 1000;
	float step = 0.5 / div;
    for(int i = 0; i < total /*/ div / div*/; i++) {
		for(int j = 0; j < 1/*div*/; j++) {
			for(int k = 0; k < 1/*div*/; k++) {
				p.x = 0.5 + j * step; p.y = 0.5 + k * step;
				q.x = 0.5 + (j + 1) * step; p.y = 0.5 + (k + 1) * step;
				ans = search(p, q);
			}
		}
    }
    end = clock();
    //cout << "KD-tree query time: " << (end - start) * 1000. / CLOCKS_PER_SEC << "ms." << endl;
	time_compared.push_back((end - start) * 1000. / CLOCKS_PER_SEC);

    // brute force query
    start = clock();
    vector< KD_Point<double> > test_ans;
    for(int i = 0; i < total /*/ div / div*/; i++) {
		for(int j = 0; j < 1/*div*/; j++) {
			for(int k = 0; k < 1/*div*/; k++) {
				test_ans.clear();
				p.x = 0.5 + j * step; p.y = 0.5 + k * step;
				q.x = 0.5 + (j + 1) * step; p.y = 0.5 + (k + 1) * step;
					for(int a = 0; a < number; a++) {
						if(p.x <= point_set[a].x  && point_set[a].x <= q.x &&
							p.y <= point_set[a].y && point_set[a].y <= q.y) {
								test_ans.push_back(point_set[a]);
						}
					}
			}
		}
    }
    end = clock();
    //cout << "brute force query time: " << (end - start) * 1000. / CLOCKS_PER_SEC << "ms." << endl;
	time_compared.push_back((end - start) * 1000. / CLOCKS_PER_SEC);

    // verification
    int n = static_cast<int>(ans.size()),
        m = static_cast<int>(test_ans.size());
    if(n != m) {
        printf("Wrong Size: s %d b %d\n", n, m);
		return false;
    }

    sort(ans.begin(), ans.end(), cmp_x);
    sort(test_ans.begin(), test_ans.end(), cmp_x);
    for(int i = 0; i < n; i++) {
        if(ans[i].x != test_ans[i].x || ans[i].y != test_ans[i].y) {
            printf("Wrong!\n");
            printf("ans[%d]: ", i);
            ans[i].print();
            printf("test_ans[%d]: ", i);
            test_ans[i].print();
            //exit(1);
			return false;
        }
    }
	return true;
    //printf("Test OK!\n");
}

void KD_Tree::traverse_test(const Node *cur) {
    puts("");
    printf("Node Region: X[%f:%f] x Y[%f:%f].\n", cur->tl.x, cur->br.x, cur->tl.y, cur->br.y);
    printf("Depth %d: %s with size: %d ", cur->depth, cur->depth%2==0?"X-split":"Y-split", cur->size);
    printf("Split Point: ");
    (cur->mark_point).print();
    if(cur->size != 1) {
        traverse_test(cur->lc);
        traverse_test(cur->rc);
    }
}
