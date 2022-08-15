/*  
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This file contains unit tests implemented with the Google Test Framework.
*/

#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"

// Tests the default constructor
TEST(grid, defaultConstructor){
    Grid<char> g1;
    EXPECT_EQ(g1.size(), 16);
    EXPECT_EQ(g1.numrows(), 4);
    for (size_t r = 0; r < g1.numrows(); ++r) {
        EXPECT_EQ(g1.numcols(r), 4);
        for (size_t c = 0; c < g1.numcols(r); ++c) {
            EXPECT_EQ(g1(r, c), '\0');
        }    
    }
    
    Grid<int> g2;
    EXPECT_EQ(g2.size(), 16);
    EXPECT_EQ(g2.numrows(), 4);
    for (size_t r = 0; r < g2.numrows(); ++r) {
        EXPECT_EQ(g1.numcols(r), 4);
        for (size_t c = 0; c < g2.numcols(r); ++c) {
            EXPECT_EQ(g2(r, c), 0);
        }    
    }

    Grid<double> g3;
    EXPECT_EQ(g3.size(), 16);
    EXPECT_EQ(g3.numrows(), 4);
    for (size_t r = 0; r < g3.numrows(); ++r) {
        EXPECT_EQ(g3.numcols(r), 4);
        for (size_t c = 0; c < g3.numcols(r); ++c) {
            EXPECT_EQ(g3(r, c), 0);
        }    
    }

    Grid<string> g4;
    EXPECT_EQ(g4.size(), 16);
    EXPECT_EQ(g4.numrows(), 4);
    for (size_t r = 0; r < g4.numrows(); ++r) {
        EXPECT_EQ(g4.numcols(r), 4);
        for (size_t c = 0; c < g4.numcols(r); ++c) {
            EXPECT_EQ(g4(r, c), "");
        }    
    }

}

// Tests the parameterized constructor's ability to handle zero values
TEST(grid, paramConstructorZeroValues){
    try {
        Grid<int> g1(0, 0);  
    } catch(exception& e) {
        string s(e.what()); 
        EXPECT_EQ(s, "r cannot be 0");
    }
    try {
        Grid<char> g1(0, 0);  
    } catch(exception& e) {
        string s(e.what()); 
        EXPECT_EQ(s, "r cannot be 0");
    }
    try {
        Grid<double> g1(0, 0);  
    } catch(exception& e) {
        string s(e.what()); 
        EXPECT_EQ(s, "r cannot be 0");
    }
    try {
        Grid<string> g1(0, 0);  
    } catch(exception& e) {
        string s(e.what()); 
        EXPECT_EQ(s, "r cannot be 0");
    }
    try {
        Grid<int> g1(1, 0);
    } catch(exception& e) {
        string s(e.what());  
        EXPECT_EQ(s, "c cannot be 0");
    }

    try {
        Grid<char> g1(1, 0);
    } catch(exception& e) {
        string s(e.what());  
        EXPECT_EQ(s, "c cannot be 0");
    }

    try {
        Grid<double> g1(1, 0);
    } catch(exception& e) {
        string s(e.what());  
        EXPECT_EQ(s, "c cannot be 0");
    }

    try {
        Grid<string> g1(1, 0);
    } catch(exception& e) {
        string s(e.what());  
        EXPECT_EQ(s, "c cannot be 0");
    }
}

