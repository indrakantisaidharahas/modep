#include "include/data_points.h"
#include "include/dec_tree.h"
int main() {

    data_points df("test2.csv");
    random_forest rf("forest.bin");
    auto ans=rf.predict(df.dpoints);
    for(auto i:ans){
cout<<i<<" ";
    }
    return 0;
}