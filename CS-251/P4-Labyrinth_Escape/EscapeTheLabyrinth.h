#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change this constant to contain your full first and last name (middle is ok too).
 *
 * WARNING: Once you've set set this constant and started exploring your maze,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "Mohammed Aaqel Shaik Abdul Mazeed";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "SENSEENWESWWSSEEN";
const string kPathOutOfTwistyMaze = "WNENWESWWSNESWN";

bool isPathToFreedom(MazeCell *start, const string& moves) {
    bool pickedSpellbook = false;
    bool pickedWand = false;
    bool pickedPotion = false;
    bool isValid = true;

    if (start->whatsHere == "Potion") {
        pickedPotion = true;
    } else if (start->whatsHere == "Spellbook") {
        pickedSpellbook = true;
    } else if (start->whatsHere == "Wand") {
        pickedWand = true;
    }

    MazeCell *cur = start;
    for (char c : moves) {
        if (c == 'N') {
            if (cur->north != nullptr) {
                cur = cur->north;
            } else {
                isValid = false;
                break;
            }
        } else if (c == 'S') {
            if (cur->south != nullptr) {
                cur = cur->south;
            } else {
                isValid = false;
                break;
            }
        } else if (c == 'E') {
            if (cur->east != nullptr) {
                cur = cur->east;
            } else {
                isValid = false;
                break;
            }
        } else if (c == 'W') {
            if (cur->west != nullptr) {
                cur = cur->west;
            } else {
                isValid = false;
                break;
            }
        } else {
            isValid = false;
            break;
        }

        if (cur->whatsHere == "Potion") {
            pickedPotion = true;
        } else if (cur->whatsHere == "Spellbook") {
            pickedSpellbook = true;
        } else if (cur->whatsHere == "Wand") {
            pickedWand = true;
        }
    }
    if (pickedPotion && pickedSpellbook && pickedWand && isValid) {
        return true;
    } else {
        return false;
    }    
}