// Tests the parameterized constructor
TEST(grid, paramConstructor){
    
    for (int i = 0; i < 100; ++i) {
        size_t R = (rand() % 100) + 1; // +1 ensures R != 0
        size_t C = (rand() % 100) + 1; // +1 ensures C != 0
        size_t S = R * C;
        
        Grid<char> g1(R, C);
        EXPECT_EQ(g1.size(), S);
        EXPECT_EQ(g1.numrows(), R);
        for (size_t r = 0; r < g1.numrows(); ++r) {
            EXPECT_EQ(g1.numcols(r), C);
            for (size_t c = 0; c < g1.numcols(r); ++c) {
                EXPECT_EQ(g1(r, c), '\0');
            }    
        }

        Grid<int> g2(R, C);
        EXPECT_EQ(g2.size(), S);
        EXPECT_EQ(g2.numrows(), R);
        for (size_t r = 0; r < g2.numrows(); ++r) {
            EXPECT_EQ(g1.numcols(r), C);
            for (size_t c = 0; c < g2.numcols(r); ++c) {
                EXPECT_EQ(g2(r, c), 0);
            }    
        }

        Grid<double> g3(R, C);
        EXPECT_EQ(g3.size(), S);
        EXPECT_EQ(g3.numrows(), R);
        for (size_t r = 0; r < g3.numrows(); ++r) {
            EXPECT_EQ(g3.numcols(r), C);
            for (size_t c = 0; c < g3.numcols(r); ++c) {
                EXPECT_EQ(g3(r, c), 0);
            }    
        }

        Grid<string> g4(R, C);
        EXPECT_EQ(g4.size(), S);
        EXPECT_EQ(g4.numrows(), R);
        for (size_t r = 0; r < g4.numrows(); ++r) {
            EXPECT_EQ(g4.numcols(r), C);
            for (size_t c = 0; c < g4.numcols(r); ++c) {
                EXPECT_EQ(g4(r, c), "");
            }    
        }
    }
}

// Tests the copy constructor
TEST(grid, copyConstructor){
    string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiklmnopqrstuvwxyz";
    for (int i = 0; i < 100; ++i) {
        size_t R = (rand() % 100) + 1; // +1 ensures R != 0
        size_t C = (rand() % 100) + 1; // +1 ensures C != 0
        size_t S = R * C;

        Grid<int> g1a(R, C);
        for (int r = 0; r < g1a.numrows(); ++r) {
            for (int c = 0; c < g1a.numcols(r); ++c) {
                g1a(r, c) = r * c;
            }
        }
        Grid<int> g1b(g1a);
        EXPECT_EQ(g1b.size(), S);
        EXPECT_EQ(g1b.numrows(), R);
        for (int r = 0; r < g1b.numrows(); ++r) {
            EXPECT_EQ(g1b.numcols(r), C);
            for (int c = 0; c < g1b.numcols(r); ++c) {
                EXPECT_EQ(g1b(r, c), r * c);
            }
        }
        // Changing one grid and making sure the other grid does not change
        g1a(R - 1, C - 1) = 101;
        EXPECT_FALSE(g1a(R - 1, C - 1) == g1b(R - 1, C - 1));

        Grid<char> g2a(R, C);
        for (int r = 0; r < g2a.numrows(); ++r) {
            for (int c = 0; c < g2a.numcols(r); ++c) {
                g2a(r, c) = s[(r * c) % 52];
            }
        }
        Grid<char> g2b(g2a);
        EXPECT_EQ(g2b.size(), S);
        EXPECT_EQ(g2b.numrows(), R);
        for (int r = 0; r < g2b.numrows(); ++r) {
            EXPECT_EQ(g2b.numcols(r), C);
            for (int c = 0; c < g2b.numcols(r); ++c) {
                EXPECT_EQ(g2b(r, c), s[(r * c) % 52]);
            }
        }
        // Changing one grid and making sure the other grid does not change
        g2a(R - 1, C - 1) = '\0';
        EXPECT_FALSE(g2a(R - 1, C - 1) == g2b(R - 1, C - 1)); 

        Grid<double> g3a(R, C);
        for (int r = 0; r < g3a.numrows(); ++r) {
            for (int c = 0; c < g3a.numcols(r); ++c) {
                g3a(r, c) = r * c * 0.1;
            }
        }
        Grid<double> g3b(g3a);
        EXPECT_EQ(g3b.size(), S);
        EXPECT_EQ(g3b.numrows(), R);
        for (int r = 0; r < g3b.numrows(); ++r) {
            EXPECT_EQ(g3b.numcols(r), C);
            for (int c = 0; c < g3b.numcols(r); ++c) {
                EXPECT_EQ(g3b(r, c), r * c * 0.1);
            }
        }
        // Changing one grid and making sure the other grid does not change
        g3a(R - 1, C - 1) = 101;
        EXPECT_FALSE(g3a(R - 1, C - 1) == g3b(R - 1, C - 1));

        Grid<string> g4a(R, C);
        for (int r = 0; r < g4a.numrows(); ++r) {
            for (int c = 0; c < g4a.numcols(r); ++c) {
                g4a(r, c) = s.substr((r * c) % 52, 1);
            }
        }
        Grid<string> g4b(g4a);
        EXPECT_EQ(g4b.size(), S);
        EXPECT_EQ(g4b.numrows(), R);
        for (int r = 0; r < g4b.numrows(); ++r) {
            EXPECT_EQ(g4b.numcols(r), C);
            for (int c = 0; c < g4b.numcols(r); ++c) {
                EXPECT_EQ(g4b(r, c), s.substr((r * c) % 52, 1));
            }
        }
        // Changing one grid and making sure the other grid does not change
        g4a(R - 1, C - 1) = "";
        EXPECT_FALSE(g4a(R - 1, C - 1) == g4b(R - 1, C - 1));

    }
}

