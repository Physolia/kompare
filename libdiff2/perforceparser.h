/**************************************************************************
**                             perforceparser.h
**                              -------------------
**      begin                   : Sun Sep  8 20:58:59 2002
**      copyright               : (c) 2002-2003 by Otto Bruggeman
**      email                   : otto.bruggeman@home.nl
**
***************************************************************************/
/***************************************************************************
**
**   This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 2 of the License, or
**   ( at your option ) any later version.
**
***************************************************************************/

#ifndef _PERFORCE_PARSER_H
#define _PERFORCE_PARSER_H

#include "parserbase.h"

namespace Diff2
{

class PerforceParser : public ParserBase
{
public:
	PerforceParser( const QStringList& diff );
	virtual ~PerforceParser();

protected:
	virtual bool parseContextDiffHeader();
	virtual bool parseRCSDiffHeader();
	virtual bool parseUnifiedDiffHeader();

protected:
	virtual enum Kompare::Format determineFormat();
};

} // End of namespace Diff2

#endif