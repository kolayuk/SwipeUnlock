/*
 ============================================================================
 Name		: Application.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CApplication declaration
 ============================================================================
 */

#ifndef APPLICATION_H
#define APPLICATION_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <ProcessMonitor.h>
// CLASS DECLARATION
class CApplication : public CBase, public MProcessCallBack
	{
public:
	// Constructors and destructor
	~CApplication();
	static CApplication* NewL();
	static CApplication* NewLC();
	void StateChanged();
	CProcessMonitor* iMon;
private:
	CApplication();
	void ConstructL();
	};

#endif // APPLICATION_H