// Tests the copy operator used during initialization of new grids
TEST(grid, copyOperatorInitialization){
    string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiklmnopqrstuvwxyz";
    for (int i = 0; i < 100; ++i) {
        size_t R = (rand() % 100) + 1; // +1 ensures R != 0
        size_t C = (rand() % 100) + 1; // +1 ensures C != 0
        size_t S = R * C;

        Grid<int> g1a(R, C);
        for (int r = 0; r < g1a.numrows(); ++r) {
            for (int c = 0; c < g1a.numcols(r); ++c) {
                g1a(r, c) = r * c;
            }
        }
        Grid<int> g1b = g1a;
        EXPECT_EQ(g1b.size(), S);
        EXPECT_EQ(g1b.numrows(), R);
        for (int r = 0; r < g1b.numrows(); ++r) {
            EXPECT_EQ(g1b.numcols(r), C);
            for (int c = 0; c < g1b.numcols(r); ++c) {
                EXPECT_EQ(g1b(r, c), r * c);
            }
        }
        // Changing one grid and making sure the other grid does not change
        g1a(R - 1, C - 1) = 101;
        EXPECT_FALSE(g1a(R - 1, C - 1) == g1b(R - 1, C - 1)); 

        Grid<char> g2a(R, C);
        for (int r = 0; r < g2a.numrows(); ++r) {
            for (int c = 0; c < g2a.numcols(r); ++c) {
                g2a(r, c) = s[(r * c) % 52];
            }
        }
        Grid<char> g2b = g2a;
        EXPECT_EQ(g2b.size(), S);
        EXPECT_EQ(g2b.numrows(), R);
        for (int r = 0; r < g2b.numrows(); ++r) {
            EXPECT_EQ(g2b.numcols(r), C);
            for (int c = 0; c < g2b.numcols(r); ++c) {
                EXPECT_EQ(g2b(r, c), s[(r * c) % 52]);
            }
        }
        // Changing one grid and making sure the other grid does not change
        g2a(R - 1, C - 1) = '\0';
        EXPECT_FALSE(g2a(R - 1, C - 1) == g2b(R - 1, C - 1));

        Grid<double> g3a(R, C);
        for (int r = 0; r < g3a.numrows(); ++r) {
            for (int c = 0; c < g3a.numcols(r); ++c) {
                g3a(r, c) = r * c * 0.1;
            }
        }
        Grid<double> g3b = g3a;
        EXPECT_EQ(g3b.size(), S);
        EXPECT_EQ(g3b.numrows(), R);
        for (int r = 0; r < g3b.numrows(); ++r) {
            EXPECT_EQ(g3b.numcols(r), C);
            for (int c = 0; c < g3b.numcols(r); ++c) {
                EXPECT_EQ(g3b(r, c), r * c * 0.1);
            }
        }
        // Changing one grid and making sure the other grid does not change
        g3a(R - 1, C - 1) = 101;
        EXPECT_FALSE(g3a(R - 1, C - 1) == g3b(R - 1, C - 1));

        Grid<string> g4a(R, C);
        for (int r = 0; r < g4a.numrows(); ++r) {
            for (int c = 0; c < g4a.numcols(r); ++c) {
                g4a(r, c) = s.substr((r * c) % 52, 1);
            }
        }
        Grid<string> g4b = g4a;
        EXPECT_EQ(g4b.size(), S);
        EXPECT_EQ(g4b.numrows(), R);
        for (int r = 0; r < g4b.numrows(); ++r) {
            EXPECT_EQ(g4b.numcols(r), C);
            for (int c = 0; c < g4b.numcols(r); ++c) {
                EXPECT_EQ(g4b(r, c), s.substr((r * c) % 52, 1));
            }
        }
        // Changing one grid and making sure the other grid does not change
        g4a(R - 1, C - 1) = "";
        EXPECT_FALSE(g4a(R - 1, C - 1) == g4b(R - 1, C - 1));
    }
}

