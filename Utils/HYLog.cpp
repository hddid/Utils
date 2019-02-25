#include "../Utils/HYLog.h"

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace HY
{

	HYLog::HYLog()
	{
		//empty
	}

	HYLog::~HYLog()
	{
		mVerbosity = 0;
		if (mLog[0].is_open())
		{
			mLog[0].close();
		}

		if (mLog[1].is_open())
		{
			mLog[1].close();
		}
	}

	bool HYLog::Init(const std::string& logPath, int level)
	{
		if (logPath.empty())
			return false;

		mLogPath[0] = logPath + "_0.log";
		mLogPath[1] = logPath + "_1.log";
		mLog[0].open(mLogPath[0].c_str(), std::ofstream::out);
		if (!mLog[0].is_open())
		{
			return false;
		}


		mLog[1].open(mLogPath[1].c_str(), std::ofstream::out);
		if (!mLog[1].is_open())
		{
			mLog[0].close();
			return false;
		}
		mVerbosity = level;

		return true;
	}

	void HYLog::SetFileSize(unsigned int fLen)
	{
		if (fLen < 1)
			fLen = 1;

		mFileSize = fLen * 1024 * 1024;
	}

	bool HYLog::IsFileOverflow(void)
	{
		if (mEnable)
		{
			mEnable = false;
			int tmpIdx = 1 - mCurIndex;
			mLog[tmpIdx].close();
			std::remove(mLogPath[tmpIdx].c_str());
			mLog[tmpIdx].open(mLogPath[tmpIdx].c_str(), std::ofstream::out);
		}

		struct stat tFileProp;
		if (stat(mLogPath[mCurIndex].c_str(), &tFileProp))
		{
			cout << "stat file " << mLogPath[mCurIndex] << " error" << endl;
			cout << "error is: [" << errno << "," << strerror(errno) << "]" << endl;
			return false;
		}

		bool ret = (static_cast<uint64_t>(tFileProp.st_size)) >= mFileSize;
		if (ret)
		{
			mCurIndex = 1 - mCurIndex;
			mEnable = true;
		}

		return ret;
	}

}
