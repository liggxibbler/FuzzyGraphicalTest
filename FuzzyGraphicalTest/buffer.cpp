#include "buffer.h"

using namespace Fuzzy;

Buffer::Buffer()
{
}

Buffer::Buffer(const Buffer& other)
{
}

Buffer::~Buffer()
{
}

void Buffer::Clear()
{
	m_value = 0;
}

float Buffer::Read()
{
	return m_value;
}

void Buffer::Write(float value)
{
	m_value = value;
}

void Buffer::Max(float value)
{
	m_value = value > m_value ? value : m_value ;
}