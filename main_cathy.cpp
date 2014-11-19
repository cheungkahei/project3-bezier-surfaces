#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Triangle {
	float vertex1[3];
	float vertex2[3];
	float vertex3[3];
};

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
vector<Triangle> adaptiveTriangle;

float x_pos = 0.0f;
float y_pos = 0.0f;
float x_angle = 0.0f;
float y_angle = 0.0f;

float translate_constant;
float rotation_constant;
float zoom_constant;
bool flat_mode = true;
bool smooth_mode = false;
bool filled_mode = true;
bool wireframe_mode = false;
bool hiddeline_mode = false;
bool adaptive_mode = false;


class Viewport;
class Veiwport {
public:
	int w, h;
};

void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;

  glViewport (0,0,viewport.w,viewport.h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, viewport.w, 0, viewport.h);
}


void initScene(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent
	myReshape(viewport.w,viewport.h);
}


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


void keyboardCommand(unsigned char key, int x, int y) {
    switch(key) {
    case ('S'):
    case ('s'):
        if (flat_mode):
        	smooth_mode = true;
        	flat_mode = false;
        else if (smooth_mode):
        	smooth_mode = false;
        	flat_mode = true;

    case ('W'):
    case ('w'):
        if (filled_mode):
        	wireframe_mode = true;
        	filled_mode = false;
        else if (wireframe_mode):
        	wireframe_mode = false;
        	filled_mode = true;

    case ('H'):
    case ('h)':
        if (filled_mode):
        	hiddeline_mode = true;
        	filled_mode = false;
        else if (hiddeline_mode):
        	hiddeline_mode = false;
        	filled_mode = true;

    case ('+'):
    	zoom += zoom_constant;

    case ('-'):
    	zoom -= zoom_constant;
    }
    redrawImage();
}


void specialCommand(int key, int x, int y) {
	int mod = glutGetModifiers()
	switch(mod) {
	case (GLUT_ACTIVE_SHIFT && GLUT_KEY_LEFT):			// shift + left
		x_pos -= translate_constant;

	case (GLUT_ACTIVE_SHIFT && GLUT_KEY_RIGHT):			// shift + right
		x_pos += translate_constant;

	case (GLUT_ACTIVE_SHIFT && GLUT_KEY_UP):			// shift + up
		y_pos += translate_constant;

	case (GLUT_ACTIVE_SHIFT && GLUT_KEY_DOWN):			// shift + up
		y_pos -= translate_constant;

	case (GLUT_KEY_LEFT):								// left
		x_angle -= rotation_constant;

	case (GLUT_KEY_RIGHT):								// right
		x_angle += rotation_constant;

	case (GLUT_KEY_UP):									// up
		y_angle += rotation_constant;

	case (GLUT_KEY_DOWN):								// right
		y_angle -= rotation_constant;
	}
	redrawImage();
}


void redrawImage() {
	// Clear color frame  and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

	// Replace the current matrix with identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glPolygonMode (GL_FRONT_AND_BACK, filled_mode ? GL_FILL : GL_LINE);

	glTranslate(x_pos, y_pos, 0.0f);
	glRotatef(x_angle, 0.0f, 1.0f, 0.0f);
	glRotatef(y_angle, 1.0f, 0.0f, 0.0f);

	drawImage();
}


void drawImage() {
	if (!adaptive_mode) {
		for (int n = 0; n < numOfPatches; n++) {
			BezierPatch curr_patch = patches.allPatches[n];
			std::vector<vector> curve;
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					curve = allPatches.curve1;
				} else if (i == 1) {
					curve = allPatches.curve2;
				} else if(i == 2) {
					curve = allPatches.curve3;
				} else {
					curve = allPatches.curve4;
				}
				float point1[3] = curve[0];
				float point2[3] = curve[1];
				float point3[3] = curve[2];
				float point4[4] = curve[3];

				if (smooth_mode) {
					glShadingModel(GL_SMOOTH);
					glBegin(GL_TRIANGLES);

					glEnd();

				}
				else {
					glShadingModel(GL_FLAT);
					glBegin(GL_QUADS);
					float triNorm[3] = normalizeTriangle(point1, point2, point3);
					glNormal3f(triNorm[0], triNorm[1], triNorm[2] );
					glVertex3f(point1[0], point1[1], point1[2]);
					glVertex3f(point2[0], point2[1], point2[2]);
					glVertex3f(point3[0], point3[1], point3[2]);
					glVertex3f(point4[0], point4[1], point4[2]);
					glEnd();
				}
			}
		}
		
	} else {
		//adaptive triangulation
	}


}



