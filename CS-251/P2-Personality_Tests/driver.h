/*  
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    The file holds all the necessary functions to implement a data-processing 
    framework to tabulate scores and compare personalities.
*/
#include <math.h>
#include <limits>
#include <string>
#include <map>
#include <set>
#include "myrandom.h"

using namespace std;

constexpr double lowest_double = std::numeric_limits<double>::lowest();

/* Type: Question
 *
 * Type representing a personality quiz question.
 */
struct Question {
    string questionText;  // Text of the question
    map<char, int> factors;   // Map from factors to +1 or -1
    friend bool operator< (const Question& lhs, const Question& rhs) {
        return lhs.questionText < rhs.questionText;
    }
    friend bool operator== (const Question& lhs, const Question& rhs) {
        return lhs.questionText == rhs.questionText;
    }
    friend bool operator!= (const Question& lhs, const Question& rhs) {
        return lhs.questionText != rhs.questionText;
    }
};

/* Type: Person
 *
 * Type representing a person, used to represent people when determining
 * who's the closest match to the user.
 */
struct Person {
    string name;      // Name of the person
    map<char, int> scores;  // Map from factors to +1 or -1
    friend bool operator< (const Person& lhs,   const Person& rhs) {
        return lhs.name < rhs.name;
    }
    friend bool operator== (const Person& lhs, const Person& rhs) {
        return lhs.name == rhs.name;
    }
    friend bool operator!= (const Person& lhs, const Person& rhs) {
        return lhs.name != rhs.name;
    }
};

/* randomElement
 *
 * This function selects, at random, a Question from the inputted questions set
 * and returns the question.  Note, this function does not remove the randomly
 * selected question from the set.
*/
Question randomElement(set<Question>& questions) {
    int ind = randomInteger(0, (int)questions.size()-1);
    int i = 0;
    for (auto e : questions) {
        if (i == ind) {
            return e;
        }
        i++;
    }
    return {};
}

/* randomQuestionFrom
 *
 * This function selects a random question from the inputted questions set using 
 * the randomElement function and erases the selected question from the given set.
*/
Question randomQuestionFrom(set<Question>& questions) {
    if (questions.size() == 0) {
        throw runtime_error("questions: empty");
    } else {
        Question qn = randomElement(questions);
        questions.erase(qn);
        return qn;
    }
}

/* scoresFrom
 *
 * This function iterates through the answers map to calculate OCEAN scores based
 * on user-inputted answers. It returns a map with the five factors as keys and their
 * scores as values.
*/
map<char, int> scoresFrom(map<Question, int>& answers) {
    map<char, int> scores;
    for (auto &a : answers) {
        Question q = a.first;
        for (auto &f : q.factors) {
            if (q.factors.count(f.first) == 1) {
                // Score = Factor * (Answer - 3)
                scores[f.first] += f.second * (a.second - 3); 
            }
        }
    }
    return scores;
}

/* normalize
 *
 * This function iterates through the scores map to normalize the scores and return them
 * in a different map normalizedScores. It first checks if the scores map contains at least
 * one non-zero value and then proceeds to normalize the values in the map. If no non-zero 
 * value is found, a runtime error is thrown.
*/
map<char, double> normalize(map<char, int>& scores) {
    map<char, double> normalizedScores;
    double sum = 0.0;
    double div;
    bool isAllZero = true;

    for (auto &s : scores) {
        if (s.second != 0) {
            isAllZero = false;
            break;
        }
    }

    if (isAllZero) {
        throw runtime_error("Scores are all zero!");
    } else {
        for (auto &s : scores) {
            int i = pow(s.second, 2);
            sum += i;
        }
        div = sqrt(sum);  // div = sqrt(o^2 + c^2 + e^2 + a^2 + n^2)
        for (auto &s : scores) {
            normalizedScores[s.first] = s.second / div;
        }
    }

    return normalizedScores;
}

/* cosineSimilarityOf
 *
 * This function accepts two normalized maps and returns their cosine similarity. It iterates through 
 * the first map and checks if the current key exists in the second map. Once a match is found, it adds 
 * the product of the two values to the total sum which is then returned. 
*/
double cosineSimilarityOf(const map<char, double>& lhs,
                          const map<char, double>& rhs) {
    double sim = 0.0;

    for (auto &l : lhs) {
        if (rhs.count(l.first) == 1) {  // If the same key is found in rhs...
            sim += l.second * rhs.find(l.first)->second;
        }
    }

    return sim;  // sim = o1o2 + c1c2 + e1e2 + a1a2 + n1n2
}

/* mostSimilarTo
 *
 * This function accepts a map of scores and a set of people and finds the person in the set that has the
 * highest cosine similarity with the user. It checks if the given set of people isn't empty, and raises 
 * a runtime error if it is.
*/
Person mostSimilarTo(map<char, int>& scores, set<Person>& people) {
    Person similarPerson;
    double cosSim;
    double maxCosSim = lowest_double;
    map<char, double> normalScores, normalPeople;

    if (people.size() == 0) {
        throw runtime_error("people: empty");
    } else {
        normalScores = normalize(scores);
        for (auto p : people) {
            normalPeople = normalize(p.scores);
            cosSim = cosineSimilarityOf(normalScores, normalPeople);
            if (cosSim > maxCosSim) {
                maxCosSim = cosSim;
                similarPerson = p;
            }
        }
    }

    return similarPerson;
}
