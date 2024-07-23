#pragma once

#include "BaseIOInterface.h"

class UdpSender :
    public BaseIOInterface
{
public:
    typedef BoundedBuffer<UdpData, QSIZE> QueueType;
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