// Tests the copy operator used on pre-existing grids
TEST(grid, copyOperatorPreExisting){
    string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiklmnopqrstuvwxyz";
    for (int i = 0; i < 100; ++i) {
        size_t R = (rand() % 100) + 1; // +1 ensures R != 0
        size_t C = (rand() % 100) + 1; // +1 ensures C != 0
        size_t S = R * C;

        Grid<int> g1a(R, C);
        for (int r = 0; r < g1a.numrows(); ++r) {
            for (int c = 0; c < g1a.numcols(r); ++c) {
                g1a(r, c) = r * c;
            }
        }
        Grid<int> g1b(R, C);
        for (int r = 0; r < g1b.numrows(); ++r) {
            for (int c = 0; c < g1b.numcols(r); ++c) {
                g1b(r, c) = r + c;
            }
        }
        g1b = g1a;
        EXPECT_EQ(g1b.size(), S);
        EXPECT_EQ(g1b.numrows(), R);
        for (int r = 0; r < g1b.numrows(); ++r) {
            EXPECT_EQ(g1b.numcols(r), C);
            for (int c = 0; c < g1b.numcols(r); ++c) {
                EXPECT_EQ(g1b(r, c), r * c);
            }
        }
        // Changing one grid and making sure the other grid does not change
        g1a(R - 1, C - 1) = 101;
        EXPECT_FALSE(g1a(R - 1, C - 1) == g1b(R - 1, C - 1)); 

        Grid<char> g2a(R, C);
        for (int r = 0; r < g2a.numrows(); ++r) {
            for (int c = 0; c < g2a.numcols(r); ++c) {
                g2a(r, c) = s[(r * c) % 52];
            }
        }
        Grid<char> g2b(R, C); 
        for (int r = 0; r < g2b.numrows(); ++r) {
            for (int c = 0; c < g2b.numcols(r); ++c) {
                g2b(r, c) = s[(r + c) % 52];
            }
        }
        g2b = g2a;
        EXPECT_EQ(g2b.size(), S);
        EXPECT_EQ(g2b.numrows(), R);
        for (int r = 0; r < g2b.numrows(); ++r) {
            EXPECT_EQ(g2b.numcols(r), C);
            for (int c = 0; c < g2b.numcols(r); ++c) {
                EXPECT_EQ(g2b(r, c), s[(r * c) % 52]);
            }
        }
        // Changing one grid and making sure the other grid does not change
        g2a(R - 1, C - 1) = '\0';
        EXPECT_FALSE(g2a(R - 1, C - 1) == g2b(R - 1, C - 1));

        Grid<double> g3a(R, C);
        for (int r = 0; r < g3a.numrows(); ++r) {
            for (int c = 0; c < g3a.numcols(r); ++c) {
                g3a(r, c) = r * c * 0.1;
            }
        }
        Grid<double> g3b(R, C); 
        for (int r = 0; r < g3b.numrows(); ++r) {
            for (int c = 0; c < g3b.numcols(r); ++c) {
                g3b(r, c) = (r + c) * 0.1;
            }
        }
        g3b = g3a;
        EXPECT_EQ(g3b.size(), S);
        EXPECT_EQ(g3b.numrows(), R);
        for (int r = 0; r < g3b.numrows(); ++r) {
            EXPECT_EQ(g3b.numcols(r), C);
            for (int c = 0; c < g3b.numcols(r); ++c) {
                EXPECT_EQ(g3b(r, c), r * c * 0.1);
            }
        }
        // Changing one grid and making sure the other grid does not change
        g3a(R - 1, C - 1) = 101;
        EXPECT_FALSE(g3a(R - 1, C - 1) == g3b(R - 1, C - 1));

        Grid<string> g4a(R, C);
        for (int r = 0; r < g4a.numrows(); ++r) {
            for (int c = 0; c < g4a.numcols(r); ++c) {
                g4a(r, c) = s.substr((r * c) % 52, 1);
            }
        }
        Grid<string> g4b(R, C); 
        for (int r = 0; r < g4b.numrows(); ++r) {
            for (int c = 0; c < g4b.numcols(r); ++c) {
                g4b(r, c) = s.substr((r + c) % 52, 1);
            }
        }
        g4b = g4a;
        EXPECT_EQ(g4b.size(), S);
        EXPECT_EQ(g4b.numrows(), R);
        for (int r = 0; r < g4b.numrows(); ++r) {
            EXPECT_EQ(g4b.numcols(r), C);
            for (int c = 0; c < g4b.numcols(r); ++c) {
                EXPECT_EQ(g4b(r, c), s.substr((r * c) % 52, 1));
            }
        }
        // Changing one grid and making sure the other grid does not change
        g4a(R - 1, C - 1) = "";
        EXPECT_FALSE(g4a(R - 1, C - 1) == g4b(R - 1, C - 1));
    }
}

