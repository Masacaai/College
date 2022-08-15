/*  
    Course: CS 251, Spring 2022. Wed 12 PM Lab
    System: NixOS 22.05 using Visual Studio Code
    Author: Mohammed Aaqel Shaik Abdul Mazeed

    Program Overview:
    This file contains tests for the animated bar chart program.
*/

#include <iostream>
#include "barchartanimate.h"
using namespace std;

bool testBarDefaultConstructor() {
	Bar b;
    if (b.getName() != "") {
    	cout << RED << "testBarDefaultConstructor: getName failed" << RESET << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << RED << "testBarDefaultConstructor: getValue failed" << RESET << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << RED << "testBarDefaultConstructor: getCategory failed" << RESET << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor1() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << RED << "testBarParamConstructor1: getName failed" << RESET << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << RED << "testBarParamConstructor1: getValue failed" << RESET << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << RED << "testBarParamConstructor1: getCategory failed" << RESET << endl;
    	return false;
    }
    cout << "testBarParamConstructor1: all passed!" << endl;
    return true;
}

bool testBarParamConstructor2() {
	Bar b("Phoenix", 8573758, "US");
    if (b.getName() != "Phoenix") {
    	cout << RED << "testBarParamConstructor2: getName failed" << RESET << endl;
    	return false;
    } else if (b.getValue() != 8573758) {
    	cout << RED << "testBarParamConstructor2: getValue failed" << RESET << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << RED << "testBarParamConstructor2: getCategory failed" << RESET << endl;
    	return false;
    }
    cout << "testBarParamConstructor2: all passed!" << endl;
    return true;
}

bool testBarLessOperator1() {
	Bar b1("Chicago", 1, "US"), b2("Arizona", 2, "US"), b3("Toronto", 2, "CA");
	if ((b1 < b2) != true) {
		cout << RED << "testBarLessOperator1: b1 < b2 failed" << RESET << endl;
		return false;
	} else if ((b2 < b1) != false) {
		cout << RED << "testBarLessOperator1: b2 < b1 failed" << RESET << endl;
		return false;
	}
	else if ((b2 < b3) != false) {
		cout << RED << "testBarLessOperator1: b2 < b3 failed" << RESET << endl;
		return false;
	}
	cout << "testBarLessOperator1: all passed!" << endl;
	return true;
}

bool testBarLessOperator2() {
	Bar b1("Chicago", 2, "US"), b2("Arizona", 3, "US"), b3("Toronto", 3, "CA");
	if ((b1 < b2) != true) {
		cout << RED << "testBarLessOperator2: b1 < b2 failed" << RESET << endl;
		return false;
	} else if ((b2 < b1) != false) {
		cout << RED << "testBarLessOperator2: b2 < b1 failed" << RESET << endl;
		return false;
	}
	else if ((b2 < b3) != false) {
		cout << RED << "testBarLessOperator2: b2 < b3 failed" << RESET << endl;
		return false;
	}
	cout << "testBarLessOperator2: all passed!" << endl;
	return true;
}

bool testBarGreaterOperator1() {
	Bar b1("Chicago", 1, "US"), b2("Arizona", 2, "US"), b3("Toronto", 2, "CA");
	if ((b1 > b2) != false) {
		cout << RED << "testBarGreaterOperator1: b1 > b2 failed" << RESET << endl;
		return false;
	} else if ((b2 > b1) != true) {
		cout << RED << "testBarGreaterOperator1: b2 > b1 failed" << RESET << endl;
		return false;
	}
	else if ((b2 > b3) != false) {
		cout << RED << "testBarGreaterOperator1: b2 > b3 failed" << RESET << endl;
		return false;
	}
	cout << "testBarGreaterOperator1: all passed!" << endl;
	return true;
}

