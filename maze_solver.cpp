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
#include <stdlib.h> 

using namespace cv;
using namespace std;

struct myTuple {
	/*Tuple with two values*/
	int row; // row
	int col; // col
};

class maze_solver {
	private:
		Mat image;
		int cell_width = 0;
		vector< vector < int > > adjacency_list;

		int read_image(void);
		int get_width_of_cell(void);
		int round(int);
		bool wall_exists(myTuple, myTuple);
		void set_cell_width(int);
		void get_adjacency_list(void);
		list<myTuple> get_neighbors(myTuple);
		list<myTuple> maze_solver_algo(void);		

	public:
		int im_height = 0, im_width = 0;
		list<myTuple> path;
		String image_path;

		int color_cell(myTuple);
		int view_image(void);
		myTuple get_height_and_width_of_img(void);
		void solve_maze(void);

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
			} else {
				maze_solver::set_cell_width(width);
			}
			myTuple dims = maze_solver::get_height_and_width_of_img();
			if (!(dims.row > 0 && dims.col > 0)) {
				cout << "Trouble finding the dimensions of maze." << endl;
				maze_solver::~maze_solver();
			} else {
				maze_solver::im_height = dims.row;
				maze_solver::im_width = dims.col;
			}
			cout << "STEP: " <<maze_solver::image.step << endl;
			cout << "WIDTH: " << maze_solver::image.cols << endl;
			cout << "HEIGHT: " << maze_solver::image.rows<< endl;
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
	cout << "DIM: " << dims.row << " " << dims.col << endl;
	//solver1.solve_maze();
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
	cvtColor(maze_solver::image, maze_solver::image, cv::COLOR_BGR2GRAY);
	maze_solver::image = maze_solver::image > 128;
	if (image.empty()) {
		return -1;
	}
	return 0;
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

int maze_solver::color_cell(myTuple cell) {
	/*
		* FUNCTION: Given the col and row of a cell, colour the cell gray
					while not colouring any maze borders
		* INPUT: (myTuple) cell
		* OUTPUT: int representing errors (if any). 0 -> no errors, 1 -> errors
	*/
	int start_row = (cell.row) * maze_solver::cell_width;
	int start_col = (cell.col) * maze_solver::cell_width;
	int end_row = (cell.row + 1)* (maze_solver::cell_width);
	int end_col= (cell.col + 1) * (maze_solver::cell_width);
	for (int row_iter = start_row; row_iter < end_row; row_iter++) {
		for (int col_iter = start_col; col_iter < end_col; col_iter++) {
			if ( maze_solver::image.at<uchar>(row_iter, col_iter) ) {
				maze_solver::image.at<uchar>(row_iter, col_iter) = 128;
			}
		}
	}
	return 0;
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
	dims.row = sz.height / maze_solver::cell_width;
	dims.col = sz.width / maze_solver::cell_width;
	return dims;
}

int maze_solver::get_width_of_cell(void) {
	/*
		* FUNCTION: Uses the image (from maze_solver::image) to estimate the width of one cell.
		*			For ease, the width is always the closest multiple of 10.
		* INPUT: none
		* OUTPUT: Width of cell
	*/
	//TODO
	int cell_width = 0;
	int height = maze_solver::image.rows;
	int width = maze_solver::image.cols;
	int _stride = maze_solver::image.step;
	uint8_t* img_data = maze_solver::image.data;
	int counter = 0;
	int min_white = width;
	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width; j++) {
			uint8_t val = img_data[(i * _stride + j)];
			if (val == 255) {
				counter++;
			}
			else {
				if (counter != 0 && counter < min_white)
					min_white = counter;
				counter = 0;
			}
		}
	}
	cell_width = maze_solver::round(min_white);
	cout << "CELL WIDTH: " << cell_width << endl;
	return cell_width;
}

void maze_solver::set_cell_width(int cell_width) {
	/*
		* FUNCTION: Set the class variable cell_width to the value provided in argument.
		* INPUT: cell_width (int)
		* OUTPUT: none
	*/
	maze_solver::cell_width = cell_width;
}

int maze_solver::round(int n) {
	int a = (n / 10) * 10;
	int b = a + 10;
	return (n - a > b - n) ? b : a;
}

void maze_solver::solve_maze() {
	/*
		* FUNCTION: Handler. Calls maze_solver_algo. updates path on image, shows image
		* INPUT: none
		* OUTPUT: none
	*/
	maze_solver::get_adjacency_list();
	for (int i = 0; i < maze_solver::im_height * maze_solver::im_width; i++) {
		cout << "NODE: " << i << " NEIGHBORS: ";
		vector<int> node = maze_solver::adjacency_list[i];
		vector<int>::iterator it;
		it = node.begin();
		while (it != node.end()) {
			cout << *it << "\t";
			it++;
		}
		cout << endl;
	}
	/*list<myTuple> path = maze_solver::maze_solver_algo();
	list<myTuple>::iterator it;
	it = path.begin();
	while (it != path.end()) {
		cout << "X: " << it->x << " Y: " << it->y << endl;
		maze_solver::color_cell(it->x, it->y);
		it++;
	}
	maze_solver::view_image();*/
}

list<myTuple> maze_solver::maze_solver_algo() {
	/*
		* FUNCTION: The function that actually solves the maze
		*			Add and use helper functions as required
		* INPUT: none
		* OUTPUT: list of cells to visit (in order) to traverse the maze
		* (Start at (0,0) (Top left) and reach (n,n) (Bottom right))
	*/
	// First generating an adjacency matrix
	list<myTuple> path;
	/*DO STUFF*/
	return path;
}