// Tests the numrows function
TEST(grid, numrows){
    for (int i = 0; i < 100; ++i) {
        size_t R = (rand() % 100) + 1; // +1 ensures R != 0
        
        Grid<char> g1(R, 1);
        EXPECT_EQ(g1.numrows(), R);

        Grid<int> g2(R, 1);
        EXPECT_EQ(g2.numrows(), R);

        Grid<double> g3(R, 1);
        EXPECT_EQ(g3.numrows(), R);

        Grid<string> g4(R, 1);
        EXPECT_EQ(g4.numrows(), R);
        
    }
}

// Tests the numcols function
TEST(grid, numcols){
    for (int i = 0; i < 100; ++i) {
        size_t C = (rand() % 100) + 1; // +1 ensures C != 0
        
        Grid<char> g1(1, C);
        for (size_t r = 0; r < g1.numrows(); ++r) {
            EXPECT_EQ(g1.numcols(r), C);
        }

        Grid<int> g2(1, C);
        for (size_t r = 0; r < g2.numrows(); ++r) {
            EXPECT_EQ(g1.numcols(r), C);
        }

        Grid<double> g3(1, C);
        for (size_t r = 0; r < g3.numrows(); ++r) {
            EXPECT_EQ(g3.numcols(r), C);
        }

        Grid<string> g4(1, C);
        for (size_t r = 0; r < g4.numrows(); ++r) {
            EXPECT_EQ(g4.numcols(r), C);
        }
    }
}

// Tests the size function
TEST(grid, size){
    for (int i = 0; i < 100; ++i) {
        size_t R = (rand() % 100) + 1; // +1 ensures R != 0
        size_t C = (rand() % 100) + 1; // +1 ensures C != 0
        size_t S = R * C;
        
        Grid<char> g1(R, C);
        EXPECT_EQ(g1.size(), S);

        Grid<int> g2(R, C);
        EXPECT_EQ(g2.size(), S);

        Grid<double> g3(R, C);
        EXPECT_EQ(g3.size(), S);

        Grid<string> g4(R, C);
        EXPECT_EQ(g4.size(), S);
        
    }
}

