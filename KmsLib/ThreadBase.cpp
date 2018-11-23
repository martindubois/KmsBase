
// Author   KMS - Martin Dubois, ing.
// Product  KmsBase
// File     KmsLib/ThreadBase.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== C ==================================================================
#include <assert.h>

// ===== Windows ============================================================
#include <Windows.h>

// ===== Includes ===========================================================
#include <KmsLib/Exception.h>

#include <KmsLib/ThreadBase.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

static const int PRIORITIES[KmsLib::ThreadBase::PRIORITY_QTY] =
{
    0,
    THREAD_PRIORITY_IDLE         ,
    THREAD_PRIORITY_BELOW_NORMAL ,
    THREAD_PRIORITY_NORMAL       ,
    THREAD_PRIORITY_ABOVE_NORMAL ,
    THREAD_PRIORITY_TIME_CRITICAL,
};

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static DWORD WINAPI Run(PVOID aParameter);

namespace KmsLib
{

    // Public
    /////////////////////////////////////////////////////////////////////////

    void ThreadBase::Sleep_ms(unsigned int aDelay_ms)
    {
        Sleep(aDelay_ms);
    }

    void ThreadBase::Sleep_s(unsigned int aDelay_s)
    {
        Sleep(1000 * aDelay_s);
    }

    void ThreadBase::Sleep_us(unsigned int aDelay_us)
    {
        Sleep(aDelay_us / 1000);
    }

    ThreadBase::~ThreadBase()
    {
        if (NULL != mThread)
        {
            BOOL lRetB = CloseHandle(mThread);
            assert(lRetB);
        }
    }

