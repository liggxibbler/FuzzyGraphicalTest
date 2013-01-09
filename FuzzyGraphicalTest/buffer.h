#ifndef _FUZZY_BUFFER_H_
#define _FUZZY_BUFFER_H_

namespace Fuzzy
{
	class Buffer
	{
	public:
		Buffer();
		Buffer(const Buffer&);
		~Buffer();

		float Read();
		void Max(float val);
		void Write(float val);
		void Clear();
	private:
		float m_value;
	};
}

#endif