/***************************************************************************
			main.cpp  -  description
			-------------------
	begin			: Sun Mar 4 2001
	copyright			: (C) 2001 by Otto Bruggeman
	email			: otto.bruggeman@home.nl
***************************************************************************/

/***************************************************************************
**
**   This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 2 of the License, or
**   (at your option) any later version.
**
****************************************************************************/

#include <qcstring.h>

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>
#include <kdebug.h>
#include <kmessagebox.h>

#include "kdiff_shell.h"
#include "kcomparedialog.h"

static const char *description =
	I18N_NOOP("A program to view the differences between files and optionally generate a diff." );

static const char *version = "v2.0";

static KCmdLineOptions options[] =
{
	{ "f format", I18N_NOOP( "The format of the generated diff. It can be one of\nthese: Context, Ed, Normal, RCS, Unified." ), 0 },
	{ "+[URL [URL2]]", I18N_NOOP( "Document to open. If only one url is given\nit is considered a .diff file. If 2 files are given\nkdiff will compare them." ), 0 },
	{ 0, 0, 0 }
};

int main(int argc, char *argv[])
{
	KAboutData aboutData( "kdiff", I18N_NOOP("KDiff"), version, description,
	                      KAboutData::License_GPL,
	                      "(c) 2001, Otto Bruggeman", 0, 0, "otto.bruggeman@home.nl");
	aboutData.addAuthor( "Otto Bruggeman", "Author", "otto.bruggeman@home.nl" );
	aboutData.addAuthor( "John Firebaugh", "Author", "jfirebaugh@kde.org" );
	aboutData.addCredit( "Malte Starostik", "Big help :)", "malte@kde.org" );
	aboutData.addCredit( "Bernd Gehrmann", "Cervisia diff viewer", "bernd@physik.hu-berlin.de" );
	KCmdLineArgs::init(argc, argv, &aboutData);
	KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.
	KApplication app;

	// see if we are starting with session management
	if (app.isRestored())
	{
		RESTORE(KDiffShell)
	}
	else
	{
		KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

		KDiffShell* widget;
		QCString format;

		// I would suggest something like this:
		// DiffSettings* settings = new DiffSettings();
		// settings->parseCmdLineArgs( args );

		// ...instead of this:
		if ( args->isSet( "f" ) )
		{
			// a diffformat has been set
			// check if it is valid...
			format = args->getOption( "f" );
			// kdDebug() << format << endl;
			format = format.upper(); // make uppercase to ease comparing
			// kdDebug() << format << endl;
			// Some checking for the format... we could abort here if necessary
			if ( format != "CONTEXT" && format != "ED" && format != "NORMAL" \
			     && format != "RCS" && format != "UNIFIED" )
			{
				kdDebug() << "Unknown diff format" << endl;
				return 0;
			}
		}

		switch ( args->count() )
		{
		case 0:  // no files, show compare dialog
			{
				KCompareDialog* dialog = new KCompareDialog();
				if( dialog->exec() == QDialog::Accepted ) {
					KURL source = dialog->getSourceURL();
					KURL destination = dialog->getDestinationURL();
					widget = new KDiffShell();
					widget->show();
					if ( !format.isEmpty() )
						widget->setFormat( format );
					widget->compare( source, destination );
				} else {
					return 0;
				}
				delete dialog;
			}
			break;
		case 1:  // 1 file -> it is a diff, use load()
			widget = new KDiffShell();
			widget->show();
			if ( !format.isEmpty() )
				widget->setFormat( format );
			widget->load( args->url( 0 ) );
			break;
		case 2:  // 2 files -> diff them with compare
			widget = new KDiffShell();
			widget->show();
			if ( !format.isEmpty() )
				widget->setFormat( format );
			widget->compare( args->url( 0 ), args->url( 1 ) );
			break;
		default: // error
			KMessageBox::error( NULL, i18n( "Sorry you gave too many arguments, dont know what to do with them..." ) );
			return 0;
			break;
		}
		args->clear();
	}

	return kapp->exec();
}
