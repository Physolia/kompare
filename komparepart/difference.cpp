/***************************************************************************
                                difference.cpp  -  description
                                -------------------
        begin                   : Sun Mar 4 2001
        copyright               : (C) 2001 by Otto Bruggeman
                                  and John Firebaugh
        email                   : otto.bruggeman@home.nl
                                  jfirebaugh@kde.org
****************************************************************************/
 
/***************************************************************************
**
**   This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 2 of the License, or
**   (at your option) any later version.
**
***************************************************************************/

#include "difference.h"

/** */
Difference::Difference( int linenoA, int linenoB )
{
	this->linenoA = linenoA;
	this->linenoB = linenoB;
};

/** */
Difference::~Difference()
{
};

void Difference::addSourceLine( QString line )
{
	sourceLines.append( line );
}

void Difference::addDestinationLine( QString line )
{
	destinationLines.append( line );
}

int Difference::sourceLineCount() const
{
	return sourceLines.count();
}

int Difference::destinationLineCount() const
{
	return destinationLines.count();
}

/** */
QString Difference::asString() const
{
	int linecountA = sourceLineCount();
	int linecountB = destinationLineCount();
	int lineendA = linenoA+linecountA-1;
	int lineendB = linenoB+linecountB-1;
	QString res;
	if (linecountB == 0)
		res = QString("%1,%2d%3").arg(linenoA).arg(lineendA).arg(linenoB-1);
	else if (linecountA == 0)
		res = QString("%1a%2,%3").arg(linenoA-1).arg(linenoB).arg(lineendB);
	else if (linenoA == lineendA)
		if (linenoB == lineendB)
			res = QString("%1c%2").arg(linenoA).arg(linenoB);
		else
			res = QString("%1c%2,%3").arg(linenoA).arg(linenoB).arg(lineendB);
	else if (linenoB == lineendB)
		res = QString("%1,%2c%3").arg(linenoA).arg(lineendA).arg(linenoB);
	else
		res = QString("%1,%2c%3,%4").arg(linenoA).arg(lineendA).arg(linenoB).arg(lineendB);

	return res;
}

#include "difference.moc"

