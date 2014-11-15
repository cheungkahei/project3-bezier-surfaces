#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string> 

using namespace std;

//******NOTE: I just added this part from pj1,
//******but will edit it with open gl methods once I do the research - AI

int main(int argc, char *argv[]) {
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  initScene();              // quick function to set up scene

  cout << "Please enter a command";
  getline (cin,str); 
  
};