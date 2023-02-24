#include "Bytestream.hpp"
#include "SwapEndian.hpp"
#include <fstream>
#include <stdexcept>

const std::size_t ALLOC_CHUNK_SIZE = 1024;

void BytestreamOut::updateBufferSize(std::size_t bytecount)
{
	if (pos + bytecount > data.size())
	{
		const auto ALLOC_SIZE = std::max(bytecount, ALLOC_CHUNK_SIZE);
		data.resize(data.size() + ALLOC_SIZE);
	}
}

BytestreamOut& BytestreamOut::operator<<(uint8_t num)
{
	updateBufferSize(sizeof(num));

	data[pos] = num;
	pos += sizeof(num);

	return *this;
}

BytestreamOut& BytestreamOut::operator<<(uint16_t num)
{
	updateBufferSize(sizeof(num));

	*((uint16_t*)(data.data() + pos)) = sanitize(num);
	pos += sizeof(num);

	return *this;
}

BytestreamOut& BytestreamOut::operator<<(uint32_t num)
{
	updateBufferSize(sizeof(num));

	*((uint32_t*)(data.data() + pos)) = sanitize(num);
	pos += sizeof(num);

	return *this;
}

BytestreamOut& BytestreamOut::operator<<(uint64_t num)
{
	updateBufferSize(sizeof(num));

	*((uint64_t*)(data.data() + pos)) = sanitize(num);
	pos += sizeof(num);

	return *this;
}

BytestreamOut& BytestreamOut::operator<<(const std::string& str)
{
	if (str.size() > 255)
	{
		throw std::runtime_error(
			"Trying to export std::string longer than 255 symbols. String: " + str);
	}

	*this << uint8_t(str.size());

	updateBufferSize(str.size());

	for (unsigned i = 0; i < str.size(); i++)
	{
		data[pos++] = str[i];
	}

	return *this;
}

BytestreamOut& BytestreamOut::operator<<(const std::vector<uint16_t>& vec)
{
	*this << uint32_t(vec.size());

	updateBufferSize(vec.size() * sizeof(uint16_t));

	uint16_t* vecdata = (uint16_t*)(data.data() + pos);

	for (unsigned i = 0; i < vec.size(); i++)
	{
		vecdata[i] = sanitize(vec[i]);
	}

	pos += vec.size() * sizeof(uint16_t);

	return *this;
}


void BytestreamOut::close()
{
	std::ofstream save(filename, std::ios::binary);

	save.write((char*)data.data(), pos);

	save.close();
	save.clear();
}