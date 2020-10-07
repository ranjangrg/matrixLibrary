#include "./test.hpp"

std::unordered_map<std::string, bool> testMatrixConstructors() {
	std::unordered_map<std::string, bool> testResults = {
		{"usingRowColCount", false},
		{"usingVector", false},
		{"usingInitializerList", false}
	};

	//testResults["usingRowColCount"] 
	// test: usingRowColCount
	try {
		Matrix::MatrixStruct<int> matA  = Matrix::createMatrix<int>(3, 5);
		testResults["usingRowColCount"] = true;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;		
	}

	// test: usingVector
	try {
		std::vector<int> elems = {1,2,3,4,5,6,7,8,0};
		Matrix::MatrixStruct<int> matB  = Matrix::createMatrix<int>(3, 3, elems);
		testResults["usingVector"] = true;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;		
	}
	try {
		// should fail
		std::vector<int> elems = {1,2,3,4,5,6,7,8,0};
		Matrix::MatrixStruct<int> matC  = Matrix::createMatrix<int>(3, 4, elems);
		testResults["usingVector"] = false;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		testResults["usingVector"] = true;
	}

	// test: usingInitializerList
	try {
		Matrix::MatrixStruct<int> matD  = Matrix::createMatrix<int>(3, 3, {1,2,3,4,5,6,7,8,0});
		testResults["usingInitializerList"] = true;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;
	}

	return testResults;
}

std::unordered_map<std::string, bool> testMatrixOperators() {
	std::unordered_map<std::string, bool> testResults = {
		{"using (): Positive case", false},
		{"using  +: Positive case", false},
		{"using  +: Negative case", false},
		{"using  -: Positive case", false},
		{"using  -: Negative case", false},
		{"using ==: Positive case", false},
		{"using ==: Negative case", false},
		{"using  *: Positive case", false}
		//{"using  *: Negative case", false}
	};

	// matrices for test; suppose constructors work
	Matrix::MatrixStruct<int> matA  = Matrix::createMatrix<int>(5, 5);
	Matrix::MatrixStruct<int> matB  = Matrix::createMatrix<int>(5, 5);
	Matrix::MatrixStruct<int> matC  = Matrix::createMatrix<int>(2, 2, {9,5,4,-1});
	Matrix::MatrixStruct<int> matD  = Matrix::createMatrix<int>(2, 2, {9,5,4,-1});
	Matrix::MatrixStruct<int> matE  = Matrix::createMatrix<int>(3, 5);
	Matrix::MatrixStruct<int> matF  = Matrix::createMatrix<int>(2, 2, {1,2,3,4});
	Matrix::MatrixStruct<int> matG  = Matrix::createMatrix<int>(2, 2, {10,20,30,40});

	// test: usingBrackets: PASS
	try {
		for (size_t rowIdx = 0; rowIdx < matA.nRows; ++rowIdx) {
			for (size_t colIdx = 0; colIdx < matA.nCols; ++colIdx) {
				matA(rowIdx, colIdx);
			}
		}		
		testResults["using (): Positive case"] = true;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;		
	}

	// test: using + : PASS
	try {
		matA + matB;
		testResults["using  +: Positive case"] = true;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;		
	}
	try {
		Matrix::MatrixStruct<int> matSumCorrect  = Matrix::createMatrix<int>(2, 2, {11,22,33,44});
		Matrix::MatrixStruct<int> matSumA = matF + matG;
		for (size_t idx = 0; (idx < matSumA.elements.size()) && testResults["using  +: Positive case"]; ++idx) {
			testResults["using  +: Positive case"] = matSumA.elements.at(idx) == matSumCorrect.elements.at(idx);
		}
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;	
	}

	// test: using + : FAIL
	try {
		Matrix::MatrixStruct<int> matSumB = matA + matE;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		testResults["using  +: Negative case"] = true;
	}

	// test: using - : PASS
	try {
		Matrix::MatrixStruct<int> matDiffCorrect = Matrix::createMatrix<int>(2, 2, {9,18,27,36});
		Matrix::MatrixStruct<int> matDiff = matG - matF;
		for (size_t idx = 0; (idx < matDiff.elements.size()) && testResults["using  +: Positive case"]; ++idx) {
			testResults["using  -: Positive case"] = matDiff.elements.at(idx) == matDiffCorrect.elements.at(idx);
		}
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		testResults["using  -: Positive case"] = false;
	}
	// test: using - : FAIL
	try {
		matA - matE;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		testResults["using  -: Negative case"] = true;
	}

	// test: using == : PASS
	try {
		bool areSame = (matA == matB) && (matC == matD);
		testResults["using ==: Positive case"] = areSame ? true : false;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		testResults["using ==: Positive case"] = false;
	}
	// test: using == : FAIL
	try {
		bool areSame = (matA == matE) && (matF == matG);
		testResults["using ==: Negative case"] = areSame ? false : true;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		testResults["using ==: Negative case"] = false;
	}

	// test: using * : PASS
	try {
		Matrix::MatrixStruct<int> matProdCorrect = Matrix::createMatrix<int>(2, 2, {90,50,40,-10});
		Matrix::MatrixStruct<int> matProd = matC * 10;
		testResults["using  *: Positive case"] = true;
		for (size_t idx = 0; (idx < matProd.elements.size()) && testResults["using  *: Positive case"]; ++idx) {
			testResults["using  *: Positive case"] = matProd.elements.at(idx) == matProdCorrect.elements.at(idx);
		}
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		testResults["using  *: Positive case"] = false;
	}

	return testResults;
}

