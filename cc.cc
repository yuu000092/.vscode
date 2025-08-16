#include <iostream>
#include <vector>

using namespace std;
int main(void){
    vector<int> v;

    for( int i = 0; i < 101; ++i ) {
        v.push_back(i);
        cout << v[i] << " \n";
    }
    cout << endl;
}