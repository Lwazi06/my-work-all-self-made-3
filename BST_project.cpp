#include <queue>
#include <iostream>
#include <vector>
using namespace std ;

void print_maze(vector< vector<string> > matrix, int cols, int rows) {
 for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            cout << matrix[i][j] ;
        }
        cout << endl;
     }
}

bool MoveAcrossTheMaze(vector< vector<string> > &matrix, int cols, int rows , int x, int y) {
        if (x<0 || x>=rows || y<0 || y>=cols ){
                return false ;
        }
        if (matrix[x][y] == "x") {
            return false ;
        }
        return true  ;
}



void ShortestPath(int rows,int cols, vector< vector<string> > matrix,int xG,int yG,int xS,int yS ){ 
    vector< vector<int> > distance_array(rows,vector<int>(cols,-1)) ;
    vector< vector< pair<int, int> > > parent_array(rows, vector< pair<int, int> > (cols));
        for (int i=0 ; i < rows ; i++){
            for (int j=0 ; j < cols ; j++) {
                parent_array[i][j] = make_pair(-1,-1) ;
            }
        }

    distance_array[xS][yS] = 0 ;
    vector < pair<int, int> > movement(4) ;
    movement[0] = make_pair(1,0) ; //down
    movement[1] = make_pair(0,-1) ; //left
    movement[2] = make_pair(-1,0) ; //up
    movement[3] = make_pair(0,1) ; //right

    queue < pair<int,int> > fringe ;
    fringe.push(make_pair(xS,yS)) ;

    while (fringe.size() !=0 && distance_array[xG][yG] == -1) {
        pair <int,int> currx = fringe.front() ;
        int curr1 =  currx.first ;
        int curr2 = currx.second ;
        fringe.pop() ;


             for (int i=0 ; i < movement.size() ; i++ ) {
                int xnew = curr1 + movement[i].first ;
                int ynew = curr2 + movement[i].second ;
               

                if (MoveAcrossTheMaze(matrix,cols,rows,xnew,ynew) == true && distance_array[xnew][ynew] == -1){
                    distance_array[xnew][ynew] = distance_array[curr1][curr2] + 1 ;
                    parent_array[xnew][ynew] = make_pair(curr1,curr2) ;
                    fringe.push(make_pair(xnew,ynew)) ;
                }
             }
        }

    if (distance_array[xG][yG] == -1) {
        cout << "No Path" << endl ;
        return ;
    }
    else{

        vector< vector<string> > star_array(rows, vector<string>(cols, "*"));
        vector< pair<int, int> > output_list ;

        pair <int,int> curr ;
        curr.first = xG ;
        curr.second = yG ;
        pair <int,int> start ;
        start.first = xS ;
        start.second = yS ;

        while (curr != start ) {
            output_list.insert(output_list.begin(),curr) ;
            curr =  parent_array[curr.first][curr.second] ;
        }

        output_list.insert(output_list.begin(),start) ;

        for (int i=1 ;  i < output_list.size() - 1 ; i++) {
            int a = output_list[i].first ;
            int b = output_list[i].second ;
            matrix[a][b] = star_array[a][b] ;
        }

        print_maze(matrix,cols,rows) ;

    }
}


int main(){  
    int rows, cols ;
    cin >> rows >> cols ;
    cin.ignore() ;
    int xG, yG, xS, yS ;
    vector< vector<string> > matrix(rows, vector<string>(cols)) ;
    string entries ;
    for (int k = 0; k < rows; k++) {
        getline(cin,entries) ;
        for (int j = 0; j < cols ; j++) {
         if (j < entries.size()) {
         matrix[k][j] = string(1,entries[j]) ;
            if (matrix[k][j] == "S") {
                xS = k ;
                yS = j ;
            }
         else if (matrix[k][j] == "G"){
            xG = k ;
            yG = j ;
         }
         }
    }
    }


   ShortestPath(rows,cols,matrix,xG,yG,xS,yS) ;

   return 0 ;
}