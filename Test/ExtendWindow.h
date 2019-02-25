#ifndef _EXTEND_WINDOW_H_
#define _EXTEND_WINDOW_H_

class ExtendWindow
{
private:
	int mX;
	int mY;
	int mWidth;
	int mHeight;
	int mHeightNotMinimized;
	cv::String mTitle;
	bool mMinimized;
	bool mMinimizable;

public:
	ExtendWindow(int x, int y, int width, int height, const cv::String& title, bool minimizable = true) :
		mX(x),
		mY(y),
		mWidth(width),
		mHeight(height),
		mHeightNotMinimized(height),
		mTitle(title),
		mMinimized(false),
		mMinimizable(minimizable) {
	}

	void begin(cv::Mat &frame)
	{
		bool mouseInsideTitleArea = cvui::mouse().inside(cv::Rect(mX, mY, mWidth, 20));
		mHeight = mMinimized ? 20 : mHeightNotMinimized;

		mX = std::max(0, mX);
		mY = std::max(0, mY);
		mX = std::min(frame.cols - mWidth, mX);
		mY = std::min(frame.rows - 20, mY);

		cvui::window(frame, mX, mY, mWidth, mHeight, mTitle);
		if (mMinimizable && cvui::button(frame, mX + mWidth - 20, mY + 1, 18, 18, mMinimized ? "+" : "-"))
		{
			mMinimized = !mMinimized;
		}
		cvui::beginRow(frame, mX + 10, mY + 30, mWidth - 20, mHeight - 20);
		cvui::beginColumn(mWidth - 10, mHeight - 20);
	}

	void end()
	{
		cvui::endColumn();
		cvui::endRow();
	}

	int width() const
	{
		return mWidth;
	}

	int height() const
	{
		return mHeight;
	}

	void setWidth(int w)
	{
		mWidth = w;
	}

	void setHeight(int h)
	{
		mHeight = h;
	}

	bool isMinimized()
	{
		return mMinimized;
	}
};

#endif // _EXTEND_WINDOW_H_