    ThreadBase::Priority ThreadBase::GetCurrentPriority() const
    {
        if (NULL != mThread)
        {
            switch (GetThreadPriority(mThread))
            {
            case THREAD_PRIORITY_ABOVE_NORMAL:
                return PRIORITY_HIGH;

            case THREAD_PRIORITY_BELOW_NORMAL:
                return PRIORITY_LOW;

            case THREAD_PRIORITY_ERROR_RETURN:
                throw new Exception(Exception::CODE_THREAD_ERROR, "GetThreadPriority(  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, 0);

            case THREAD_PRIORITY_HIGHEST      :
            case THREAD_PRIORITY_TIME_CRITICAL:
                return PRIORITY_CRITICAL;

            case THREAD_PRIORITY_IDLE  :
            case THREAD_PRIORITY_LOWEST:
                return PRIORITY_IDLE;

            case THREAD_PRIORITY_NORMAL:
                return PRIORITY_NORMAL;

            default: assert(false);
            }
        }

        return PRIORITY_UNKNOWN;
    }

    ThreadBase::Priority ThreadBase::GetPriority() const
    {
        assert(PRIORITY_UNKNOWN != mPriority);
        assert(PRIORITY_QTY     > mPriority );

        return mPriority;
    }

    ThreadBase::State ThreadBase::GetState() const
    {
        assert(STATE_QTY > mState);

        return mState;
    }

    bool ThreadBase::IsRunning() const
    {
        assert(STATE_QTY > mState);

        return (STATE_RUNNING == mState);
    }

    bool ThreadBase::IsStopped() const
    {
        assert(STATE_QTY > mState);

        return (STATE_INIT == mState);
    }

    bool ThreadBase::IsStopping() const
    {
        switch (mState)
        {
        case STATE_INIT           :
        case STATE_RUNNING        :
        case STATE_START_REQUESTED:
        case STATE_STARTING       :
            break;

        case STATE_STOP_REQUESTED:
        case STATE_STOPPING      :
            return true;

        default: assert(false);
        }

        return false;
    }

    void ThreadBase::SetPriority(ThreadBase::Priority aPriority)
    {
        assert(PRIORITY_UNKNOWN != aPriority);
        assert(PRIORITY_QTY     >  aPriority);

        assert(PRIORITY_UNKNOWN != mPriority);
        assert(PRIORITY_QTY     >  mPriority);

        mPriority = aPriority;

        if (NULL != mThread)
        {
            ApplyPriority();
        }
    }

    void ThreadBase::Start()
    {
        switch (mState)
        {
        case STATE_STOPPING:
            assert(NULL != mThread);

            CloseThread();
            assert(STATE_INIT == mState);
            // no break;

        case STATE_INIT    :
            assert(NULL == mThread);

            mState = STATE_START_REQUESTED;

            mThread = CreateThread(NULL, 0, ::Run, this, 0, &mThreadId);
            if (NULL == mThread)
            {
                // NOT TESTED  KmsLib.ThreadBase.ErrorHandling
                //             CreateThread fail
                mState = STATE_INIT;

                throw new Exception(Exception::CODE_THREAD_ERROR, "CreateThread( , , , , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, 0);
            }
            break;

        default:
            throw new Exception(Exception::CODE_STATE_ERROR, "Invalid state", NULL, __FILE__, __FUNCTION__, __LINE__, mState);
        }
    }

    void ThreadBase::Stop()
    {
        switch (mState)
        {
        case STATE_INIT          :
        case STATE_STOP_REQUESTED:
        case STATE_STOPPING      :
            break;

        case STATE_RUNNING:
            mState = STATE_STOP_REQUESTED;
            break;

        default: assert(false);

        case STATE_START_REQUESTED:
        case STATE_STARTING       :
            // NOT TESTED  KmsLib.ThreadBase.ErrorHandling
            //             Stop while still starting
            throw new Exception(Exception::CODE_STATE_ERROR, "Invalid state", NULL, __FILE__, __FUNCTION__, __LINE__, mState);
        }
    }

    bool ThreadBase::StopAndWait(bool aForce, unsigned int aTimeout_ms)
    {
        Stop();

       return Wait(aForce, aTimeout_ms);
    }

    bool ThreadBase::Wait(bool aForce, unsigned int aTimeout_ms)
    {
        bool lResult = false;

        switch (mState)
        {
        case STATE_INIT :
            lResult = true;
            break;

        case STATE_RUNNING        :
        case STATE_START_REQUESTED:
        case STATE_STARTING       :
        case STATE_STOP_REQUESTED :
        case STATE_STOPPING       :
            assert(NULL != mThread);

            switch (WaitForSingleObject(mThread, aTimeout_ms))
            {
            case WAIT_OBJECT_0:
                CloseThread();
                assert(STATE_INIT == mState );
                assert(NULL       == mThread);

                lResult = true;
                break;

            case WAIT_TIMEOUT:
                if (aForce)
                {
                    mState = STATE_STOPPING;

                    BOOL lRetB = TerminateThread(mThread, __LINE__);

                    CloseThread();
                    assert(STATE_INIT == mState );
                    assert(NULL       == mThread);

                    if (!lRetB)
                    {
                        // NOT TESTED  KmsLib::ThreadBase.ErrorHandling
                        //             TerminateThread fail
                        throw new Exception(Exception::CODE_THREAD_ERROR, "TerminateThread( ,  ) failed", 0, __FILE__, __FUNCTION__, __LINE__, 0);
                    }
                }
                break;

            default:
                // NOT TESTED  KmsLib.ThreadBase.ErrorHandling
                //             WaitForSingleObject fail
                if (aForce)
                {
                    CloseThread();
                    assert(STATE_INIT == mState );
                    assert(NULL       == mThread);
                }

                throw new Exception(Exception::CODE_THREAD_ERROR, "WaitForSingleObject( ,  ) failed", 0, __FILE__, __FUNCTION__, __LINE__, 0);
            }
            break;

        default: assert(false);
        }
    
        return lResult;
    }

    // Internal
    /////////////////////////////////////////////////////////////////////////

    unsigned int ThreadBase::Run_Internal()
    {
        assert(STATE_START_REQUESTED == mState);

        mState = STATE_STARTING;

        unsigned int lResult;

        try
        {
            ApplyPriority();

            mState = STATE_RUNNING;

            lResult = Run();
        }
        catch (...)
        {
            lResult = __LINE__;
        }

        mState = STATE_STOPPING;

        return lResult;
    }

    // Protected
    /////////////////////////////////////////////////////////////////////////

    ThreadBase::ThreadBase()
        : mPriority(PRIORITY_NORMAL)
        , mState   (STATE_INIT     )
        , mThread  (NULL           )
        , mThreadId(              0)
    {
    }

    // Private
    /////////////////////////////////////////////////////////////////////////

    // Exception  Exception  CODE_THREAD_ERROR
    void ThreadBase::ApplyPriority()
    {
        assert(PRIORITY_UNKNOWN != mPriority);
        assert(PRIORITY_QTY     >  mPriority);
        assert(NULL             != mThread  );

        if (!SetThreadPriority(mThread, PRIORITIES[mPriority]))
        {
            // NOT TESTED  KmsLib.ThreadBase.ErrorHandling
            //             SetThreadPriority fail
            throw new Exception(Exception::CODE_THREAD_ERROR, "SetThreadPriority( ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, mPriority);
        }
    }

    void ThreadBase::CloseThread()
    {
        assert(NULL != mThread);

        BOOL lRetB = CloseHandle(mThread);
        assert(lRetB);

        mState  = STATE_INIT;
        mThread = NULL      ;
    }

}

// Static functions
/////////////////////////////////////////////////////////////////////////////

DWORD WINAPI Run(PVOID aParameter)
{
    assert(NULL != aParameter);

    KmsLib::ThreadBase * lThis = reinterpret_cast<KmsLib::ThreadBase *>(aParameter);

    return lThis->Run_Internal();
}