bool testBarGreaterOperator2() {
	Bar b1("Chicago", 2, "US"), b2("Arizona", 3, "US"), b3("Toronto", 3, "CA");
	if ((b1 > b2) != false) {
		cout << RED << "testBarGreaterOperator2: b1 > b2 failed" << RESET << endl;
		return false;
	} else if ((b2 > b1) != true) {
		cout << RED << "testBarGreaterOperator2: b2 > b1 failed" << RESET << endl;
		return false;
	}
	else if ((b2 > b3) != false) {
		cout << RED << "testBarGreaterOperator2: b2 > b3 failed" << RESET << endl;
		return false;
	}
	cout << "testBarGreaterOperator2: all passed!" << endl;
	return true;
}

bool testBarLessEqualOperator1() {
	Bar b1("Chicago", 1, "US"), b2("Arizona", 2, "US"), b3("Toronto", 2, "CA");
	if ((b1 <= b2) != true) {
		cout << RED << "testBarLessEqualOperator1: b1 <= b2 failed" << RESET << endl;
		return false;
	} else if ((b2 <= b1) != false) {
		cout << RED << "testBarLessEqualOperator1: b2 <= b1 failed" << RESET << endl;
		return false;
	}
	else if ((b2 <= b3) != true) {
		cout << RED << "testBarLessEqualOperator1: b2 <= b3 failed" << RESET << endl;
		return false;
	}
	cout << "testBarLessEqualOperator1: all passed!" << endl;
	return true;
}

bool testBarLessEqualOperator2() {
	Bar b1("Chicago", 2, "US"), b2("Arizona", 3, "US"), b3("Toronto", 3, "CA");
	if ((b1 <= b2) != true) {
		cout << RED << "testBarLessEqualOperator2: b1 <= b2 failed" << RESET << endl;
		return false;
	} else if ((b2 <= b1) != false) {
		cout << RED << "testBarLessEqualOperator2: b2 <= b1 failed" << RESET << endl;
		return false;
	}
	else if ((b2 <= b3) != true) {
		cout << RED << "testBarLessEqualOperator2: b2 <= b3 failed" << RESET << endl;
		return false;
	}
	cout << "testBarLessEqualOperator2: all passed!" << endl;
	return true;
}

bool testBarGreaterEqualOperator1() {
	Bar b1("Chicago", 1, "US"), b2("Arizona", 2, "US"), b3("Toronto", 2, "CA");
	if ((b1 >= b2) != false) {
		cout << RED << "testBarGreaterEqualOperator1: b1 >= b2 failed" << RESET << endl;
		return false;
	} else if ((b2 >= b1) != true) {
		cout << RED << "testBarGreaterEqualOperator1: b2 >= b1 failed" << RESET << endl;
		return false;
	}
	else if ((b2 >= b3) != true) {
		cout << RED << "testBarGreaterEqualOperator1: b2 >= b3 failed" << RESET << endl;
		return false;
	}
	cout << "testBarGreaterEqualOperator1: all passed!" << endl;
	return true;
}

bool testBarGreaterEqualOperator2() {
	Bar b1("Chicago", 2, "US"), b2("Arizona", 3, "US"), b3("Toronto", 3, "CA");
	if ((b1 >= b2) != false) {
		cout << RED << "testBarGreaterEqualOperator2: b1 >= b2 failed" << RESET << endl;
		return false;
	} else if ((b2 >= b1) != true) {
		cout << RED << "testBarGreaterEqualOperator2: b2 >= b1 failed" << RESET << endl;
		return false;
	}
	else if ((b2 >= b3) != true) {
		cout << RED << "testBarGreaterEqualOperator2: b2 >= b3 failed" << RESET << endl;
		return false;
	}
	cout << "testBarGreaterEqualOperator2: all passed!" << endl;
	return true;
}

