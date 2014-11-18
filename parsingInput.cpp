struct BezierPatch {
	// 16 control points --> 4 Bezier curves
	vector<vector> curve1;
	vector<vector> curve2;
	vector<vector> curve3;
	vector<vector> curve4;
};

struct AllBezierPatches {
	vector<BezierPatch> allPatches;
	int numOfPatches;
};


/** Global Variables **/
int numOfPatches = 0;
AllBezierPatches patches;


void parsingInputFile(string file_name) {
	ifstream infile(file_name.c_str());

	if (!infile.is_open()) {
		cout << "Unable to open the file, " << file_name << endl;
		exit(-1);
	} 
	else {
		vector<Patch> allPatches;				// Store the patches in a vector
		int r = 0;
		BezierPatch patch;

		while (!infile.eof()) {
			string line;
			getline(infile, line);

			string buf;
			stringstream ss(line); 				// Insert the string into a stream
			std::vector<string> tokens;        	// Create vector to hold our input

    		while (ss >> buf) {
        		tokens.push_back(buf);			// Insert the token in to the vector
    		}

			if (r == 0) {
				patches.numOfPatches = atof(tokens[0].c_str());				// Record the num of patches in total
				r++;
				continue;
			}
			if (tokens.size() == 0) {										// Empty line
				continue;
			}
			if (tokens.size() != 12) {
					cout << "Expected 12 items, but now we have " << tokens.size() << endl;
					exit(-1);
			else {
				// parsing the points, put them into matrix patch
				std::vector<vector> tempCurve;
				for (int i = 0; i < 4; i++) {	
					float point[3] = {atof(tokens[i*3].c_str()), atof(tokens[i*3+1].c_str()), atof(tokens[i*3+2].c_str())};
					tempCurve.push_back(point);
				}
				if (r == 1) {
					patch.curve1 = tempCurve;
				} else if (r == 2) {
					patch.curve2 = tempCurve;
				} else if (r == 3) {
					patch.curve3 = tempCurve;
				} else if (r == 4){
					patch.curve4 = tempCurve;
					r = 0;
					patches.allPatches.push_back(patch);
					patch.curve1.clear();
					patch.curve2.clear();
					patch.curve3.clear();
					patch.curve4.clear();
				}
				r++;
			}
		}
	}
	infile.close();
	return allPatches;
}

/** Sample input file
Every point is store as a vector
Every row is stored as a vector
Each patch is sotred as a vector

2
 0.00  0.00  0.00   0.33  0.00  0.00   0.66  0.00  0.00   1.00  0.00  0.00
 0.00  0.33  0.00   0.33  0.33  0.00   0.66  0.33  0.00   1.00  0.33  0.00
 0.00  0.66  0.00   0.33  0.66  0.00   0.66  0.66  0.00   1.00  0.66  0.00
 0.00  1.00  0.00   0.33  1.00  0.00   0.66  1.00  0.00   1.00  1.00  0.00

 0.00  0.00  0.00   0.33  0.00  2.00   0.66  0.00  2.00   1.00  0.00  0.00
 0.00  0.33  0.00   0.33  0.33  2.00   0.66  0.33  2.00   1.00  0.33  0.00
 0.00  0.66  0.00   0.33  0.66  2.00   0.66  0.66  2.00   1.00  0.66  0.00
 0.00  1.00  0.00   0.33  1.00  2.00   0.66  1.00  2.00   1.00  1.00  0.00

**/
