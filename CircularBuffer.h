#ifndef _CIRCULARBUFFER_H_
#define _CIRCULARBUFFER_H_

#include <array>

template<class T, size_t TElemCount>
class circular_buffer
{
  public:
	explicit circular_buffer() = default;

	void put(T item) noexcept
	{
        
        //TODO later create different function
        if(buf_[head_-1] == item){
            return;
        }
        //TODO

		buf_[head_] = item;

		if(full_)
		{
			tail_ = (tail_ + 1) % TElemCount;
		}

		head_ = (head_ + 1) % TElemCount;

		full_ = head_ == tail_;
	}

	T get() const noexcept
	{
		if(empty())
		{
			return 0;
		}

		// Read data and advance the tail (we now have a free space)
		auto val = buf_[tail_];
        
        //CHANGE HERE
        buf_[tail_] = 0;

		full_ = false;
		tail_ = (tail_ + 1) % TElemCount;

		return val;
	}

	void reset() noexcept
	{
		head_ = tail_;
		full_ = false;
	}

	bool empty() const noexcept
	{
		return (!full_ && (head_ == tail_));
	}

	bool full() const noexcept
	{
		return full_;
	}

	size_t capacity() const noexcept
	{
		return TElemCount;
	}

	size_t size() const noexcept
	{
		size_t size = TElemCount;

		if(!full_)
		{
			if(head_ >= tail_)
			{
				size = head_ - tail_;
			}
			else
			{
				size = TElemCount + head_ - tail_;
			}
		}

		return size;
	}

  private:
	mutable std::array<T, TElemCount> buf_;
	mutable size_t head_ = 0;
	mutable size_t tail_ = 0;
	mutable bool full_ = 0;
};

#endif