bool testBarChartDefaultConstructor() {
	BarChart bc;
	if (bc.addBar("a", 1, "b")) {
		cout << RED << "testBarChartDefaultConstructor: addBar exceeded capacity" << RESET << endl;
		return false;
	}
	if (bc.getSize() != 0) {
		cout << RED << "testBarChartDefaultConstructor: getSize failed" << RESET << endl;
		return false;
	} else if (bc.getFrame() != "") {
		cout << RED << "testBarChartDefaultConstructor: getFrame failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartDefaultConstructor: all passed!" << endl;
	return true;
}

bool testBarChartParamConstructor1() {
	BarChart bc(10);
	bc.addBar("a", 1, "b");
	bc.addBar("a", 2, "b");
	bc.addBar("a", 3, "b");
	bc.addBar("a", 4, "b");
	bc.addBar("a", 5, "b");
	bc.addBar("a", 6, "b");
	bc.addBar("a", 7, "b");
	bc.addBar("a", 8, "b");
	bc.addBar("a", 9, "b");
	bc.addBar("a", 10, "b");
	if (bc.addBar("a", 11, "b")) {
		cout << RED << "testBarChartParamConstructor1: addBar exceeded capacity" << RESET << endl;
		return false;
	} else if (bc.getSize() != 10) {
		cout << RED << "testBarChartParamConstructor1: getSize failed" << RESET << endl;
		return false;
	} else if (bc.getFrame() != "") {
		cout << RED << "testBarChartParamConstructor1: getFrame failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartParamConstructor1: all passed!" << endl;
	return true;
}

bool testBarChartParamConstructor2() {
	BarChart bc(5);
	bc.addBar("a", 1, "b");
	bc.addBar("a", 2, "b");
	bc.addBar("a", 3, "b");
	bc.addBar("a", 4, "b");
	bc.addBar("a", 5, "b");
	if (bc.addBar("a", 6, "b")) {
		cout << RED << "testBarChartParamConstructor2: addBar exceeded capacity" << RESET << endl;
		return false;
	} else if (bc.getSize() != 5) {
		cout << RED << "testBarChartParamConstructor2: getSize failed" << RESET << endl;
		return false;
	} else if (bc.getFrame() != "") {
		cout << RED << "testBarChartParamConstructor2: getFrame failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartParamConstructor2: all passed!" << endl;
	return true;
}

bool testBarChartCopyConstructor1() {
	BarChart bc1(10);
	bc1.setFrame("1950");
	bc1.addBar("a", 1, "b");
	BarChart bc2(bc1);
	if (bc2.getSize() != 1) {
		cout << RED << "testBarChartCopyConstructor1: getSize failed" << RESET << endl;
		return false;
	} else if (bc2.getFrame() != "1950") {
		cout << RED << "testBarChartCopyConstructor1: getFrame failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartCopyConstructor1: all passed!" << endl;
	return true;
}

bool testBarChartCopyConstructor2() {
	BarChart bc1(5);
	bc1.setFrame("2012");
	bc1.addBar("a", 1, "b");
	bc1.addBar("b", 2, "c");
	BarChart bc2(bc1);
	if (bc2.getSize() != 2) {
		cout << RED << "testBarChartCopyConstructor2: getSize failed" << RESET << endl;
		return false;
	} else if (bc2.getFrame() != "2012") {
		cout << RED << "testBarChartCopyConstructor2: getFrame failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartCopyConstructor2: all passed!" << endl;
	return true;
}

bool testBarChartCopyOperator1() {
	BarChart bc1(10), bc2(20);
	bc1.setFrame("1950");
	bc1.addBar("a", 1, "b");
	bc2.setFrame("2012");
	bc2 = bc1;
	if (bc2.getSize() != 1) {
		cout << RED << "testBarChartCopyOperator1: getSize failed" << RESET << endl;
		return false;
	} else if (bc2.getFrame() != "1950") {
		cout << RED << "testBarChartCopyOperator1: getFrame failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartCopyOperator1: all passed!" << endl;
	return true;
}

bool testBarChartCopyOperator2() {
	BarChart bc1(10), bc2(20);
	bc1.setFrame("2012");
	bc1.addBar("a", 1, "b");
	bc1.addBar("b", 2, "c");
	bc2.setFrame("2018");
	bc2 = bc1;
	if (bc2.getSize() != 2) {
		cout << RED << "testBarChartCopyOperator2: getSize failed" << RESET << endl;
		return false;
	} else if (bc2.getFrame() != "2012") {
		cout << RED << "testBarChartCopyOperator2: getFrame failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartCopyOperator2: all passed!" << endl;
	return true;
}

bool testBarChartClear1() {
	BarChart bc(10);
	bc.setFrame("1950");
	bc.addBar("a", 1, "b");
	bc.clear();
	if (bc.getSize() != 0) {
		cout << RED << "testBarChartClear1: getSize failed" << RESET << endl;
		return false;
	} else if (bc.getFrame() != "") {
		cout << RED << "testBarChartClear1: getFrame failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartClear1: all passed!" << endl;
	return true;;
}

bool testBarChartClear2() {
	BarChart bc(5);
	bc.setFrame("2012");
	bc.addBar("a", 1, "b");
	bc.addBar("b", 2, "c");
	bc.clear();
	if (bc.getSize() != 0) {
		cout << RED << "testBarChartClear2: getSize failed" << RESET << endl;
		return false;
	} else if (bc.getFrame() != "") {
		cout << RED << "testBarChartClear2: getFrame failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartClear2: all passed!" << endl;
	return true;;
}

bool testBarChartSetFrame1() {
	BarChart bc(10);
	bc.setFrame("1950");
	if (bc.getFrame() != "1950") {
		cout << RED << "testBarChartSetFrame1: setFrame(1950) failed" << RESET << endl;
		return false;
	}
	bc.setFrame("2000");
	if (bc.getFrame() != "2000") {
		cout << RED << "testBarChartSetFrame1: setFrame(2000) failed" << RESET << endl;
		return false;
	}
	bc.setFrame("2012");
	if (bc.getFrame() != "2012") {
		cout << RED << "testBarChartSetFrame1: setFrame(2012) failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartSetFrame1: all passed!" << endl;
	return true;
}

bool testBarChartSetFrame2() {
	BarChart bc(10);
	bc.setFrame("1800");
	if (bc.getFrame() != "1800") {
		cout << RED << "testBarChartSetFrame2: setFrame(1800) failed" << RESET << endl;
		return false;
	}
	bc.setFrame("2010");
	if (bc.getFrame() != "2010") {
		cout << RED << "testBarChartSetFrame2: setFrame(2010) failed" << RESET << endl;
		return false;
	}
	bc.setFrame("2018");
	if (bc.getFrame() != "2018") {
		cout << RED << "testBarChartSetFrame2: setFrame(2018) failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartSetFrame2: all passed!" << endl;
	return true;
}

bool testBarChartAddBar1() {
	BarChart bc(10);
	bc.addBar("a", 1, "b");
	if (bc.getSize() != 1) {
		cout << RED << "testBarChartAddBar1: getSize failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartAddBar1: all passed!" << endl;
	return true;
}

bool testBarChartAddBar2() {
	BarChart bc(5);
	bc.addBar("a", 1, "b");
	bc.addBar("b", 2, "c");
	if (bc.getSize() != 2) {
		cout << RED << "testBarChartAddBar2: getSize failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartAddBar2: all passed!" << endl;
	return true;
}

bool testBarChartSquareBracketsOperator1() {
	BarChart bc(10);
	bc.addBar("a", 1, "b");
	bc.addBar("b", 2, "c");
	bc.addBar("c", 3, "d");
	if (bc[0].getName() != "a") {
		cout << RED << "testBarChartSquareBracketsOperator1: getName failed" << RESET << endl;
		return false;
	} else if (bc[1].getValue() != 2) {
		cout << RED << "testBarChartSquareBracketsOperator1: getValue failed" << RESET << endl;
		return false;
	} else if (bc[2].getCategory() != "d") {
		cout << RED << "testBarChartSquareBracketsOperator1: getCategory failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartSquareBracketsOperator1: all passed!" << endl;
	return true;
}

bool testBarChartSquareBracketsOperator2() {
	BarChart bc(5);
	bc.addBar("Chicago", 120, "US");
	bc.addBar("Toronto", 256, "CA");
	bc.addBar("Phoenix", 112, "US");
	if (bc[0].getName() != "Chicago") {
		cout << RED << "testBarChartSquareBracketsOperator2: getName failed" << RESET << endl;
		return false;
	} else if (bc[1].getValue() != 256) {
		cout << RED << "testBarChartSquareBracketsOperator2: getValue failed" << RESET << endl;
		return false;
	} else if (bc[2].getCategory() != "US") {
		cout << RED << "testBarChartSquareBracketsOperator2: getCategory failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartSquareBracketsOperator2: all passed!" << endl;
	return true;
}

bool testBarChartDump1() {
	BarChart bc(10);
	bc.setFrame("1950");
	bc.addBar("Phoenix", 26, "US");
	bc.addBar("Chicago", 42, "US");
	bc.addBar("Toronto", 31, "CA");
	stringstream ssActual;
	stringstream ssExpected;
	bc.dump(ssActual);
	ssExpected << "frame: 1950" << endl
			   << "Chicago 42 US" << endl
			   << "Toronto 31 CA" << endl
			   << "Phoenix 26 US" << endl;
	if (ssActual.str() != ssExpected.str()) {
		cout << RED << "testBarChartDump1: ssActual != ssExpected" << RESET << endl;
		return false;
	}
	cout << "testBarChartDump1: all passed!" << endl;
	return true;
}

bool testBarChartDump2() {
	BarChart bc(5);
	bc.setFrame("2012");
	bc.addBar("Milkauwee", 56, "US");
	bc.addBar("New York", 72, "US");
	bc.addBar("Montreal", 10, "CA");
	stringstream ssActual;
	stringstream ssExpected;
	bc.dump(ssActual);
	ssExpected << "frame: 2012" << endl
			   << "New York 72 US" << endl
			   << "Milkauwee 56 US" << endl
			   << "Montreal 10 CA" << endl;
	if (ssActual.str() != ssExpected.str()) {
		cout << RED << "testBarChartDump2: ssActual != ssExpected" << RESET << endl;
		return false;
	}
	cout << "testBarChartDump2: all passed!" << endl;
	return true;
}

bool testBarChartGraph1() {
	BarChart bc(10);
	bc.setFrame("1950");
	bc.addBar("Phoenix", 26, "US");
	bc.addBar("Chicago", 42, "US");
	bc.addBar("Toronto", 31, "CA");

	map<string, string> colorMap;
	colorMap["US"] = RED;
	colorMap["CA"] = BLUE;
	stringstream ssActual;
	stringstream ssExpected;
	ssExpected << "\033[1;36m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Chicago 42" << endl
			   << "\033[1;33m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Toronto 31" << endl
			   << "\033[1;36m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Phoenix 26" << endl;
	bc.graph(ssActual, colorMap, 3);
	if (ssActual.str() != ssExpected.str()) {
		cout << RED << "testBarChartGraph1: ssActual != ssExpected" << RESET << endl;
		return false;
	}
	cout << "testBarChartGraph1: all passed!" << endl;
	return true;
}

bool testBarChartGraph2() {
	BarChart bc(5);
	bc.setFrame("2012");
	bc.addBar("Milkauwee", 56, "US");
	bc.addBar("New York", 72, "US");
	bc.addBar("Montreal", 10, "CA");

	map<string, string> colorMap;
	colorMap["US"] = RED;
	colorMap["CA"] = BLUE;
	stringstream ssActual;
	stringstream ssExpected;
	ssExpected << "\033[1;36m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ New York 72" << endl
			   << "\033[1;36m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Milkauwee 56" << endl
			   << "\033[1;33m⧈⧈⧈⧈⧈⧈⧈⧈ Montreal 10" << endl;
	bc.graph(cout, colorMap, 3);
	if (ssActual.str() != ssExpected.str()) {
		cout << RED << "testBarChartGraph2: ssActual != ssExpected" << RESET << endl;
		return false;
	}
	cout << "testBarChartGraph2: all passed!" << endl;
	return true;
}

bool testBarChartAnimateParamConstructor() {
	BarChartAnimate bca("title", "xlabel", "source");
	if (bca.getSize() != 0) {
		cout << RED << "testBarChartAnimateParamConstructor: getSize failed" << RESET << endl;
		return false;
	} 
	cout << "testBarChartAnimateParamConstructor: all passed!" << endl;
	return true;
}

bool testBarChartAnimateAddFrame1() {
	string buffer;
	BarChartAnimate bca("title", "xlabel", "source");
	ifstream file("cities.txt");
	getline(file, buffer);
	getline(file, buffer);
	getline(file, buffer);
	bca.addFrame(file);
	if (bca[0].getFrame() != "1500") {
		cout << RED << "testBarChartAnimateAddFrame1: getFrame failed" << RESET << endl;
		return false;
	}
	bca.addFrame(file);
	bca.addFrame(file);
	bca.addFrame(file);
	bca.addFrame(file);
	if (bca.getSize() != 5) {
		cout << RED << "testBarChartAnimateAddFrame1: getSize failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartAnimateAddFrame1: all passed!" << endl;
	return true;
}

bool testBarChartAnimateAddFrame2() {
	string buffer;
	BarChartAnimate bca("title", "xlabel", "source");
	ifstream file("brands.txt");
	getline(file, buffer);
	getline(file, buffer);
	getline(file, buffer);
	bca.addFrame(file);
	bca.addFrame(file);
	if (bca[1].getFrame() != "2000-02-01") {
		cout << RED << "testBarChartAnimateAddFrame2: getFrame failed" << RESET << endl;
		return false;
	}
	bca.addFrame(file);
	bca.addFrame(file);
	bca.addFrame(file);
	bca.addFrame(file);
	if (bca.getSize() != 6) {
		cout << RED << "testBarChartAnimateAddFrame2: getSize failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartAnimateAddFrame2: all passed!" << endl;
	return true;
}

bool testBarChartAnimateAnimate1() {
	string buffer;
	stringstream ssActual;
	stringstream ssExpected;
	BarChartAnimate bca("title", "xlabel", "source");
	ifstream file("cities.txt");
	getline(file, buffer);
	getline(file, buffer);
	getline(file, buffer);
	bca.addFrame(file);
	bca.addFrame(file);
	bca.animate(ssActual, 3, -1);
	ssExpected << "\033[2J\033[1;37mtitle" << endl
			   << "source" << endl
			   << "\033[1;36m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Beijing 672" << endl
			   << "\033[1;33m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Vijayanagar 500" << endl
			   << "\033[1;32m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Cairo 400" << endl
			   << "\033[1;37mxlabel" << endl 
			   << "Frame: " << bca[0].getFrame() << endl
			   << "\033[2J\033[1;37mtitle" << endl
			   << "source" << endl
			   << "\033[1;36m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Beijing 672" << endl
			   << "\033[1;33m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Vijayanagar 500" << endl
			   << "\033[1;32m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Cairo 399" << endl
			   << "\033[1;37mxlabel" << endl 
			   << "Frame: " << bca[1].getFrame() << endl;		
	if (ssActual.str() != ssExpected.str()) {
		cout << RED << "testBarChartAnimateAnimate1: ssActual != ssExpected" << RESET << endl;
		return false;
	}
	cout << "testBarChartAnimateAnimate1: all passed!" << endl;
	return true;
}

bool testBarChartAnimateAnimate2() {
	string buffer;
	stringstream ssActual;
	stringstream ssExpected;
	BarChartAnimate bca("title", "xlabel", "source");
	ifstream file("brands.txt");
	getline(file, buffer);
	getline(file, buffer);
	getline(file, buffer);
	bca.addFrame(file);
	bca.addFrame(file);
	bca.animate(ssActual, 3, -1);
	ssExpected << "\033[2J\033[1;37mtitle" << endl
			   << "source" << endl
			   << "\033[1;37m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Coca-Cola 72537" << endl
			   << "\033[1;35m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Microsoft 70196" << endl
			   << "\033[1;35m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ IBM 53183" << endl
			   << "\033[1;37mxlabel" << endl 
			   << "Frame: " << bca[0].getFrame() << endl
			   << "\033[2J\033[1;37mtitle" << endl
			   << "source" << endl
			   << "\033[1;37m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Coca-Cola 72238" << endl
			   << "\033[1;35m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Microsoft 69769" << endl
			   << "\033[1;35m⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ IBM 53147" << endl
			   << "\033[1;37mxlabel" << endl 
			   << "Frame: " << bca[1].getFrame() << endl;		
	if (ssActual.str() != ssExpected.str()) {
		cout << RED << "testBarChartAnimateAnimate2: ssActual != ssExpected" << RESET << endl;
		return false;
	}
	cout << "testBarChartAnimateAnimate2: all passed!" << endl;
	return true;
}

bool testBarChartAnimateSquareBracketsOperator1() {
	string buffer;
	BarChartAnimate bca("title", "xlabel", "source");
	ifstream file("cities.txt");
	getline(file, buffer);
	getline(file, buffer);
	getline(file, buffer);
	bca.addFrame(file);
	bca.addFrame(file);
	bca.addFrame(file);
	if (bca[0].getFrame() != "1500") {
		cout << RED << "testBarChartAnimateSquareBracketsOperator1: getFrame failed" << RESET << endl;
		return false;
	} else if (bca[1].getSize() != 12) {
		cout << RED << "testBarChartAnimateSquareBracketsOperator1: getSize failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartAnimateSquareBracketsOperator1: all passed!" << endl;
	return true;
}

bool testBarChartAnimateSquareBracketsOperator2() {
	string buffer;
	BarChartAnimate bca("title", "xlabel", "source");
	ifstream file("brands.txt");
	getline(file, buffer);
	getline(file, buffer);
	getline(file, buffer);
	bca.addFrame(file);
	bca.addFrame(file);
	bca.addFrame(file);
	if (bca[1].getFrame() != "2000-02-01") {
		cout << RED << "testBarChartAnimateSquareBracketsOperator2: getFrame failed" << RESET << endl;
		return false;
	} else if (bca[2].getSize() != 100) {
		cout << RED << "testBarChartAnimateSquareBracketsOperator2: getSize failed" << RESET << endl;
		return false;
	}
	cout << "testBarChartAnimateSquareBracketsOperator2: all passed!" << endl;
	return true;
}

int main() {
	// bar.h tests
	testBarDefaultConstructor();
	testBarParamConstructor1();
	testBarParamConstructor2();
	testBarLessOperator1();
	testBarLessOperator2();
	testBarLessEqualOperator1();
	testBarLessEqualOperator2();
	testBarGreaterOperator1();
	testBarGreaterOperator2();
	testBarGreaterEqualOperator1();
	testBarGreaterEqualOperator2();
	
	// barchart.h tests
	testBarChartDefaultConstructor();
	testBarChartParamConstructor1();
	testBarChartParamConstructor2();
	testBarChartCopyConstructor1();
	testBarChartCopyConstructor2();
	testBarChartCopyOperator1();
	testBarChartCopyOperator2();
	testBarChartClear1();
	testBarChartClear2();
	testBarChartSetFrame1();
	testBarChartSetFrame2();
	testBarChartAddBar1();
	testBarChartAddBar2();
	testBarChartSquareBracketsOperator1();
	testBarChartSquareBracketsOperator2();
	testBarChartDump1();
	testBarChartDump2();
	testBarChartGraph1();
	testBarChartGraph2();

	// barchartanimate.h tests
	testBarChartAnimateParamConstructor();
	testBarChartAnimateAddFrame1();
	testBarChartAnimateAddFrame2();
	testBarChartAnimateAnimate1();
	testBarChartAnimateAnimate2();
	testBarChartAnimateSquareBracketsOperator1();
	testBarChartAnimateSquareBracketsOperator2();
    return 0;
}