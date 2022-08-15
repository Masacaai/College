/*  
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This file contains the templated class Grid that is used to create mazes
*/

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
 private:
    struct CELL {
        CELL* Next;
        T Val;
        size_t NumCols;  // total # of columns (0..NumCols-1)
        CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
            Next = _Next;
            Val = _Val;
            NumCols = _NumCols;
        }
    };

    size_t NumRows;  // total # of rows (0..NumRows-1)
    CELL** Rows;     // C array of linked lists
 public:
    /* Default constructor:
     *
     * Called automatically by C++ to construct a 4x4 Grid.  All
     * elements are initialized to the default value of T.
     */
    Grid() {
        // initialize 4 rows
        Rows = new CELL*[4];
        NumRows = 4;

        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), 4);
            CELL* cur = Rows[r];

            // create the linked list for this row.
            for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
    }

    /* Parameterized constructor:
     *
     * Called automatically by C++ to construct a Grid with R rows,
     * where each row has C columns. All elements are initialized to
     * the default value of T.
     */
    Grid(size_t R, size_t C) {
        if (R == 0) {
            throw out_of_range("r cannot be 0");
        }
        if (C == 0) {
            throw out_of_range("c cannot be 0");
        }

        // initialize R rows
        Rows = new CELL*[R];
        NumRows = R;

        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), C);
            CELL* cur = Rows[r];

            // create the linked list for this row.
            for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
    }

    /* Destructor:
     *
     * Called automatically by C++ to free the memory associated by the vector.
     */
    virtual ~Grid() {
        for (size_t r = 0; r < this->NumRows; ++r) {
            CELL* curr = this->Rows[r];
            CELL* prev = nullptr;
            while (curr != nullptr) {
                prev = curr;
                curr = curr->Next;
                delete prev;
            }
        }
        delete[] Rows; // Delete array at the end
    }
    
    /* Copy constructor:
     *
     * Called automatically by C++ to construct a Grid that contains a
     * copy of an existing Grid.
     */
    Grid(const Grid<T>& other) {
        // initialize R rows
        this->Rows = new CELL*[other.NumRows];
        this->NumRows = other.NumRows;

        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < this->NumRows; ++r) {
            this->Rows[r] = new CELL(nullptr, other.Rows[r]->Val, other.Rows[r]->NumCols);
            CELL* cur = this->Rows[r];
            CELL* otherCur = other.Rows[r]->Next;

            // create the linked list for this row.
            for(size_t c = 1; c < this->Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, otherCur->Val);
                cur = cur->Next;
                otherCur = otherCur->Next;
            }
        }
    }

    /* Copy operator=
     *
     * Called when you assign one vector into another, i.e. this = other;
     */
    Grid& operator=(const Grid& other) {
        // Check if we are assigning to ourself
        if (this == &other) {
            return *this;
        }

        // Delete pre-existing grid
        for (size_t r = 0; r < this->NumRows; ++r) {
            CELL* curr = this->Rows[r];
            CELL* prev = nullptr;
            while (curr != nullptr) {
                prev = curr;
                curr = curr->Next;
                delete prev;
            }
        }
        delete[] Rows;

        // initialize R rows
        this->Rows = new CELL*[other.NumRows];
        this->NumRows = other.NumRows;

        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < this->NumRows; ++r) {
            this->Rows[r] = new CELL(nullptr, other.Rows[r]->Val, other.Rows[r]->NumCols);
            CELL* cur = this->Rows[r];
            CELL* otherCur = other.Rows[r]->Next;

            // create the linked list for this row.
            for(size_t c = 1; c < this->Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, otherCur->Val);
                cur = cur->Next;
                otherCur = otherCur->Next;
            }
        }
        return *this;
    }

    /* numrows
     *
     * Returns the # of rows in the Grid.  The indices for these rows
     * are 0..numrows-1.
     */
    size_t numrows() const {
        return NumRows;
    }

    /* numcols
     *
     * Returns the # of columns in row r.  The indices for these columns
     * are 0..numcols-1.  For now, each row will have the same number of columns.
     */
    size_t numcols(size_t r) const {
        return Rows[r]->NumCols;
    }

    /* size
     *
     * Returns the total # of elements in the grid.
     */
    size_t size() const {
        return NumRows * Rows[0]->NumCols;
    }

    /* Access operator()
     *
     * Returns a reference to the element at location (r, c); this
     * allows you to access the element or change it.
     */
    T& operator()(size_t r, size_t c) {
        if ( r >= NumRows) {
            throw out_of_range("r is out of range.");
        }

        CELL* cur = this->Rows[r];
        for (size_t i = 0; i < this->Rows[r]->NumCols; ++i) {
            if (i == c) { // If current column is the requested column...
                return cur->Val;
            }
            cur = cur->Next;
        }
        // If the program reaches this point, it means c wasn't found
        throw out_of_range("c is out of range.");
    }

    /* _output
     *
     * Outputs the contents of the grid; for debugging purposes.  This is not
     * tested.
     */
    void _output() {
        cout << "*** OUTPUT START ***" << endl
             << " ## Size of the grid: " << NumRows << " x " << Rows[0]->NumCols << endl;
        cout << "        ";
        for (size_t i = 0; i < Rows[0]->NumCols; ++i) {
            cout << "<" << i << "> ";
        }
        cout << endl;
        for (size_t r = 0; r < NumRows; ++r) {
            CELL* cur = Rows[r];
            cout << "    <" << r << "> ";
            for (size_t c = 0; c < Rows[r]->NumCols; ++c) {
                cout << " " << cur->Val << "  ";
                cur = cur->Next;
            }
            cout << endl;
        }
        cout << "*** OUTPUT END ***" << endl;
    }
};

