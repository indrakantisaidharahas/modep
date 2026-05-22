#include "include/data_points.h"

int main() {

    data_points df;
    random_forest rf("forest.bin");
    auto ans=df.predict("test.csv",rf);
    for(auto i:ans){
cout<<i<<" ";
    }
    cout<<endl<<ans.size()<<endl;
    return 0;
}
