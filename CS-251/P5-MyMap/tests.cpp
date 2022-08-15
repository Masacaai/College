/*  
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This file contains unit tests implemented with the Google Test Framework.
*/

#include <gtest/gtest.h>
#include "mymap.h"

// Stress-test with map<int, int>
TEST(mymap, intInt) {
    for (int i = 0; i < 10000; ++i) {
        int num = rand() % 10000;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        int arrKey[] = {num, num - 1, num + 1, num + 2, num + 3};
        int arrKeyOrder[] = {num - 1, num, num + 1, num + 2, num + 3};
        int arrVal[] = {num, num - 1, num + 1};
        int arrValOrder[] = {num - 1, num, num + 1};
        mymap<int, int> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), int());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), int());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<int, int>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<int, int> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], int());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], int());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");

    }
}

// Stress-test with map<int, string>
TEST(mymap, intStr) {
    for (int i = 0; i < 10000; ++i) {
        int num = rand() % 10000;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        int arrKey[] = {num, num - 1, num + 1, num + 2, num + 3};
        int arrKeyOrder[] = {num - 1, num, num + 1, num + 2, num + 3};
        string arrVal[] = {"B", "A", "C"};
        string arrValOrder[] = {"A", "B", "C"};
        mymap<int, string> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), string());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), string());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<int, string>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<int, string> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], string());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], string());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<int, double>
TEST(mymap, intDbl) {
    for (int i = 0; i < 10000; ++i) {
        int num = rand() % 10000;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        int arrKey[] = {num, num - 1, num + 1, num + 2, num + 3};
        int arrKeyOrder[] = {num - 1, num, num + 1, num + 2, num + 3};
        double arrVal[] = {num * 1.0, num - 0.5, num + 0.5};
        double arrValOrder[] = {num - 0.5, num * 1.0, num + 0.5};
        mymap<int, double> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), double());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), double());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<int, double>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<int, double> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], double());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], double());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<int, char>
TEST(mymap, intChr) {
    for (int i = 0; i < 10000; ++i) {
        int num = rand() % 10000;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        int arrKey[] = {num, num - 1, num + 1, num + 2, num + 3};
        int arrKeyOrder[] = {num - 1, num, num + 1, num + 2, num + 3};
        char arrVal[] = {'B', 'A', 'C'};
        char arrValOrder[] = {'A', 'B', 'C'};
        mymap<int, char> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), char());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), char());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<int, char>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<int, char> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], char());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], char());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<string, int>
TEST(mymap, strInt) {
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 10000; ++i) {
        int num = (rand() % 22) + 1;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        string arrKey[] = {abc.substr(num, 1), abc.substr(num - 1, 1), abc.substr(num + 1, 1), abc.substr(num + 2, 1), abc.substr(num + 3, 1)};
        string arrKeyOrder[] = {abc.substr(num - 1, 1), abc.substr(num, 1), abc.substr(num + 1, 1), abc.substr(num + 2, 1), abc.substr(num + 3, 1)};
        int arrVal[] = {2, 1, 3};
        int arrValOrder[] = {1, 2, 3};
        mymap<string, int> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), int());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), int());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<string, int>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<string, int> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], int());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], int());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");

    }
}

// Stress-test with map<string, string>
TEST(mymap, strStr) {
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 10000; ++i) {
        int num = (rand() % 22) + 1;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        string arrKey[] = {abc.substr(num, 1), abc.substr(num - 1, 1), abc.substr(num + 1, 1), abc.substr(num + 2, 1), abc.substr(num + 3, 1)};
        string arrKeyOrder[] = {abc.substr(num - 1, 1), abc.substr(num, 1), abc.substr(num + 1, 1), abc.substr(num + 2, 1), abc.substr(num + 3, 1)};
        string arrVal[] = {abc.substr(num, 1), abc.substr(num - 1, 1), abc.substr(num + 1, 1)};
        string arrValOrder[] = {abc.substr(num - 1, 1), abc.substr(num, 1), abc.substr(num + 1, 1)};
        mymap<string, string> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), string());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), string());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<string, string>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<string, string> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], string());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], string());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<string, double>
TEST(mymap, strDbl) {
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 10000; ++i) {
        int num = (rand() % 22) + 1;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        string arrKey[] = {abc.substr(num, 1), abc.substr(num - 1, 1), abc.substr(num + 1, 1), abc.substr(num + 2, 1), abc.substr(num + 3, 1)};
        string arrKeyOrder[] = {abc.substr(num - 1, 1), abc.substr(num, 1), abc.substr(num + 1, 1), abc.substr(num + 2, 1), abc.substr(num + 3, 1)};
        double arrVal[] = {num * 1.0, num - 0.5, num + 0.5};
        double arrValOrder[] = {num - 0.5, num * 1.0, num + 0.5};
        mymap<string, double> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), double());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), double());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<string, double>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<string, double> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], double());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], double());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<string, char>
