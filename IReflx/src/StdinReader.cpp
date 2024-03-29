#include "StdinReader.h"

#ifdef _WIN32
#include <io.h>
#endif
#include <fcntl.h>


StdinReader::StdinReader(QueueType& queue)
	:_count(0)
	, _bytes(0)
	, _run(true)
	, _queue(queue)
{
#ifdef _WIN32
	_setmode(_fileno(stdin), _O_BINARY);
#endif
}

StdinReader::~StdinReader()
{
}

void StdinReader::stop() noexcept
{
	_run = false;
}

uint64_t StdinReader::count() noexcept
{
	return _count;
}

uint64_t StdinReader::bytes() noexcept
{
	const uint64_t ret = _bytes;
	_bytes = 0;
	return ret;
}

uint32_t StdinReader::address() noexcept
{
	return 0;
}

uint32_t StdinReader::port() noexcept
{
	return 0;
}

void StdinReader::operator()()
{
	uint8_t buffer[1468]{};
	while (_run)
	{
		size_t r = fread(buffer, 1, sizeof(buffer), stdin);
		if (r > 0)
		{
			_count++;
			_queue.Put(UdpData(buffer, r));
			_bytes += r;
		}
		else
		{
			_run = false;
		}
	}
}
