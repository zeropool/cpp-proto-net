#pragma once

#include "Strategy.h"
#include "globalmembers.h"

#include <boost/bind.hpp>
#include <boost/format.hpp>

#define DBL_TEST_UPPER_BOUNDERY 9999999
#define DBL_TEST_LOWER_BOUNDERY -9999999

class CNonUseChecker : public CConditionChecker<double>
{
public:
	bool Test(double val) { return false; }
};

class CValueChecker : public CConditionChecker<double>
{
public:
	CValueChecker() : m_comparsion(NOT_COMPARE), m_targetVal(0)
	{
	}

	virtual double TargetVal() { return m_targetVal; }
	void SetTargetVal(double val) { m_targetVal = val; }

	COMPARE_OP Comparsion() const { return m_comparsion; }
	void Comparsion(COMPARE_OP val) { m_comparsion = val; }

	bool Test(double valToTest)
	{
		_ASSERT(valToTest < DBL_TEST_UPPER_BOUNDERY && valToTest > DBL_TEST_LOWER_BOUNDERY);

		double targetVal = TargetVal();

		if(valToTest < DBL_TEST_UPPER_BOUNDERY && 
			valToTest > DBL_TEST_LOWER_BOUNDERY)
		{
			switch(m_comparsion)
			{
			case GREATER_THAN:
				logger.Info(boost::str(boost::format("? %f > %f")
					% valToTest % targetVal));
				return valToTest > targetVal;
			case GREATER_EQUAL_THAN:
				logger.Info(boost::str(boost::format("? %f >= %f")
					% valToTest % targetVal));
				return DoubleGreaterEqual(valToTest, targetVal);
			case LESS_THAN:
				logger.Info(boost::str(boost::format("? %f < %f")
					% valToTest % targetVal));
				return valToTest < targetVal;
			case LESS_EQUAL_THAN:
				logger.Info(boost::str(boost::format("? %f <= %f")
					% valToTest % targetVal));
				return DoubleGreaterEqual(targetVal, valToTest);
			default:
				return false;
			}
		}
		
		return false; 
	}

protected:
	
	double m_targetVal;
	COMPARE_OP m_comparsion;	

};

class CDiffStrategy : public CStrategy<double>
{
public:
	virtual ~CDiffStrategy(){}

	entity::PosiDirectionType Direction() const { return m_direction; }
	void Direction(entity::PosiDirectionType val) { m_direction = val; }

	virtual void Test(){}

private:
	entity::PosiDirectionType m_direction;

};

typedef boost::function<double()> GetPortfolioCostFunc;

class CCostValueChecker : public CValueChecker
{
public:
	void SetGetCostFunc(GetPortfolioCostFunc funcGetCost){ m_func = funcGetCost; }
	virtual double TargetVal() 
	{
		double cost = m_func();
		if(Comparsion() < LESS_THAN)
			return cost + m_targetVal;
		else
			return cost - m_targetVal;
	}

private:
	GetPortfolioCostFunc m_func;
};