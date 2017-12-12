#pragma once
#include "DynArr.h"


class DynArrTwo : public DynArr {
public:
	DynArrTwo();

	DynArrTwo(std::initializer_list<int> _arg1, std::initializer_list<int> _arg2);

	DynArrTwo(DynArrTwo const& _arg);

	DynArrTwo(DynArr const& _arg);

	DynArrTwo(DynArrTwo&& _arg);

	virtual ~DynArrTwo();

	DynArrTwo& operator = (DynArrTwo const& _arg);

	DynArrTwo& operator = (DynArr const& _arg) override;

	DynArrTwo& operator += (DynArr const& _arg);

	virtual bool isDynArrTwo() const;

	DynArrTwo& operator = (DynArrTwo&& _arg);

	bool operator == (DynArrTwo const& _arg) const;

	bool operator != (DynArrTwo const& _arg) const; 

	virtual void Copy(DynArrTwo const& _arg);

	virtual void Move(DynArrTwo& _arg);

	virtual DynArrTwo getDynArrTwo() const;

	virtual void print(std::string) const;

	virtual void clear();

	virtual int* getPointerTwo() const;

	virtual int getSizeTwo() const;

private:
	int* b;
	int sizeB;
};