TEST(mymap, strChr) {
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 10000; ++i) {
        int num = (rand() % 22) + 1;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        string arrKey[] = {abc.substr(num, 1), abc.substr(num - 1, 1), abc.substr(num + 1, 1), abc.substr(num + 2, 1), abc.substr(num + 3, 1)};
        string arrKeyOrder[] = {abc.substr(num - 1, 1), abc.substr(num, 1), abc.substr(num + 1, 1), abc.substr(num + 2, 1), abc.substr(num + 3, 1)};
        char arrVal[] = {'B', 'A', 'C'};
        char arrValOrder[] = {'A', 'B', 'C'};
        mymap<string, char> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), char());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), char());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<string, char>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<string, char> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], char());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], char());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<double, int>
TEST(mymap, dblInt) {
    for (int i = 0; i < 10000; ++i) {
        int num = rand() % 10000;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        double arrKey[] = {num * 1.0, num - 0.5, num + 0.5, num + 1.0, num + 1.5};
        double arrKeyOrder[] = {num - 0.5, num * 1.0, num + 0.5, num + 1.0, num + 1.5};
        int arrVal[] = {2, 1, 3};
        int arrValOrder[] = {1, 2, 3};
        mymap<double, int> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), int());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), int());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<double, int>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<double, int> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], int());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], int());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");

    }
}

// Stress-test with map<double, string>
TEST(mymap, dblStr) {
    for (int i = 0; i < 10000; ++i) {
        int num = rand() % 10000;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        double arrKey[] = {num * 1.0, num - 0.5, num + 0.5, num + 1.0, num + 1.5};
        double arrKeyOrder[] = {num - 0.5, num * 1.0, num + 0.5, num + 1.0, num + 1.5};
        string arrVal[] = {"B", "A", "C"};
        string arrValOrder[] = {"A", "B", "C"};
        mymap<double, string> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), string());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), string());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<double, string>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<double, string> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], string());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], string());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<double, double>
TEST(mymap, dblDbl) {
    for (int i = 0; i < 10000; ++i) {
        int num = rand() % 10000;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        double arrKey[] = {num * 1.0, num - 0.5, num + 0.5, num + 1.0, num + 1.5};
        double arrKeyOrder[] = {num - 0.5, num * 1.0, num + 0.5, num + 1.0, num + 1.5};
        double arrVal[] = {num * 1.0, num - 0.5, num + 0.5};
        double arrValOrder[] = {num - 0.5, num * 1.0, num + 0.5};
        mymap<double, double> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), double());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), double());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<double, double>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<double, double> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], double());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], double());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<double, char>
TEST(mymap, dblChr) {
    for (int i = 0; i < 10000; ++i) {
        int num = rand() % 10000;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        double arrKey[] = {num * 1.0, num - 0.5, num + 0.5, num + 1.0, num + 1.5};
        double arrKeyOrder[] = {num - 0.5, num * 1.0, num + 0.5, num + 1.0, num + 1.5};
        char arrVal[] = {'B', 'A', 'C'};
        char arrValOrder[] = {'A', 'B', 'C'};
        mymap<double, char> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), char());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), char());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<double, char>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<double, char> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], char());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], char());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<char, int>
TEST(mymap, chrInt) {
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 10000; ++i) {
        int num = (rand() % 22) + 1;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        char arrKey[] = {abc[num], abc[num - 1], abc[num + 1], abc[num + 2], abc[num + 3]};
        char arrKeyOrder[] = {abc[num - 1], abc[num], abc[num + 1], abc[num + 2], abc[num + 3]};
        int arrVal[] = {2, 1, 3};
        int arrValOrder[] = {1, 2, 3};
        mymap<char, int> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3); 
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), int());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), int());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<char, int>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<char, int> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], int());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], int());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");

    }
}

// Stress-test with map<char, string>
TEST(mymap, chrStr) {
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 10000; ++i) {
        int num = (rand() % 22) + 1;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        char arrKey[] = {abc[num], abc[num - 1], abc[num + 1], abc[num + 2], abc[num + 3]};
        char arrKeyOrder[] = {abc[num - 1], abc[num], abc[num + 1], abc[num + 2], abc[num + 3]};
        string arrVal[] = {"B", "A", "C"};
        string arrValOrder[] = {"A", "B", "C"};
        mymap<char, string> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), string());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), string());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<char, string>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<char, string> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], string());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], string());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<char, double>
TEST(mymap, chrDbl) {
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 10000; ++i) {
        int num = (rand() % 22) + 1;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        char arrKey[] = {abc[num], abc[num - 1], abc[num + 1], abc[num + 2], abc[num + 3]}; 
        char arrKeyOrder[] = {abc[num - 1], abc[num], abc[num + 1], abc[num + 2], abc[num + 3]};
        double arrVal[] = {num * 1.0, num - 0.5, num + 0.5};
        double arrValOrder[] = {num - 0.5, num * 1.0, num + 0.5};
        mymap<char, double> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), double());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), double());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<char, double>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<char, double> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], double());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], double());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}

