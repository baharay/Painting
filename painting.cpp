#include <string>
#include <fstream>
#include <iostream>

using namespace std;
class input {
		public:
			char data;
			bool painted;
			input();
	};
input::input() {
	painted = false;
}
class wall {
public:
	input **array;
	int col;
	int row;
	wall(int,int);
};
wall::wall(int i,int j) {
	row = i;
	col = j;
	array = new input*[row];
	for(int i = 0; i<row; i++) {
		array[i] = new input[col];
	}
}
wall takeInput(string fileName) {
	fstream file;
	file.open(fileName.c_str());
	string *rows;
	string tempRow;
	int column;
	int row;
	
	file >> row;
	file >> column;
	wall temp = wall(row,column);
	rows = new string[row];
	for(int i = 0;i<row;i++) {
		file >> rows[i];
	}
	
	for(int i = 0; i<row; i++) {
		for(int j = 0; j<column; j++) {
			temp.array[i][j].data = rows[i][j];
			temp.array[i][j].painted = false;
		}
	}
	delete[] rows;
	file.close();
 	return temp;
}

float tol = 0.5;

bool checkSquare(wall& input, int n, int col, int row) {
 int emptyLim = n*tol;
 int paintedLim = n*tol;
 int empties = 0;
 int painted = 0;

 for(int i = row-n/2; i <= row + n/2; i++) {

  for(int j = col - n/2; j <= col + n/2; j++) {

   if( input.array[i][j].painted == true) painted++;
   if( input.array[i][j].data == '.') empties++;

   if( empties > emptyLim ) return false;
   if( painted > paintedLim) return false;
  }
 }

 for(int i = row-n/2; i <= row + n/2; i++) {

  for(int j = col - n/2; j <= col + n/2; j++) {

   input.array[i][j].painted = true;
  }
 }
 return true;
}

void paintSquares(wall& input) {
	int col = input.col;
	int row = input.row;

	int init;
	col < row ? init = col : init = row;
	init%2 ? true : init--;

	for(int dim = init; dim >= 3; dim -= 2)
	{
		for(int i = dim/2; i <= row - dim/2; i++){
		for(int j = dim/2; j <= col - dim/2; j++){

			if( checkSquare(input,dim, j, i) )
				cout << "PAINT_SQUARE " << i << " " << j << " " << dim/2<<endl;
		}
		}

	}

}

void empty(wall& input) {
 int col = input.col;
 int row = input.row;
  for(int i = 0; i < row; i++) {
 	for(int j = 0; j < col; j++) {


   if( input.array[i][j].painted == true && input.array[i][j].data == '.')
   {
    input.array[i][j].painted = false;
    cout << "ERASE_CELL " << j << " " << i << endl;
   }
  }
 }

}

int main() {
	wall inp = takeInput("right_angle.in");
	fstream output;
	fstream input;
	input.open("right_angle.in");
	output.open("output.txt");

	//string in = input.read();
	//string out = 

/*cout << checkSquare(inp,3,2,3) << endl;
cout << checkSquare(inp,5,2,3) << endl;
cout << checkSquare(inp,3,1,3) << endl;*/
paintSquares(inp);
empty(inp);



cout << "PAINTED" << endl;
for(int i = 0; i<inp.row; i++)
{
 for(int j = 0; j<inp.col;j++)
 {
  if(inp.array[i][j].painted)
   cout << '#';
  else
   cout << '.';
 }
 cout << '\n';
}

for(int i = 0; i<inp.row; i++) {
	for(int j = 0; j<inp.col;j++)  {
 		 if(inp.array[i][j].painted)
 		  output << '#';
 		 else
 		  output << '.';
 	}	
	output << '\n';
	}
	return 0;
}
