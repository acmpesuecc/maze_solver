// maze_solver.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
	Author: Gall1frey (github.com/ga1frey)
	
	This is a maze solver that takes in pictures of square mazes and tries to compute a way out
	The start point is taken as (0,0), which is the cell in the top left corner and the end point is
	(m,n) where m and n are the number of rows/columns in the matrix. This would be the bottom right cell.

	The input image can be of type png/jpeg/etc., and each cell in the maze is a white square. Walls are represented
	by black lines.
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

struct myTuple {
	/*Tuple with two values*/
	int x;
	int y;
};

class maze_solver {
	private:
		Mat image;
		int cell_width = 0;

		int read_image(void);
		int get_width_of_cell(void);
		int color_cell(int cell_col, int cell_row);
		void set_cell_width(int cell_width);
		list<myTuple> get_neighbors(int cell_col, int cell_row);
		list<myTuple> maze_solver_algo();

	public:
		int im_height = 0, im_width = 0;
		list<myTuple> path;
		String image_path;

		int view_image(void);
		myTuple get_height_and_width_of_img(void);
		void solve_maze();

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
	myTuple dims = solver1.get_height_and_width_of_img();
	cout << "DIM: " << dims.x << " " << dims.y << endl;
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
	return 20;
}

list<myTuple> maze_solver::get_neighbors(int cell_col, int cell_row) {
	/*
		* FUNCTION: Uses the image (from maze_solver::image), and row and col nos 
					of the cell to find all neighbors of said cell.
		* INPUT: cell_col (int), cell_row(int)
		* OUTPUT: list of tuples (myTuple) representing neighbors
	*/
	/*DO STUFF*/
	myTuple cell;
	cell.x = 0;
	cell.y = 0;
	list<myTuple> neighbors;
	neighbors.push_back(cell);
	return neighbors;
}

int maze_solver::view_image(void) {
	/*
		* FUNCTION: Views the image (from maze_solver::image)
		* INPUT: none
		* OUTPUT: int representing errors (if any). 0 -> no errors, 1 -> errors
	*/
	String windowName = "image";
	imshow(windowName, maze_solver::image);
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

myTuple maze_solver::get_height_and_width_of_img(void) {
	/*
		* FUNCTION: Get the height, width and channels of image,
		*			Use that to calculate no. of rows and columns in the maze
		* INPUT: none
		* OUTPUT: nos of rows and columns (list)
	*/
	Mat img = maze_solver::image;
	cv::Size sz = img.size();
	myTuple dims;
	dims.x = sz.height / maze_solver::cell_width;
	dims.y = sz.width / maze_solver::cell_width;
	return dims;
}

list<myTuple> maze_solver::maze_solver_algo() {
	/*
		* FUNCTION: The function that actually solves the maze
		*			Add and use helper functions as required
		* INPUT: none
		* OUTPUT: list of cells to visit (in order) to traverse the maze
		* (Start at (0,0) (Top left) and reach (n,n) (Bottom right))
	*/
	list<myTuple> path;
	/*DO STUFF*/
	return path;
}

void maze_solver::solve_maze() {
	/*
		* FUNCTION: Handler. Calls maze_solver_algo. updates path on image, shows image
		* INPUT: none
		* OUTPUT: none
	*/
	list<myTuple> path = maze_solver::maze_solver_algo();
	list<myTuple>::iterator it;
	it = path.begin();
	while (it != path.end()) {
		cout << "X: " << it->x << " Y: " << it->y << endl;
		maze_solver::color_cell(it->x, it->y);
		it++;
	}
	maze_solver::view_image();
}