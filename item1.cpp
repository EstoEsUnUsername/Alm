#include <iostream>

using namespace std;

int sudoku[4][4];

int row = 0;
int column = 0;

bool isFull(int s[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(s[4][4] == 0){
                return false;
            }
        }
    }

    return true;
}

void printMatrix(int s[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << sudoku[i][j] << "  ";
        }
        cout << endl;
    }
}

bool isAssigned(int row, int column){
    if(row == 1 && column == 0 ||
       row == 0 && column == 2 ||
       row == 1 && column == 2){
        return true;
    } else return false;
}

bool verify(int s[4][4], int row, int column){

    bool flag = false;

    int sumrow = 0, sumcolumn = 0, sumDiagonal = 0, sumDiagonal2 = 0;
    int value = 3;
    for(int i = 0; i < 4; i++){
        sumrow = sumrow + s[row][i];
        sumcolumn = sumcolumn + s[i][column];
        sumDiagonal = sumDiagonal + s[i][i];
        sumDiagonal2 = sumDiagonal2 + s[i][value];
        value--;
    }

    if(sumrow <= 34 && sumcolumn <= 34 && sumDiagonal2 <= 34 && sumDiagonal2 <= 34){
        return true;
    } else return false;

}

bool backtracking(int s[4][4], int row, int column){

    if(isFull(s) == true){ //verify if there are no zeros in the matrix
        printMatrix(sudoku);
        cout<<"Solution find ";
    }
    else {

        if(isAssigned(row, column) == false){ // verify if the cell is already assigned

            for(int i = 1; i <= 16; i++){

                s[row][column] = i; // assigned value

                if(verify(s, row, column) == true){ // verify that the sum of the column, row and diagonal not greater 34

                    if(column == 4) {
                            row++;
                            column=0;
                    }

                    backtracking(s, row, column + 1); // recursion
                    printMatrix(s); // Print the matrix to see progress
                    cout<<endl;

                } else { // the sum value exceeds 34
                    s[row][column] = 0;
                    return false;
                }
            }
        }
    }
}

int main(){

    sudoku[1][0] = 5;
    sudoku[0][2] = 15;
    sudoku[1][2] = 10;

    backtracking(sudoku, row, column);

    return 0;
}
