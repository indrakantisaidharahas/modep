#include "include/data_points.h"

int main() {

    data_points df;
    
    auto ans=df.predict("test2.csv");
    for(auto i:ans){
cout<<i<<" ";
    }
    cout<<endl<<ans.size()<<endl;
    return 0;
}