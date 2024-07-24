#pragma once

#include "BaseIOInterface.h"
#include "QueueType.h"

class UdpSender :
    public BaseIOInterface
{
public:
    UdpSender(const char* ipaddr, uint32_t port, QueueType& queue, unsigned char ttl, const char* iface_addr);
    ~UdpSender();

    void operator()();

    void stop();

    uint64_t count() noexcept;

    uint64_t bytes() noexcept;

    uint32_t address() noexcept;

    uint32_t port() noexcept;

private:
    class Impl;
    std::unique_ptr<Impl> _pimpl;
};

