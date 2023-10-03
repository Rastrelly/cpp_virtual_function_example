#include <iostream>
#include <vector>

struct point
{
	float x, y;
};

class functionalAnalyzer
{
private:
	point min, max;
	float x1, x2;
	int nCoeffs;
	std::vector <point> funcData;
	std::vector <float> coefficients;

public:
	void setX1(float val) { x1 = val; };
	void setX2(float val) { x2 = val; };
	void setNCoeffs(int val) { nCoeffs = val; };
	void addFuncPoint(point pt) { funcData.push_back(pt); };
	void addCoefficient(float val) { coefficients.push_back(val); };
	void setMin(point val) { min = val; };
	void setMax(point val) { max = val; };
	
	float getX1() { return x1; };
	float getX2() { return x2; };
	int getNCoeffs() { return nCoeffs; };
	std::vector <point> getFuncData() { return funcData; };
	point getFuncPoint(int id) { return getFuncData()[id]; };
	std::vector<float> getCoefficients() { return coefficients; };
	point getMin() { return min; };
	point getMax() { return max; };

	int getFuncDataLength() { return getFuncData().size(); };

	//printing point value
	void printPoint(std::string label, point pt)
	{
		std::cout << label.c_str() << pt.x << "; " << pt.y << "\n";
	}

	//print minimum and maximum
	void printMinMax()
	{
		printPoint("Min = ", getMin());
		printPoint("Max = ", getMax());
	}

	//data collector
	void requestUserData()
	{
		float data;
		std::cout << "Input X1:\n";
		std::cin >> data;
		setX1(data);

		std::cout << "Input X2:\n";
		std::cin >> data;
		setX2(data);

		if (getX1() > getX2())
		{
			data = getX1();
			setX1(getX2());
			setX2(data);
		}

		int cCoeff = 0;
		while (cCoeff < nCoeffs)
		{
			std::cout << "Input coefficient " << cCoeff+1 << ":\n";
			std::cin >> data;
			addCoefficient(data);
			cCoeff++;
		}
	}

	//constructor
	functionalAnalyzer()
	{
		setNCoeffs(3);
	}

	//check vector length
	bool vectorIsFine(std::vector<float> coeffs, int nCoeffs)
	{
		if (coeffs.size() >= nCoeffs) return true;
		else return false;
	}

	//virtual function claculator
	virtual float calcFunc(float x, std::vector<float> coeffs, int nCoeffs)
	{
		if (vectorIsFine(coeffs, nCoeffs))
			return coeffs[0] * pow(x, 2) + coeffs[1] * x + coeffs[2];
		return 0;
	}

	//generate array of points
	void buildDataArray()
	{
		float step = (getX2() - getX1()) / 100.0f;
		std::cout << "* step = " << step << std::endl;
		float cx = getX1();
		while (cx <= getX2())
		{
			point pOut = {cx,calcFunc(cx,getCoefficients(),getNCoeffs())};
			printPoint("Data point added: ", pOut);
			addFuncPoint(pOut);
			cx += step;
		}
	}

	//find extremes
	void findMinMax()
	{
		setMin(getFuncPoint(0));
		setMax(getFuncPoint(0));
		int l = getFuncDataLength();
		for (int i = 1; i < l; i++)
		{
			point cPoint = getFuncPoint(i);
			if (cPoint.y < getMin().y) setMin(cPoint);
			if (cPoint.y > getMax().y) setMax(cPoint);
		}
	}

	//global process method
	void performOps()
	{
		std::cout << "Getting user data\n";
		requestUserData();
		std::cout << "Building data array...\n";
		buildDataArray();
		std::cout << "Searching extremes...\n";
		findMinMax();
		std::cout << "Outputting result\n";
		printMinMax();
	}
};

class sinAnalyzer : public functionalAnalyzer
{
public:
	//child constructor
	sinAnalyzer()
	{
		setNCoeffs(2);
	}
	//overridden func calc
	virtual float calcFunc(float x, std::vector<float> coeffs, int nCoeffs) override
	{
		if (vectorIsFine(coeffs, nCoeffs))
		{
			return coeffs[0] * sin(coeffs[1] * x * (3.14f/180.0f));
		}
		return 0;
	}
};

class cubeAnalyzer : public functionalAnalyzer
{
public:
	//child constructor
	cubeAnalyzer()
	{
		setNCoeffs(4);
	}
	//overridden func calc
	virtual float calcFunc(float x, std::vector<float> coeffs, int nCoeffs) override
	{
		if (vectorIsFine(coeffs, nCoeffs))
		{
			return coeffs[0] * pow(x, 3) + coeffs[1] * pow(x, 2) + coeffs[2] * x + coeffs[3];
		}
		return 0;
	}
};

int main()
{
	
	std::cout << "---- PARENT CLASS ----\n";
	functionalAnalyzer fa;
	fa.performOps();

	std::cout << "---- CHILD CLASS 1 ----\n";
	sinAnalyzer sa;
	sa.performOps();

	std::cout << "---- CHILD CLASS 2 ----\n";
	cubeAnalyzer ca;
	ca.performOps();
}