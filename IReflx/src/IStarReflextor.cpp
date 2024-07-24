#include "IStarReflextor.h"

#include "SourceReader.h"
#include "UdpSender.h"

#include <thread>

#ifdef PERFCNTR
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <IReflxPerfCntr/IReflxCounter.h>
#endif

namespace ThetaStream
{
    class IStarReflextor::Impl
    {
    public:
        uint64_t _inCount{ 0 };
        uint64_t _outCount{ 0 };
        SourceReader* _sourceReader{};
        UdpSender* _destReader{};
        ThetaStream::CommandLineParser _cmdLine;
#ifdef PERFCNTR
        IReflxCounter* _counter{};
#endif
    };


    IStarReflextor::IStarReflextor()
    {
        _pimpl = std::make_unique<ThetaStream::IStarReflextor::Impl>();
    }

    IStarReflextor::IStarReflextor(const ThetaStream::CommandLineParser& cmdLine)
    {
        _pimpl = std::make_unique<ThetaStream::IStarReflextor::Impl>();
        _pimpl->_cmdLine = cmdLine;
    }

    IStarReflextor::~IStarReflextor()
    {
    }

    void IStarReflextor::init(const ThetaStream::CommandLineParser& cmdLine)
    {
        _pimpl->_cmdLine = cmdLine;
    }

    int IStarReflextor::run()
    {
        QueueType queue;

        SourceReader reader(_pimpl->_cmdLine.sourceIp(), _pimpl->_cmdLine.sourcePort(), queue, _pimpl->_cmdLine.sourceInterfaceAddress());
        UdpSender sender(_pimpl->_cmdLine.destinationIp(), _pimpl->_cmdLine.destinationPort(), queue, _pimpl->_cmdLine.ttl(), _pimpl->_cmdLine.destinationInterfaceAddress());
#ifdef PERFCNTR
        IReflxCounter perfCounter(reader, sender);
#endif

        _pimpl->_sourceReader = &reader;
        _pimpl->_destReader = &sender;
#ifdef PERFCNTR
        _pimpl->_counter = &perfCounter;
#endif

        std::thread listenThread{ &SourceReader::operator(), &reader };
        std::thread senderThread{ &UdpSender::operator(), &sender };
#ifdef PERFCNTR
        std::thread perfCounterThread{ &IReflxCounter::operator(), &perfCounter };
#endif

        listenThread.join();
        senderThread.join();
#ifdef PERFCNTR
        perfCounter.stop();
        perfCounterThread.join();
#endif
        return 0;
    }

    void IStarReflextor::stop()
    {
        _pimpl->_sourceReader->stop();
        _pimpl->_destReader->stop();

        _pimpl->_inCount = _pimpl->_sourceReader->count();
        _pimpl->_outCount = _pimpl->_destReader->count();
    }

    uint64_t IStarReflextor::inCount() const
    {
        return _pimpl->_inCount;
    }

    uint64_t IStarReflextor::outCount() const
    {
        return _pimpl->_outCount;
    }

}