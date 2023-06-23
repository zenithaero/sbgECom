// sbgCommonLib headers
#include <sbgCommon.h>

//----------------------------------------------------------------------//
//- Include specific header for WIN32 and UNIX platforms               -//
//----------------------------------------------------------------------//
#ifdef KERNEL
#include <zephyr/kernel.h>
#elif defined(WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <mach/mach_time.h>
#include <unistd.h>
#else
#include <unistd.h>
#endif

#include <time.h>

//----------------------------------------------------------------------//
//- Global singleton for the log callback							   -//
//----------------------------------------------------------------------//

/*!
 * Unique singleton used to log error messages.
 */
SbgCommonLibOnLogFunc	gLogCallback = NULL;

//----------------------------------------------------------------------//
//- Public functions                                                   -//
//----------------------------------------------------------------------//

SBG_COMMON_LIB_API uint32_t sbgGetTime(void)
{
#ifdef KERNEL
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);

	//
	// Return the current time in ms
	//
	return now.tv_sec * 1000 + now.tv_nsec / 1000000;
#elif defined(WIN32)
	//
	// Return the current time in ms
	//
	return clock() / (CLOCKS_PER_SEC / 1000);
#elif defined(__APPLE__)
	mach_timebase_info_data_t	timeInfo;
	mach_timebase_info(&timeInfo);

	//
	// Return the current time in ms
	//
	return (mach_absolute_time() * timeInfo.numer / timeInfo.denom) / 1000000.0;
#else
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);

	//
	// Return the current time in ms
	//
	return now.tv_sec * 1000 + now.tv_nsec / 1000000;
#endif
}

SBG_COMMON_LIB_API void sbgSleep(uint32_t ms)
{
#ifdef KERNEL
	k_usleep(ms * 1000);
#elif defined(WIN32)
	Sleep(ms);
#else
	struct timespec req;
	struct timespec rem;
	int ret;

	req.tv_sec = ms / 1000;
	req.tv_nsec = (ms % 1000) * 1000000L;

	for (;;)
	{
		ret = nanosleep(&req, &rem);

		if (ret == 0
	#ifndef __APPLE__
		|| (errno != EINTR)
	#endif	
	)
		{
			break;
		}
		else
		{
			req = rem;
		}
	}
#endif
}

SBG_COMMON_LIB_API void sbgCommonLibSetLogCallback(SbgCommonLibOnLogFunc logCallback)
{
	//
	// TODO: should we implement lock / sync mechanisms ?
	//
	gLogCallback = logCallback;
}

SBG_COMMON_LIB_API void sbgPlatformDebugLogMsg(const char *pFileName, const char *pFunctionName, uint32_t line, const char *pCategory, SbgDebugLogType logType, SbgErrorCode errorCode, const char *pFormat, ...)
{
	char		errorMsg[SBG_CONFIG_LOG_MAX_SIZE];
	va_list		args;

	assert(pFileName);
	assert(pFunctionName);
	assert(pCategory);
	assert(pFormat);

	//
	// Initialize the list of variable arguments on the latest function argument
	//
	va_start(args, pFormat);

	//
	// Generate the error message string
	//
	vsnprintf(errorMsg, sizeof(errorMsg), pFormat, args);

	//
	// Close the list of variable arguments
	//
	va_end(args);

	//
	// Check if there is a valid logger callback if not use a default output
	//
	if (gLogCallback)
	{
		gLogCallback(pFileName, pFunctionName, line, pCategory, logType, errorCode, errorMsg);
	}
	else
	{
		//
		// Log the correct message according to the log type
		//
		switch (logType)
		{
		case SBG_DEBUG_LOG_TYPE_ERROR:
			printf("*ERR * %s(%"PRIu32"): %s - %s\n\r", pFunctionName, line, sbgErrorCodeToString(errorCode), errorMsg);
			break;
		case SBG_DEBUG_LOG_TYPE_WARNING:
			printf("*WARN* %s(%"PRIu32"): %s - %s\n\r", pFunctionName, line, sbgErrorCodeToString(errorCode), errorMsg);
			break;
		case SBG_DEBUG_LOG_TYPE_INFO:
			printf("*INFO* %s(%"PRIu32"): %s\n\r", pFunctionName, line, errorMsg);
			break;
		case SBG_DEBUG_LOG_TYPE_DEBUG:
			printf("*DBG * %s(%"PRIu32"): %s\n\r", pFunctionName, line, errorMsg);
			break;
		default:
			printf("*UKNW* %s(%"PRIu32"): %s\n\r", pFunctionName, line, errorMsg);
			break;
		}
	}
}
