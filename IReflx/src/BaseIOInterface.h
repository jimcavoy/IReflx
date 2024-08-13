#pragma once

#include <cstdint>

class BaseIOInterface
{
public:
	BaseIOInterface(void);
	virtual ~BaseIOInterface(void);

	virtual void stop() = 0;

	virtual uint64_t count() = 0;

	virtual uint64_t bytes() = 0;

	virtual uint32_t address() = 0;

	virtual uint32_t port() = 0;

	virtual void operator () () = 0;
};