// Tests the access operator's ability to handle invalid indices
TEST(grid, accessOperatorInvalid){
    string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiklmnopqrstuvwxyz";
    for (int i = 0; i < 100; ++i) {
        size_t R = (rand() % 100) + 1; // +1 ensures R != 0
        size_t C = (rand() % 100) + 1; // +1 ensures C != 0
        
        Grid<char> g1(R, C);
        try {
            char ch = g1(R, 0);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "r is out of range.");
        }
        try {
            char ch = g1(R + 1, 0);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "r is out of range.");
        }
        try {
            char ch = g1(0, C);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "c is out of range.");
        }
        try {
            char ch = g1(0, C + 1);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "c is out of range.");
        }

        Grid<int> g2(R, C);
        try {
            int n = g2(R, 0);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "r is out of range.");
        }
        try {
            int n = g2(R + 1, 0);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "r is out of range.");
        }
        try {
            int n = g2(0, C);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "c is out of range.");
        }
        try {
            int n = g2(0, C + 1);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "c is out of range.");
        }

        Grid<double> g3(R, C);
        try {
            double d = g3(R, 0);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "r is out of range.");
        }
        try {
            double d = g3(R + 1, 0);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "r is out of range.");
        }
        try {
            double d = g3(0, C);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "c is out of range.");
        }
        try {
            double d = g3(0, C + 1);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "c is out of range.");
        }

        Grid<string> g4(R, C);
        try {
            string str = g4(R, 0);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "r is out of range.");
        }
        try {
            string str = g4(R + 1, 0);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "r is out of range.");
        }
        try {
            string str = g4(0, C);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "c is out of range.");
        }
        try {
            string str = g4(0, C + 1);
        } catch(exception& e) {
            string s(e.what());  
            EXPECT_EQ(s, "c is out of range.");
        }
    }
}

// Tests the access operator
TEST(grid, accessOperator){
    string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiklmnopqrstuvwxyz";
    for (int i = 0; i < 100; ++i) {
        size_t R = (rand() % 100) + 1; // +1 ensures R != 0
        size_t C = (rand() % 100) + 1; // +1 ensures C != 0
        
        Grid<char> g1(R, C);
        char arr1[R][C];
        for (size_t r = 0; r < g1.numrows(); ++r) {
            for (size_t c = 0; c < g1.numcols(r); ++c) {
                char ch = s[(r * c) % 52];
                arr1[r][c] = ch;
                g1(r, c) = ch;
                EXPECT_EQ(g1(r, c), arr1[r][c]);
            }    
        }

        Grid<int> g2(R, C);
        int arr2[R][C];
        for (size_t r = 0; r < g2.numrows(); ++r) {
            for (size_t c = 0; c < g2.numcols(r); ++c) {
                int n = r * c;
                arr2[r][c] = n;
                g2(r, c) = n;
                EXPECT_EQ(g2(r, c), arr2[r][c]);
            }    
        }

        Grid<double> g3(R, C);
        double arr3[R][C];
        for (size_t r = 0; r < g3.numrows(); ++r) {
            for (size_t c = 0; c < g3.numcols(r); ++c) {
                double n = r * c * 0.1;
                arr3[r][c] = n;
                g3(r, c) = n;
                EXPECT_EQ(g3(r, c), arr3[r][c]);
            }    
        }

        Grid<string> g4(R, C);
        string arr4[R][C];
        for (size_t r = 0; r < g4.numrows(); ++r) {
            for (size_t c = 0; c < g4.numcols(r); ++c) {
                string str = s.substr((r * c) % 52, 1);
                arr4[r][c] = str;
                g4(r, c) = str;
                EXPECT_EQ(g4(r, c), arr4[r][c]);
            }    
        }
    }
}