void maze_solver::get_adjacency_list() {
	/*
		* FUNCTION: Generates an adjacency list of the form:
		*			<NODE>:{<NEIGHBOR>,<NEIGHBOR>}
		*			<NODE>:{<NEIGHBOR>,<NEIGHBOR>,<NEIGHBOR>,<NEIGHBOR>,<NEIGHBOR>}
		*			<NODE>:{<NEIGHBOR>}
		*			and store it in the class variable adjacency_list
		* INPUT: none
		* OUTPUT: none
	*/
	int no_of_nodes = maze_solver::im_height * maze_solver::im_width;

	//Initialize the adjacency list with an empty list for each node.
	for (int i = 0; i < maze_solver::im_height * maze_solver::im_width; i++) {
		std::vector<int> tmp;
		maze_solver::adjacency_list.push_back(tmp);
	}

	//Traverse the maze to find neighbors and populate the adjacency list
	for (int row_iter = 0; row_iter < maze_solver::im_height; row_iter++) {
		for (int col_iter = 0; col_iter < maze_solver::im_width; col_iter++) {
			myTuple cell = { row_iter, col_iter };
			list<myTuple> neighbors = maze_solver::get_neighbors(cell);
			list<myTuple>::iterator it;
			it = neighbors.begin();
			while (it != neighbors.end()) {
				maze_solver::adjacency_list[(it->row * maze_solver::im_width) + it->col].push_back((row_iter * maze_solver::im_width) + col_iter);
				it++;
			}
			neighbors.clear();
		}
	}
}

list<myTuple> maze_solver::get_neighbors(myTuple cell) {
	/*
		* FUNCTION: Uses the image (from maze_solver::image), and row and col nos
					of the cell to find all neighbors of said cell.
		* INPUT: cell_col (int), cell_row(int)
		* OUTPUT: list of tuples (myTuple) representing neighbors
	*/
	/*DO STUFF*/
	list<myTuple> neighbors;
	neighbors.clear();
	for (int row_iter = -1; row_iter <= 1; row_iter++) {
		for (int col_iter = -1; col_iter <= 1; col_iter++) {
			if (cell.col + col_iter >= 0 && cell.col + col_iter < maze_solver::im_width) {
				if (cell.row + row_iter >= 0 && cell.row + row_iter < maze_solver::im_height) {
					if (abs(row_iter) != abs(col_iter)) {
						myTuple cell_neigh;
						cell_neigh.row = cell.row + row_iter;
						cell_neigh.col = cell.col + col_iter;
						//neighbors.push_back(cell);
						if (!maze_solver::wall_exists(cell, cell_neigh)) {
							neighbors.push_back(cell_neigh);
						}
						else {
							cout << "WALL BETWEEN (" << cell.row << ", " << cell.col << ") and (" << cell_neigh.row << ", " << cell_neigh.col << ")" << endl;
						}
					}
				}
			}
		}
	}
	return neighbors;
}

bool maze_solver::wall_exists(myTuple cell1, myTuple cell2) {
	/*
		* FUNCTION: To check if a wall exists between two cells.
		* INPUT: two cells (myTuple)
		* OUTPUT: TRUE if wall exists, FALSE otherwise
	*/
	Mat croppedImage;
	int start_x = cell1.col* maze_solver::cell_width;
	int start_y = cell1.row * maze_solver::cell_width;
	Rect myROI(start_x, start_y, maze_solver::cell_width, maze_solver::cell_width);
	croppedImage = maze_solver::image(myROI);
	int width = croppedImage.cols;
	int height = croppedImage.rows;
	int _stride = croppedImage.step;
	uint8_t *img_data = croppedImage.data;
	int start = (int)(maze_solver::cell_width * 3 / 10);
	int end = (int)(maze_solver::cell_width * 7 / 10);
	//cout << croppedImage << endl << endl;
	if (cell1.row == cell2.row) { // Same row
		if (cell1.col < cell2.col) { //cell1 to the left of cell2
			//check the right wall of cell1
			for (int row_iter = start; row_iter <= end; row_iter++) {
				uint8_t val = img_data[(row_iter * _stride + width)];
				if (val == 0) {
					//cout << "RIGHT WALL\n";
					return 1;
				}
			}
		}
		else if (cell1.col > cell2.col) { //cell1 to the right of cell2
			//check the left wall
			for (int row_iter = start; row_iter <= end; row_iter++) {
				uint8_t val = img_data[row_iter * _stride + 0];
				if (val == 0) {
					//cout << "LEFT WALL\n";
					return 1;
				}
			}
		}
	}
	else if (cell1.col == cell2.col) {
		if (cell1.row < cell2.row) { //cell1 above cell2
			//check the bottom wall
			for (int col_iter = start; col_iter <= end; col_iter++) {
				uint8_t val = img_data[height * _stride + col_iter];
				if (val == 0) {
					//cout << "BOTTOM WALL\n";
					return 1;
				}
			}
		}
		else if (cell1.row > cell2.row) { //cell1 below cell2
			//check the top wall
			for (int col_iter = start; col_iter <= end; col_iter++) {
				uint8_t val = img_data[0 * _stride + col_iter];
				if (val == 0) {
					//cout << "TOP WALL\n";
					return 1;
				}
			}
		}	
	}
	else if (cell1.col != cell2.col && cell1.row != cell2.row) {
		return 1;
	}
	return 0;
}
