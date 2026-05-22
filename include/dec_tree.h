#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

using namespace std;

class dec_tree {
public:
    vector<int> left;
    vector<int> right;
    vector<int> feature;
    vector<float> threshold;
    vector<int> value;
    vector<int> leaves;
    int nodes;

    vector<int> predict(vector<vector<float>> &x) {

        int n = x.size();
        vector<int> result(n);

         #pragma omp parallel for
        for (int i = 0; i < n; i++) {

            int node = 0;

            while (left[node] != -1) {

                int f = feature[node];
                float th = threshold[node];

                if (x[i][f] <= th)
                    node = left[node];
                else
                    node = right[node];
            }

            result[i] = value[node];
        }

        return result;
    }

    void leaves_exec() {
        for (int i = 0; i < nodes; i++) {
            if (left[i] == -1) {
                leaves.push_back(i);
            }
        }
    }
};

class random_forest {
public:
    vector<dec_tree> forest;
    int n_trees;

    random_forest(string path) {

        ifstream f("forest.bin", ios::binary);

        if (!f) {
            cout << "Cannot open file\n";
            return;
        }

        f.read(reinterpret_cast<char*>(&n_trees), sizeof(int));

        forest.resize(n_trees);

        for (int t = 0; t < n_trees; t++) {

            int n_nodes;
            f.read(reinterpret_cast<char*>(&n_nodes), sizeof(int));

            forest[t].nodes = n_nodes;

            forest[t].left.resize(n_nodes);
            forest[t].right.resize(n_nodes);
            forest[t].feature.resize(n_nodes);
            forest[t].threshold.resize(n_nodes);
            forest[t].value.resize(n_nodes);

            f.read(reinterpret_cast<char*>(forest[t].left.data()),
                   n_nodes * sizeof(int));

            f.read(reinterpret_cast<char*>(forest[t].right.data()),
                   n_nodes * sizeof(int));

            f.read(reinterpret_cast<char*>(forest[t].feature.data()),
                   n_nodes * sizeof(int));

            f.read(reinterpret_cast<char*>(forest[t].threshold.data()),
                   n_nodes * sizeof(float));

            f.read(reinterpret_cast<char*>(forest[t].value.data()),
                   n_nodes * sizeof(int));

            forest[t].leaves_exec();
        }

        cout << "random forest loaded\n";
    }

    vector<int> predict(vector<vector<float>> &x) {

        int n = x.size();
        vector<int> votes(n, 0);
        vector<int> result(n);

        for (auto &tree : forest) {

            auto ans = tree.predict(x);

            for (int i = 0; i < n; i++) {
                votes[i] += ans[i];
            }
        }

        for (int i = 0; i < n; i++) {
            result[i] = (votes[i] > n_trees / 2) ? 1 : 0;
        }
        //cout<<"finished"<<endl;
        return result;
    }
};