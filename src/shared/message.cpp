#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "message.hpp"

const char* message::data() const
{
	return data_;
}

char* message::data()
{
	return data_;
}

size_t message::length() const
{
	return header_length + body_length_;
}

const char* message::body() const
{
	return data_ + header_length;
}

char* message::body()
{
	return data_ + header_length;
}

size_t message::body_length() const
{
	return body_length_;
}

void message::body_length(size_t new_length)
{
	body_length_ = new_length;
	if (body_length_ > max_body_length)
		body_length_ = max_body_length;
}

bool message::decode_header()
{
	using namespace std; // For strncat and atoi.
	char header[header_length + 1] = "";
	strncat(header, data_, header_length);
	body_length_ = atoi(header);
	if (body_length_ > max_body_length)
	{
		body_length_ = 0;
		return false;
	}
	return true;
}

void message::encode_header()
{
	using namespace std; // For sprintf and memcpy.
	char header[header_length + 1] = "";
	sprintf(header, "%4ld", body_length_);
	memcpy(data_, header, header_length);
}
