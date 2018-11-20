#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <math.h>
#include <stdlib.h>


using namespace std;

class NZ {
public:
	int col;
	int row;
	double val;
	NZ() {
		col = -1;
		val = -1;
	}

	NZ(int col, int row, double val) {
		this->col = col;
		this->row = row;
		this->val = val;
	}

	void trans() {
		int temp = this->col;
		this->col = this->row;
		this->row = temp;
	}
};

typedef list<NZ> SparseRow;
typedef list<SparseRow*> SparseMat;

void readMat(SparseMat&);
void printMat(SparseMat&);
void transposeMat(SparseMat&, SparseMat&);

int rowsToMake = 0;

int main(int argc, char* argv[]) {
	SparseMat mat;
	SparseMat transMat;

	readMat(mat);
	transposeMat(mat, transMat);
	printMat(transMat);
}

void transposeMat(SparseMat &mat, SparseMat &transMat) {
	for(int i = 0;i < rowsToMake;i++) {
		SparseRow *row = new SparseRow();
		transMat.push_back(row);
	}

	SparseMat::iterator mIt, tIt;

	for(mIt = mat.begin(); mIt != mat.end(); ++mIt) {
		tIt = transMat.begin();
		for(SparseRow::iterator rowIt = (*mIt)->begin(); rowIt != (*mIt)->end(); ++rowIt) {
			NZ nz = *rowIt;
			for(int i = 0;i < nz.col - 1;i++) {
				tIt++;
			}
			nz.trans();
			(*tIt)->push_back(nz);
		}
	}
}

void printMat(SparseMat &matrix) {
	SparseMat::iterator it;

	for(it = matrix.begin();it != matrix.end();++it, cout << endl) {
		for(SparseRow::iterator a = (*it)->begin(); a != (*it)->end(); ++a) {
			cout << a->col << " " << a->val << " " ;
		} 
	}
}

void readMat(SparseMat &matrix) {
	rowsToMake = 0;
	string line;

	int rowNo = 0;
	while(getline(cin, line)) {

		istringstream iss(line);
		SparseRow *row = new SparseRow();
		int colNo = 0;
		double val = 0;
		rowNo++;
		while(iss >> colNo >> val) {
			NZ nonZero(colNo,rowNo, val);
			row->push_back(nonZero);	
			if(rowsToMake < colNo) rowsToMake = colNo;
		}
		matrix.push_back(row);
	}
}