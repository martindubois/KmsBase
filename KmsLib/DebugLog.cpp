
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	KmsLib/DebugLog.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== C ==================================================================
#include <time.h>

#ifdef _KMS_WINDOWS_
	#include <process.h>
#endif // _KMS_WINDOWS_

// ===== Includes ===========================================================
#include <KmsLib/DebugLog.h>

// Constants / Constantes
/////////////////////////////////////////////////////////////////////////////

static const char * DAY_NAMES[] =
{
	"Sunday"	,
	"Monday"	,
	"Tuesday"	,
	"Wednesday"	,
	"Thursday"	,
	"Friday"	,
	"Saturday"	,
};

static const char * MONTH_NAMES[] =
{
	"January"	,
	"February"	,
	"March"		,
	"April"		,
	"May"		,
	"June"		,
	"July"		,
	"August"	,
	"September"	,
	"October"	,
	"November"	,
	"December"	,
};

namespace KmsLib
{
	
	// Public
	/////////////////////////////////////////////////////////////////////////

	DebugLog::DebugLog(const char * aFolder, const char * aName)
	{
		assert(NULL != aFolder	);
		assert(NULL != aName	);

		sIndex++;

		char lFileName[2048];

		sprintf_s(lFileName, "%s/pid_%u_log_%s_%u.txt", aFolder, _getpid(), aName, sIndex);

		if (0 == fopen_s(&mFile, lFileName, "w"))
		{
			assert(NULL != mFile);

			Log(__FILE__, __FUNCTION__, __LINE__);
			LogTime();
			Log("Creating log file");
		}
		else
		{
			mFile = NULL;
		}
	}

	DebugLog::~DebugLog()
	{
		if (NULL != mFile)
		{
			Log(__FILE__, __FUNCTION__, __LINE__);
			LogTime();
			Log("Closing log file");

			int lRet = fclose(mFile);
			assert(0 == lRet);

			(void)(lRet);
		}
	}

	DebugLog::operator FILE * ()
	{
		return mFile;
	}

	bool DebugLog::IsEnabled() const
	{
		return (NULL != mFile);
	}

	void DebugLog::Log( const Exception * aException)
	{
		assert(NULL != aException);

		if (NULL != mFile)
		{
			fprintf(mFile, "EXCEPTION");
			aException->Write(mFile);
		}
	}

	void DebugLog::Log(const char * aFile, const char * aFunction, unsigned int aLine)
	{
		assert(NULL != aFile		);
		assert(NULL != aFunction	);

		if (NULL != mFile)
		{
			fprintf(mFile, "%s (%u) - %s\n", aFile, aLine, aFunction);
		}
	}

	void DebugLog::Log(const char *aMessage)
	{
		assert(NULL != aMessage);

		if (NULL != mFile)
		{
			fprintf(mFile, "%s\n", aMessage);
		}
	}

	void DebugLog::LogTime()
	{
		if (NULL != mFile)
		{
			time_t	lTime;

			time(&lTime);

			tm lLT;

			int lRet = localtime_s(&lLT, &lTime);
			if (0 == lRet)
			{
				fprintf(mFile, "%s, %s %u %04u - %02u:%02u:%02u\n",
					DAY_NAMES[lLT.tm_wday], MONTH_NAMES[lLT.tm_mon], lLT.tm_mday, lLT.tm_year + 1900,
					lLT.tm_hour, lLT.tm_min, lLT.tm_sec);
			}
			else
			{
				Log(__FILE__, __FUNCTION__, __LINE__);
				fprintf(mFile, "localtime_s( , 0x%08x%08x ) failed returning %u\n",
					static_cast<unsigned int>(lTime & 0xffffffff), static_cast<unsigned int>(lTime >> 32),
					lRet);
			}
		}
	}

	// Private
	/////////////////////////////////////////////////////////////////////////

	unsigned int DebugLog::sIndex = 0;

}
