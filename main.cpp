#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

const int BOARD_SIZE = 9;
const vector<char> sudoku_nums_char = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
const vector<int> sudoku_nums_int = {1, 2, 3, 4, 5, 6, 7, 8, 9};


class Box {

    public:
        vector<int> pos;
        vector<char> possible_vals;
        char value;

        Box(vector<int> pos, char value) {

            this -> pos = pos;
            this -> value = value;
        }

        void print_box_info() {

            cout << "Coordinates: " << pos[0] << " " << pos[1] << endl;
            cout << "Value: " << value << endl;
        }

        void remove_existing_vals(const vector<char> &values, vector<char> &valid_nums) {

            for(char num : values) {
                for(int i = 0; i < valid_nums.size(); i++) {

                    if(num == valid_nums[i]) {
                        valid_nums.erase(valid_nums.begin() + i);
                    }
                }
            }
        }

        void create_possible_vals(const vector<char> &horizontal_vals, const vector<char> &vertical_vals, const vector<char> &table_vals) {
            
            vector<char> valid_nums = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

            remove_existing_vals(horizontal_vals, valid_nums);

            remove_existing_vals(vertical_vals, valid_nums);

            remove_existing_vals(table_vals, valid_nums);
        }
};


void evaluator(const vector<Box> &all_boxes, vector<vector<char>> &table_vals, int row, int j) {

    int less_than;
    int more_than;
    int table_vals_column_start;

    if(row == 1) {
        more_than = -1;
        table_vals_column_start = 0;
    }

    else if(row == 2) {
        more_than = 2;
        table_vals_column_start = 3;
    }

    else if(row == 3) {
        more_than = 5;
        table_vals_column_start = 6;
    }

    else {
        throw "'int row' in function 'evaluator' can only be 1, 2, or 3. ";
    }

    less_than = more_than + 3;

    if(all_boxes[j].pos[0] > more_than && all_boxes[j].pos[0] <= less_than) {
        if(all_boxes[j].pos[1] <= 2) {
            table_vals[table_vals_column_start].push_back(all_boxes[j].value);
        }

        else if(all_boxes[j].pos[1] > 2 && all_boxes[j].pos[1] <= 5) {
            table_vals[table_vals_column_start + 1].push_back(all_boxes[j].value);
        }

        else if(all_boxes[j].pos[1] > 5 && all_boxes[j].pos[1] <= 8) {
            table_vals[table_vals_column_start + 2].push_back(all_boxes[j].value);
        }
    }
}


int main() {

    ofstream write_file;
    ifstream read_file;
    string filename = "board.txt";
    string board;
    vector<int> lines;
    vector<vector<char>> values;
    vector<Box> all_boxes;

    read_file.open(filename);

    for(int i = 0; i < BOARD_SIZE; i++) {
        getline(read_file, board);
        
        for(int j = 0; j < board.size(); j++) {
            // cout << board[j] << endl; // Delete this later
            vector<int> coords = {i, j};

            all_boxes.push_back(Box(coords, board[j]));
        }
    }

    vector<vector<char>> horizontal_existing_vals;
    vector<vector<char>> vertical_existing_vals;
    vector<vector<char>> table_existing_vals;

    for(int i = 0; i < BOARD_SIZE; i++) {
        horizontal_existing_vals.push_back(vector<char>());
        vertical_existing_vals.push_back(vector<char>());
        table_existing_vals.push_back(vector<char>());
    }

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < all_boxes.size(); j++) {

            if(all_boxes[j].pos[0] == i && all_boxes[j].value != 'x') {
                horizontal_existing_vals[i].push_back(all_boxes[j].value);
            }

            if(all_boxes[j].pos[1] == i && all_boxes[j].value != 'x') {
                vertical_existing_vals[i].push_back(all_boxes[j].value);
            }
        }
    }

    for(int j = 0; j < all_boxes.size(); j++) {

        if(all_boxes[j].value != 'x') {

            evaluator(all_boxes, table_existing_vals, 1, j);
            evaluator(all_boxes, table_existing_vals, 2, j);
            evaluator(all_boxes, table_existing_vals, 3, j);
        }
    }

    read_file.close();

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < all_boxes.size(); j++) {

        }
    }

    return 0;
}