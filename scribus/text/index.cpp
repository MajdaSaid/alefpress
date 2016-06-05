/*
 *  index.cpp
 *  ScribusProject
 *
 *  Created by Andreas Vox on 30.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <QDebug>

#include "index.h"



// find run with runStart <= pos < runEnd
uint RunIndex::search(int pos) const
{
	const std::vector<const uint>::iterator it = std::upper_bound(runEnds.begin(), runEnds.end(), pos);
	return it - runEnds.begin();
}


uint RunIndex::insert(int pos)
{
	uint i = search(pos);
	
	if (i >= runEnds.size())
	{
		runEnds.push_back(pos);
		return runEnds.size() - 1;
	}
	else
	{
		runEnds.insert(runEnds.begin() + i, pos);
		return i;
	}
}


void RunIndex::remove (uint idx)
{
	assert ( idx < runEnds.size() );

	runEnds.erase(runEnds.begin() + idx);
}


void RunIndex::adjust(int pos, int delta)
{
	int idx = search(pos);
	for (int i=idx; i < runEnds.size(); ++i)
	{
		runEnds[i] += delta;
	}
}