// Provided Test: sample maze from handout, make lots more yourself!
TEST(maze, basic) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);

    MazeCell* start = m.getStart(2, 2);

    /* These paths are the ones in the handout. They all work. */
    EXPECT_TRUE(isPathToFreedom(start, "ESNWWNNEWSSESWWN"));
    EXPECT_TRUE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES"));
    EXPECT_TRUE(isPathToFreedom(start, "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT_FALSE(isPathToFreedom(start, "ESNW"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWN"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT_FALSE(isPathToFreedom(start, "WW"));
    EXPECT_FALSE(isPathToFreedom(start, "NN"));
    EXPECT_FALSE(isPathToFreedom(start, "EE"));
    EXPECT_FALSE(isPathToFreedom(start, "SS"));
}

// Provided Test: don't allow going through walls
TEST(maze, tryingToGoThroughWalls) {
    vector<string> textMaze;

    textMaze.push_back("* S *");
    textMaze.push_back("     ");
    textMaze.push_back("W * P");
    textMaze.push_back("     ");
    textMaze.push_back("* * *");

    Maze m(textMaze);

    MazeCell* start = m.getStart(1, 1);

    EXPECT_FALSE(isPathToFreedom(start, "WNEES"));
    EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
    EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
    EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}

// Provided Test: Works when starting on an item
TEST(maze, startOnItem) {
    vector<string> textMaze;

    textMaze.push_back("P-S-W");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    EXPECT_TRUE(isPathToFreedom(start, "EE"));
    start = m.getStart(0, 1);
    EXPECT_TRUE(isPathToFreedom(start, "WEE"));
    start = m.getStart(0, 2);
    EXPECT_TRUE(isPathToFreedom(start, "WW"));
}

// Provided Test: Reports errors if given illegal characters.
TEST(maze, invalidChar) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    /* These paths contain characters that aren't even close to permissible. */
    EXPECT_FALSE(isPathToFreedom(start, "Q"));
    EXPECT_FALSE(isPathToFreedom(start, "X"));
    EXPECT_FALSE(isPathToFreedom(start, "!"));
    EXPECT_FALSE(isPathToFreedom(start, "?"));

    EXPECT_FALSE(isPathToFreedom(start, "n"));
    EXPECT_FALSE(isPathToFreedom(start, "s"));
    EXPECT_FALSE(isPathToFreedom(start, "e"));
    EXPECT_FALSE(isPathToFreedom(start, "w"));

    ///* These are tricky - they're legal paths that happen to have an unexpected
    // * character at the end.
    start = m.getStart(2, 2);
    EXPECT_FALSE(isPathToFreedom(start, "ESNWWNNEWSSESWWNQ"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES!!!"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNEWSSESWWNSEENES??"));

}

// Provided Test: This tests your personalized regular maze to see if you were
// able to escape.
TEST(maze, escapeRegularMaze) {
    Maze m(4, 4);
    MazeCell* start = m.mazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfRegularMaze));
}

// Provided Test: This tests your personalized twisty maze to see if you were
// able to escape.
TEST(maze, escapeTwistyMaze) {
    Maze m(4, 4);
    MazeCell* start = m.twistyMazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfTwistyMaze));
}

