#pragma once

#include <string>
#include <list>

template <class T> class tableRowNode {

private:
	unsigned int noOfChainedNodes;

public: 
	tableRowNode() {
		noOfChainedNodes = 0;
	}
};

class tableRow
{
public:
	tableRow();
	~tableRow();
};

