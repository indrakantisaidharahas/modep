#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Tree {

    vector<int> left;

    vector<int> right;

    vector<int> feature;

    vector<float> threshold;

    vector<int> value;
};
int predict_tree(
    Tree& tree,
    vector<float>& x
) {

    int node = 0;

    while(tree.left[node] != -1) {

        int f = tree.feature[node];

        float th = tree.threshold[node];

        if(x[f] <= th)
            node = tree.left[node];
        else
            node = tree.right[node];
    }

    return tree.value[node];
}
int predict_forest(
    vector<Tree>& forest,
    vector<float>& x
) {

    vector<int> votes(100, 0);//assuming multiple categories 
    // we need a global array if we are going to parallesise all the trees 

    int n=forest.size();
    vector<int>dec(n,-1);//descisions are stored in this 



    #pragma omp parallel for
    for(int i=0;i<n;i++) {
       //auto tree=forest[i];
        int cls = predict_tree(forest[i], x);
       dec[i]=cls;
        // votes[cls]++;
    }
    for(int i=0;i<n;i++){
       votes[dec[i]]++;
    }


    int best = 0;

    for(int i = 1; i < 100; i++) {

        if(votes[i] > votes[best])
            best = i;
    }

    return best;
}
int main() {

    ifstream f("forest.bin", ios::binary);

    if(!f) {
        cout << "Cannot open file\n";
        return 1;
    }

    int n_trees;

    f.read(reinterpret_cast<char*>(&n_trees),
           sizeof(int));

    cout << "Trees: "
         << n_trees
         << endl;

    vector<Tree> forest(n_trees);

    for(int t = 0; t < n_trees; t++) {

        int n_nodes;

        f.read(reinterpret_cast<char*>(&n_nodes),
               sizeof(int));

        cout << "Tree "
             << t
             << " nodes = "
             << n_nodes
             << endl;

        // SAFETY CHECK
        if(n_nodes <= 0 || n_nodes > 10000000) {

            cout << "Corrupted node count\n";

            return 1;
        }

        forest[t].left.resize(n_nodes);

        forest[t].right.resize(n_nodes);

        forest[t].feature.resize(n_nodes);

        forest[t].threshold.resize(n_nodes);

        forest[t].value.resize(n_nodes);

        f.read(reinterpret_cast<char*>(
               forest[t].left.data()),
               n_nodes * sizeof(int));

        f.read(reinterpret_cast<char*>(
               forest[t].right.data()),
               n_nodes * sizeof(int));

        f.read(reinterpret_cast<char*>(
               forest[t].feature.data()),
               n_nodes * sizeof(int));

        f.read(reinterpret_cast<char*>(
               forest[t].threshold.data()),
               n_nodes * sizeof(float));

        f.read(reinterpret_cast<char*>(
               forest[t].value.data()),
               n_nodes * sizeof(int));
    }

    cout << "\nForest loaded successfully\n";
vector<float> x = {
1,52,1,1,125,325,0,2,171,0,0.0,1,0,3
};

int pred = predict_forest(
    forest,
    x
);

cout << "Prediction = "
     << pred
     << endl;
    return 0;
}