std::unordered_map<std::string, bool> testMatrixConvolution() {
	std::unordered_map<std::string, bool> testResults = {
		{"using Convolution method", false},
		{"test Convolution overflow", false}
	};

	// test: convolution == : PASS
	try {
		Matrix::MatrixStruct<int> mainMatrix  = Matrix::createMatrix<int>(5, 5, 
			{
				5,5,0,5,5,
				5,0,5,0,5,
				0,5,0,5,0,
				5,0,5,0,5,
				5,5,0,5,5
			});
		Matrix::MatrixStruct<int> kernelMatrix  = Matrix::createMatrix<int>(3, 3, 
			{
				0,1,0,
				2,2,5,
				5,5,0
			});
		Matrix::MatrixStruct<int> convolutedMatrixCorrect  = Matrix::createMatrix<int>(5, 5, 
			{
				60,45,60,60,45,
				15,65,35,65,40,
				55,35,65,35,40,
				35,90,35,65,60,
				40,20,40,35,25
			});
		Matrix::MatrixStruct<int> convolutedMatrix = Matrix::convoluteMatrixUsingKernel(mainMatrix, kernelMatrix);

		testResults["using Convolution method"] = true;
		for (size_t idx = 0; (idx < convolutedMatrix.elements.size()) && testResults["using Convolution method"]; ++idx) {
			testResults["using Convolution method"] = convolutedMatrix.elements.at(idx) == convolutedMatrixCorrect.elements.at(idx);
		}
		//Matrix::dumpMatrixInfo(convolutedMatrix);
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		testResults["using Convolution method"] = false;
	}

	// test: overflow == : 
	try {
		Matrix::MatrixStruct<signed int> mainMatrix  = Matrix::createMatrix<signed int>(5, 5, 
			{
				-2147483648,-2147483648,0,5,5,
				5,0,5,0,5,
				0,5,0,5,0,
				5,0,5,0,5,
				5,5,0,5,5
			});
		Matrix::MatrixStruct<signed int> kernelMatrix  = Matrix::createMatrix<signed int>(3, 3, 
			{
				1,1,0,
				2,25,5,
				5,5,0
			});
		Matrix::MatrixStruct<signed int> convolutedMatrixCorrect  = Matrix::createMatrix<signed int>(5, 5, 
			{
				60,45,60,60,45,
				15,65,35,65,40,
				55,35,65,35,40,
				35,90,35,65,60,
				40,20,40,35,25
			});
		Matrix::MatrixStruct<signed int> convolutedMatrix = Matrix::convoluteMatrixUsingKernel(mainMatrix, kernelMatrix);
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		testResults["test Convolution overflow"] = true;
	}

	return testResults;
}

std::unordered_map<std::string, bool> testMatrixMethods() {
	std::unordered_map<std::string, bool> testResults = {
		{"using Matrix method: dot product", false}
	};

	try {
		Matrix::MatrixStruct<int> matA  = Matrix::createMatrix<int>(2, 3, 
			{
				1,2,3,
				4,5,6
			});		
		Matrix::MatrixStruct<int> matB  = Matrix::createMatrix<int>(3, 2, 
			{
				7,8,
				9,10,
				11,12
			});
		Matrix::MatrixStruct<int> matC  = Matrix::createMatrix<int>(2, 3, 
			{
				2,5,1,
				4,0,7
			});

		Matrix::dumpMatrixInfo(matA);
		std::cout << '-' << std::endl;
		Matrix::dumpMatrixInfo(matB);

		testResults["using Matrix method: dot product"] = true;
	} catch (std::exception& e) {
		//std::cout << e.what() << std::endl;	
		//testResults["using Matrix method: dot product"] = true;
	}

	return testResults;
}

void printResults(const std::unordered_map<std::string, bool>& testResults) {
	std::string result;
	for (auto& test : testResults) {
		result = test.second ? "PASSED" : "FAILED";
		std::cout << '[' << result << "] " << test.first << std::endl;
	}
}

void testAll() {
	std::unordered_map<std::string, bool> testResults;

	testResults = testMatrixConstructors();
	printResults(testResults);
	testResults = testMatrixOperators();
	printResults(testResults);
	testResults = testMatrixConvolution();
	printResults(testResults);

	/*
	testResults = testMatrixMethods();
	printResults(testResults);
	*/
	
}

int main() {
	std::cout << "Program started." << std::endl;

	testAll();

	return 0;
}