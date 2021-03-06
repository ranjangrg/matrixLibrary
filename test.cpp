#include "./test.hpp"

bool logError = false;

void logException(std::exception& e) { 
	if (logError) {
		std::cout << e.what() << std::endl; 
	}
}

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
	} catch (std::exception& e) { logException(e); }

	// test: usingVector
	try {
		std::vector<int> elems = {1,2,3,4,5,6,7,8,0};
		Matrix::MatrixStruct<int> matB  = Matrix::createMatrix<int>(3, 3, elems);
		testResults["usingVector"] = true;
	} catch (std::exception& e) { logException(e); }

	try {
		// should fail
		std::vector<int> elems = {1,2,3,4,5,6,7,8,0};
		Matrix::MatrixStruct<int> matC  = Matrix::createMatrix<int>(3, 4, elems);
		testResults["usingVector"] = false;
	} catch (std::exception& e) {
		testResults["usingVector"] = true;
	}

	// test: usingInitializerList
	try {
		Matrix::MatrixStruct<int> matD  = Matrix::createMatrix<int>(3, 3, {1,2,3,4,5,6,7,8,0});
		testResults["usingInitializerList"] = true;
	} catch (std::exception& e) {
		logException(e);
	}

	return testResults;
}

std::unordered_map<std::string, bool> testMatrixOperators() {
	std::unordered_map<std::string, bool> testResults = {
		{"using (): get case", false},
		{"using (): set case", false},
		{"using  +: Positive case", false},
		{"using  +: Negative case", false},
		{"using  -: Positive case", false},
		{"using  -: Negative case", false},
		{"using ==: Positive case", false},
		{"using ==: Negative case", false},
		{"using  *: with Scalar", false},
		{"using  *: with another matrix", false}
	};

	// matrices for test; suppose constructors work
	Matrix::MatrixStruct<int> matA  = Matrix::createMatrix<int>(5, 5);
	Matrix::MatrixStruct<int> matB  = Matrix::createMatrix<int>(5, 5);
	Matrix::MatrixStruct<int> matC  = Matrix::createMatrix<int>(2, 2, {9,5,4,-1});
	Matrix::MatrixStruct<int> matD  = Matrix::createMatrix<int>(2, 2, {9,5,4,-1});
	Matrix::MatrixStruct<int> matE  = Matrix::createMatrix<int>(3, 5);
	Matrix::MatrixStruct<int> matF  = Matrix::createMatrix<int>(2, 2, {1,2,3,4});
	Matrix::MatrixStruct<int> matG  = Matrix::createMatrix<int>(2, 2, {10,20,30,40});

	// test: usingBrackets: get
	try {
		for (size_t rowIdx = 0; rowIdx < matA.nRows; ++rowIdx) {
			for (size_t colIdx = 0; colIdx < matA.nCols; ++colIdx) {
				matA(rowIdx, colIdx);
			}
		}		
		testResults["using (): get case"] = true;
	} catch (std::exception& e) {
		logException(e);		
	}

	// test: usingBrackets: set
	int newValue = 128;
	try {
		for (size_t rowIdx = 0; rowIdx < matA.nRows; ++rowIdx) {
			for (size_t colIdx = 0; colIdx < matA.nCols; ++colIdx) {
				matA(rowIdx, colIdx) = newValue;
			}
		}
		bool setSuccess = true;
		for (size_t rowIdx = 0; (rowIdx < matA.nRows) && (setSuccess); ++rowIdx) {
			for (size_t colIdx = 0; colIdx < matA.nCols; ++colIdx) {
				setSuccess = matA(rowIdx, colIdx) == newValue;
			}
		}
		testResults["using (): set case"] = setSuccess;
	} catch (std::exception& e) {
		logException(e);	
	}

	// test: using + : PASS
	try {
		matA + matB;
		testResults["using  +: Positive case"] = true;
	} catch (std::exception& e) {
		logException(e);	
	}
	try {
		Matrix::MatrixStruct<int> matSumCorrect  = Matrix::createMatrix<int>(2, 2, {11,22,33,44});
		Matrix::MatrixStruct<int> matSumA = matF + matG;
		for (size_t idx = 0; (idx < matSumA.elements.size()) && testResults["using  +: Positive case"]; ++idx) {
			testResults["using  +: Positive case"] = matSumA.elements.at(idx) == matSumCorrect.elements.at(idx);
		}
	} catch (std::exception& e) {
		logException(e);
	}

	// test: using + : FAIL
	try {
		Matrix::MatrixStruct<int> matSumB = matA + matE;
	} catch (std::exception& e) {
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
		logException(e);
		testResults["using  -: Positive case"] = false;
	}
	// test: using - : FAIL
	try {
		matA - matE;
	} catch (std::exception& e) {
		testResults["using  -: Negative case"] = true;
	}

	// test: using == : PASS
	try {
		bool areSame = (matA == matB) && (matC == matD);
		testResults["using ==: Positive case"] = areSame ? true : false;
	} catch (std::exception& e) {
		logException(e);
		testResults["using ==: Positive case"] = false;
	}
	// test: using == : FAIL
	try {
		bool areSame = (matA == matE) && (matF == matG);
		testResults["using ==: Negative case"] = areSame ? false : true;
	} catch (std::exception& e) {
		logException(e);	
		testResults["using ==: Negative case"] = false;
	}

	// test: using * : scalar
	try {
		Matrix::MatrixStruct<int> matProdCorrectA = Matrix::createMatrix<int>(2, 2, {90,50,40,-10});
		Matrix::MatrixStruct<int> matProdA = matC * 10;
		testResults["using  *: with Scalar"] = true;
		for (size_t idx = 0; (idx < matProdA.elements.size()) && testResults["using  *: with Scalar"]; ++idx) {
			testResults["using  *: with Scalar"] = matProdA.elements.at(idx) == matProdCorrectA.elements.at(idx);
		}
	} catch (std::exception& e) {
		logException(e);
		testResults["using  *: with Scalar"] = false;
	}

	// test: using * : with matrix
	try {
		Matrix::MatrixStruct<int> matH  = Matrix::createMatrix<int>(2, 3, {1,0,-3,-2,4,1});
		Matrix::MatrixStruct<int> matI  = Matrix::createMatrix<int>(3, 4, {
			1,0,4,1,
			-2,3,-1,5,
			0,-1,2,1
		});
		Matrix::MatrixStruct<int> matProdCorrectB = Matrix::createMatrix<int>(2, 4, {
			1,3,-2,-2,
			-10,11,-10,19
		});
		Matrix::MatrixStruct<int> matProdB = matH * matI;

		testResults["using  *: with another matrix"] = true;
		for (size_t idx = 0; (idx < matProdB.elements.size()) && testResults["using  *: with another matrix"]; ++idx) {
			testResults["using  *: with another matrix"] = matProdB.elements.at(idx) == matProdCorrectB.elements.at(idx);
		}
	} catch (std::exception& e) {
		logException(e);	
		testResults["using  *: with another matrix"] = false;
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
	} catch (std::exception& e) {
		logException(e);
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
		testResults["test Convolution overflow"] = true;
	}

	return testResults;
}

std::unordered_map<std::string, bool> testMatrixMethods() {
	std::unordered_map<std::string, bool> testResults = {
		{"using Matrix method: transpose", false}
	};
	Matrix::MatrixStruct<int> matA  = Matrix::createMatrix<int>(2, 3, 
		{
			1,2,3,
			4,5,6
		});		
	Matrix::MatrixStruct<int> transposedCorrect = Matrix::createMatrix<int>(3, 2, 
		{
			1,4,
			2,5,
			3,6
		});

	try {
		Matrix::MatrixStruct<int> transposed = Matrix::transposeMatrix(matA);
		testResults["using Matrix method: transpose"] = true;
		for (size_t idx = 0; (idx < transposed.elements.size()) && testResults["using Matrix method: transpose"]; ++idx) {
			testResults["using Matrix method: transpose"] = transposed.elements.at(idx) == transposedCorrect.elements.at(idx);
		}
	} catch (std::exception& e) {
		logException(e);
		testResults["using Matrix method: transpose"] = false;
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
	testResults = testMatrixMethods();
	printResults(testResults);
	
}

int main() {
	std::cout << "Program started." << std::endl;

	testAll();

	return 0;
}