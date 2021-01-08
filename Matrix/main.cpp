#include <iostream>
#include <stdio.h>

#define NUM_OR_COLUMNS 3
using namespace std;

void find_min_max(int matrix[][NUM_OR_COLUMNS ], int num_rows, int num_columns) {
    int min = matrix[0][0], min_row = 0, min_col = 0, min_index = 0;
    int max = matrix[0][0], max_row = 0, max_col = 0, max_index = 0;
    int index =0;
    for(int i = 0; i<num_rows; i++) {
        for(int j=0; j<num_columns; j++) {
            if(min > matrix[i][j]){
                min = matrix[i][j];
                min_row = i+1;
                min_col = j+1;
                min_index = index;
            }
            if(max < matrix[i][j]){
                max = matrix[i][j];
                max_row = i+1;
                max_col = j+1;
                max_index = index;
            }
            index++;
        }
    }
    cout<<"min "<<min<<" row "<<min_row<<" column "<<min_col<<" index "<<min_index<<"\n";
    cout<<"max "<<max<<" row "<<max_row<<" column "<<max_col<<" index "<<max_index<<"\n";

}

int main() {
    int x[3][3] ={{3,4,6},{2,8,1},{4,0,4}};
    find_min_max(x, 3, 3);
    return 0;
}
