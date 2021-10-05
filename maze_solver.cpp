// maze_solver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class maze_solver {
	private:
		Mat image;
		int read_image(void);
		int get_width_of_cell(void);
		int color_cell(int cell_col, int cell_row);
		void set_cell_width(int cell_width);
	public:
		int im_height = 0, im_width = 0;
		int cell_width = 0;
		String image_path;

		list<int> get_neighbors(int cell_col, int cell_row);
		int view_image(void);

		maze_solver() {
			cout << "PLEASE SPECIFY AN IMAGE" << endl;
			cout << "Destructor called due to some error. " << endl;
			maze_solver::~maze_solver();
		};

		maze_solver(String image_path) {
			maze_solver::image_path = image_path;
			cout << "IMAGE_PATH IS: " << image_path << endl;
			if (maze_solver::read_image() == -1) {
				cout << "Could not open or find the image" << endl;
				cin.get();
				cout << "Destructor called due to some error. " << endl;
				maze_solver::~maze_solver();
			}
			int width = maze_solver::get_width_of_cell();
			if (width % 10 != 0 || width <= 0) {
				cout << "Trouble finding the width of a cell." << endl;
				maze_solver::~maze_solver();
			}
			else {
				maze_solver::set_cell_width(width);
			}
		};
};

int main(void) {
	/*
		* FUNCTION: This is the main function. The solver class is going to be called here
		* INPUT: none
		* OUTPUT: returns 0 if program quits smoothly
	*/
	maze_solver solver1("../images/maze00.jpg");
	solver1.view_image();
	return 0;
}

int maze_solver::read_image(void) {
	/*
		* FUNCTION: Reads the image present at maze_solver::image_path and stores 
					it in maze_solver::image so it can be accessed by other members of the class.
		* INPUT: none
		* OUTPUT: Integer to specify errors. If any error occurs, return -1. Else return 0.
	*/
	maze_solver::image = imread(maze_solver::image_path);
	if (image.empty()) {
		return -1;
	}
	return 0;
}

int maze_solver::get_width_of_cell(void) {
	/*
		* FUNCTION: Uses the image (from maze_solver::image) to estimate the width of one cell.
		*			For ease, the width is always the closest multiple of 10.
		* INPUT: none
		* OUTPUT: Width of cell
	*/
	//TODO
	return 10;
}

list<int> maze_solver::get_neighbors(int cell_col, int cell_row) {
	/*
		* FUNCTION: Uses the image (from maze_solver::image), and row and col nos 
					of the cell to find all neighbors of said cell.
		* INPUT: cell_col (int), cell_row(int)
		* OUTPUT: list of integers representing neighbors as follows:
		*			1 -> UP
		*			2 -> DOWN
		*			3 -> LEFT
		*			4 -> RIGHT
		*		 (diagonal cells not considered)
	*/
	/*DO STUFF*/
	return { 0, 0 };
}

int maze_solver::view_image(void) {
	/*
		* FUNCTION: Views the image (from maze_solver::image)
		* INPUT: none
		* OUTPUT: int representing errors (if any). 0 -> no errors, 1 -> errors
	*/
	String windowName = "image";
	imshow(windowName, image);
	waitKey(0);
	destroyWindow(windowName);
	return 0;
}

int maze_solver::color_cell(int cell_col, int cell_row) {
	/*
		* FUNCTION: Given the col and row of a cell, colour the cell gray
					while not colouring any maze borders
		* INPUT: cell_col (int), cell_row(int)
		* OUTPUT: int representing errors (if any). 0 -> no errors, 1 -> errors
	*/
	/*DO STUFF*/
	return 0;
}

void maze_solver::set_cell_width(int cell_width) {
	/*
		* FUNCTION: Set the class variable cell_width to the value provided in argument.
		* INPUT: cell_width (int)
		* OUTPUT: none
	*/
	maze_solver::cell_width = cell_width;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