// Stress-test with map<char, char>
TEST(mymap, chrChr) {
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 10000; ++i) {
        int num = (rand() % 22) + 1;
        // 5 elements are in the array, but only 3 will be added to the map
        // This is so we can use the other 2 to test for how functions handle
        // keys not present in the map.
        char arrKey[] = {abc[num], abc[num - 1], abc[num + 1], abc[num + 2], abc[num + 3]};
        char arrKeyOrder[] = {abc[num - 1], abc[num], abc[num + 1], abc[num + 2], abc[num + 3]};
        char arrVal[] = {abc[num], abc[num - 1], abc[num + 1]};
        char arrValOrder[] = {abc[num - 1], abc[num], abc[num + 1]};
        mymap<char, char> map;

        // Test default constructor
        EXPECT_EQ(map.Size(), 0);

        // Add keys to the map so we can check
        // how duplicate keys are handled.
        map[arrKey[0]];

        // Test put()
        for (int i = 0; i < 3; i++) {
            map.put(arrKey[i], arrVal[i]);
            EXPECT_EQ(map.Size(), i + 1);
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
        }

        // Test Size() after elements are added
        EXPECT_EQ(map.Size(), 3);
        
        // Test contains()
        for (int i = 0; i < 3; ++i) {
            EXPECT_TRUE(map.contains(arrKey[i]));
        }
        // Test contains() with non-existent keys
        EXPECT_FALSE(map.contains(arrKey[3]));
        EXPECT_FALSE(map.contains(arrKey[4]));

        // Test get()
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map.get(arrKey[i]), arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test get() with non-existent keys
        EXPECT_EQ(map.get(arrKey[3]), char());
        EXPECT_EQ(map.Size(), 3);
        EXPECT_EQ(map.get(arrKey[4]), char());
        EXPECT_EQ(map.Size(), 3);

        // Test toString()
        stringstream sol("");
        for (int i = 0; i < 3; ++i) {
            sol << "key: " << arrKeyOrder[i] << " value: " << arrValOrder[i] << endl;
        }
        EXPECT_EQ(map.toString(), sol.str());

        // Test toVector()
        vector<pair<char, char>> vec;
        for (int i = 0; i < 3; ++i) {
            vec.push_back({arrKeyOrder[i], arrValOrder[i]});
        }
        EXPECT_EQ(map.toVector(), vec);
        
        // Test checkBalance()
        stringstream bl("");
        bl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 1 << endl;
        bl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        bl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), bl.str());

        // Test begin()
        EXPECT_EQ(*map.begin(), arrKeyOrder[0]);

        // Test for-each loop functionality
        int j = 0;
        for (auto key : map) {
            EXPECT_EQ(arrKeyOrder[j++], key);
        }

        // Test copy constructor
        mymap<char, char> mapCopy(map);
        int k = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[k++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test copy operator
        mapCopy = map;
        int l = 0;
        for (auto key : mapCopy) {
            EXPECT_EQ(arrKeyOrder[l++], key);
        }
        EXPECT_EQ(map.Size(), mapCopy.Size());
        EXPECT_EQ(map.toString(), mapCopy.toString());
        EXPECT_EQ(map.toVector(), mapCopy.toVector());
        // Test if elements in original map remain
        // constant if mapCopy is changed
        mapCopy.clear();
        EXPECT_EQ(map.Size(), 3);

        // Test [] operator
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(map[arrKey[i]], arrVal[i]);
            EXPECT_EQ(map.Size(), 3);
        }
        // Test [] with non-existent keys
        EXPECT_EQ(map[arrKey[3]], char());
        EXPECT_EQ(map.Size(), 4);
        EXPECT_EQ(map[arrKey[4]], char());
        EXPECT_EQ(map.Size(), 5);
        
        // Test checkBalance() with unbalanced tree
        stringstream ubl("");
        ubl << "key: " << arrKey[0] << ", nL: " << 1 << ", nR: " << 3 << endl;
        ubl << "key: " << arrKey[1] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[3] << ", nL: " << 1 << ", nR: " << 1 << endl;
        ubl << "key: " << arrKey[2] << ", nL: " << 0 << ", nR: " << 0 << endl;
        ubl << "key: " << arrKey[4] << ", nL: " << 0 << ", nR: " << 0 << endl;
        EXPECT_EQ(map.checkBalance(), ubl.str());

        // Test clear()
        map.clear();
        EXPECT_EQ(map.Size(), 0);
        EXPECT_EQ(map.toString(), "");
    }
}