// Tests a variety of things with a sample maze
TEST(maze, AllPurposeMaze1) {
    vector<string> textMaze;
    textMaze.push_back("* S P-*");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-*-*-*");
    textMaze.push_back("  |    ");
    textMaze.push_back("*-*-* W");
    textMaze.push_back("  |   |");
    textMaze.push_back("*-*-*-*");

    Maze m(textMaze);

    MazeCell* start = m.getStart(0, 0);

    // Paths that pick up all the items
    EXPECT_TRUE(isPathToFreedom(start, "SENSEENWESWWSSEEN"));
    EXPECT_TRUE(isPathToFreedom(start, "SEEENWESWWNSSSEEN"));
    EXPECT_TRUE(isPathToFreedom(start, "SESSEENSWWNNNSEENW"));
    EXPECT_TRUE(isPathToFreedom(start, "SESSEENSWWNNEENWESWWN"));

    // Paths that don't pick up all the items
    EXPECT_FALSE(isPathToFreedom(start, "SENS"));
    EXPECT_FALSE(isPathToFreedom(start, "SEEEN"));
    EXPECT_FALSE(isPathToFreedom(start, "SENSEENW"));

    // Paths that are illegal
    EXPECT_FALSE(isPathToFreedom(start, "WWE"));
    EXPECT_FALSE(isPathToFreedom(start, "NNN"));
    EXPECT_FALSE(isPathToFreedom(start, "EEE"));
    EXPECT_FALSE(isPathToFreedom(start, "SSS"));

    // Paths that start on an item
    start = m.getStart(0, 1);
    EXPECT_TRUE(isPathToFreedom(start, "SEENWESWWSSEEN"));
    start = m.getStart(0, 2);
    EXPECT_TRUE(isPathToFreedom(start, "ESWWNSSSEEN"));
    start = m.getStart(2, 3); 
    EXPECT_TRUE(isPathToFreedom(start, "SWWNNNSEENW"));

    start = m.getStart(0, 0);

    // Paths that have illegal characters
    EXPECT_FALSE(isPathToFreedom(start, "EFF"));
    EXPECT_FALSE(isPathToFreedom(start, "PRAK"));
    EXPECT_FALSE(isPathToFreedom(start, "SHIV"));

    // Paths that pick up all items but have illegal characters
    EXPECT_FALSE(isPathToFreedom(start, "SENSEENWESWWSSEEN?"));
    EXPECT_FALSE(isPathToFreedom(start, "SESSEENSWWNNEENWESWWN$"));
    EXPECT_FALSE(isPathToFreedom(start, "SEEENWESWWNSSSEEN3"));
}

// Tests a variety of things with another sample maze
TEST(maze, AllPurposeMaze2) {
    vector<string> textMaze;
    textMaze.push_back("S * P");
    textMaze.push_back("| | |");
    textMaze.push_back("*-*-*");
    textMaze.push_back("  |  ");
    textMaze.push_back("*-*-*");
    textMaze.push_back("| | |");
    textMaze.push_back("*-W-*");

    Maze m(textMaze);

    MazeCell* start = m.getStart(1, 1);

    // Paths that pick up all the items
    EXPECT_TRUE(isPathToFreedom(start, "WNSEENSWSS"));
    EXPECT_TRUE(isPathToFreedom(start, "ENSWWNSESS"));
    EXPECT_TRUE(isPathToFreedom(start, "SSNNENSWWN"));
    EXPECT_TRUE(isPathToFreedom(start, "SSNNWNSEEN"));

    // Paths that don't pick up all the items
    EXPECT_FALSE(isPathToFreedom(start, "WNS"));
    EXPECT_FALSE(isPathToFreedom(start, "ENSWWN"));
    EXPECT_FALSE(isPathToFreedom(start, "SES"));

    // Paths that are illegal
    EXPECT_FALSE(isPathToFreedom(start, "WS"));
    EXPECT_FALSE(isPathToFreedom(start, "ES"));
    EXPECT_FALSE(isPathToFreedom(start, "SEN"));
    EXPECT_FALSE(isPathToFreedom(start, "SWN"));

    // Paths that start on an item
    start = m.getStart(0, 0);
    EXPECT_TRUE(isPathToFreedom(start, "SEENSWSS"));
    start = m.getStart(0, 2);
    EXPECT_TRUE(isPathToFreedom(start, "SWWNSESS"));
    start = m.getStart(3, 1); 
    EXPECT_TRUE(isPathToFreedom(start, "NNENSWWN"));

    start = m.getStart(1, 1);

    // Paths that have illegal characters
    EXPECT_FALSE(isPathToFreedom(start, "TAHIR"));
    EXPECT_FALSE(isPathToFreedom(start, "CONY"));
    EXPECT_FALSE(isPathToFreedom(start, "JOHN"));

    // Paths that pick up all items but have illegal characters
    EXPECT_FALSE(isPathToFreedom(start, "WNSEENSWSS$"));
    EXPECT_FALSE(isPathToFreedom(start, "SSNNENSWWN1"));
    EXPECT_FALSE(isPathToFreedom(start, "SSNNWNSEEN3"));
}