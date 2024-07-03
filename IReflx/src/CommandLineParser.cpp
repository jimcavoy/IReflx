#include <IReflx/CommandLineParser.h>

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const char* usage = "Usage: IReflxApp <OPTIONS>";
const char* opts = "  -s\tSource socket address; otherwise, stdin.\n \
 -d\tDestination socket address; otherwise, stdout.\n \
 -t\tTime to Live. (default: 16)\n \
 -i\tSpecifies the network interface IP address for the source stream.\n \
 -o\tSpecifies the network interface IP address for the destination stream.\n \
 -?\tPrint this message.";

namespace
{
    string getip(const char* ip)
    {
        string sip(ip);
        string::size_type pos = sip.find(":");
        string ret = sip.substr(0, pos);
        return ret;
    }

    int getport(const char* ip)
    {
        string sip(ip);
        string::size_type pos = sip.find(":");
        pos++;
        string port = sip.substr(pos, sip.size() - pos);
        int ret = atoi(port.c_str());
        return ret;
    }
}

namespace ThetaStream
{
    class CommandLineParser::Impl
    {
    public:
        Impl() {}
        ~Impl() {}
        Impl(const Impl& other)
            : sourcePort(other.sourcePort)
            , destinationPort(other.destinationPort)
            , ttl(other.ttl)
            , sourceIP(other.sourceIP)
            , destinationIP(other.destinationIP)
            , ifaceAddr(other.ifaceAddr)
            , ofaceAddr(other.ofaceAddr)
        {

        }


    public:
        int sourcePort{ 50000 };
        int destinationPort{ 50000 };
        int ttl{ 16 };
        std::string sourceIP{ "-" };
        std::string destinationIP{ "-" };
        std::string ifaceAddr;
        std::string ofaceAddr;
    };
}

ThetaStream::CommandLineParser::CommandLineParser()
{
    _pimpl = std::make_unique<ThetaStream::CommandLineParser::Impl>();
}

ThetaStream::CommandLineParser::~CommandLineParser()
{
}

ThetaStream::CommandLineParser::CommandLineParser(const CommandLineParser& other)
    :_pimpl(std::make_unique<ThetaStream::CommandLineParser::Impl>(*other._pimpl))
{

}

ThetaStream::CommandLineParser& ThetaStream::CommandLineParser::operator=(const ThetaStream::CommandLineParser& rhs)
{
    if (this != &rhs)
    {
        _pimpl.reset(new ThetaStream::CommandLineParser::Impl(*rhs._pimpl));
    }
    return *this;
}

ThetaStream::CommandLineParser::CommandLineParser(CommandLineParser&& src) noexcept
{
    *this = std::move(src);
}

ThetaStream::CommandLineParser& ThetaStream::CommandLineParser::operator=(CommandLineParser&& rhs) noexcept
{
    if (this != &rhs)
    {
        _pimpl = std::move(rhs._pimpl);
    }
    return *this;
}

void ThetaStream::CommandLineParser::parse(int argc, char** argv, const char* appname)
{
    string source{ "-" };
    string dest{ "-" };
    char c{};

    while (--argc > 0 && (*++argv)[0] == '-')
    {
        c = *++argv[0];
        switch (c)
        {
        case 's':
        {
            // Check for a space character between the option and value
            if (strlen(*argv + 1) == 0)
            {
                source = *++argv;
                --argc;
            }
            else // no space character between the option and value
            {
                source = *argv + 1;
            }
            break;
        }
        case 'd':
        {
            if (strlen(*argv + 1) == 0)
            {
                dest = *++argv;
                --argc;
            }
            else
            {
                dest = *argv + 1;
            }
            break;
        }
        case 'i':
        {
            if (strlen(*argv + 1) == 0)
            {
                _pimpl->ifaceAddr = *++argv;
                --argc;
            }
            else
            {
                _pimpl->ifaceAddr = *argv + 1;
            }
            break;
        }
        case 'o':
        {
            if (strlen(*argv + 1) == 0)
            {
                _pimpl->ofaceAddr = *++argv;
                --argc;
            }
            else
            {
                _pimpl->ofaceAddr = *argv + 1;
            }
            break;
        }
        case 't':
        {
            if (strlen(*argv + 1) == 0)
            {
                _pimpl->ttl = std::stoi(*++argv);
                --argc;
            }
            else
            {
                _pimpl->ttl = std::stoi(*argv + 1);
            }
            break;
        }
        case '?':
        {
            std::stringstream msg;
            msg << usage << endl;
            msg << endl << "Options: " << endl;
            msg << opts << endl;
            std::runtime_error exp(msg.str().c_str());
            throw exp;
        }
        default:
        {
            std::stringstream msg;
            msg << appname << ": illegal option " << c << endl;
            std::runtime_error exp(msg.str().c_str());
            throw exp;
        }
        }
    }

    if (source != "-")
    {
        _pimpl->sourceIP = getip(source.c_str());
        _pimpl->sourcePort = getport(source.c_str());
    }

    if (dest != "-")
    {
        _pimpl->destinationIP = getip(dest.c_str());
        _pimpl->destinationPort = getport(dest.c_str());
    }
}

const char* ThetaStream::CommandLineParser::sourceIp() const
{
    return _pimpl->sourceIP.c_str();
}

const char* ThetaStream::CommandLineParser::destinationIp() const
{
    return _pimpl->destinationIP.c_str();
}

const char* ThetaStream::CommandLineParser::sourceInterfaceAddress() const
{
    return _pimpl->ifaceAddr.c_str();
}

const char* ThetaStream::CommandLineParser::destinationInterfaceAddress() const
{
    return _pimpl->ofaceAddr.c_str();
}

int ThetaStream::CommandLineParser::sourcePort() const
{
    return _pimpl->sourcePort;
}

int ThetaStream::CommandLineParser::destinationPort() const
{
    return _pimpl->destinationPort;
}

int ThetaStream::CommandLineParser::ttl() const
{
    return _pimpl->ttl;
}
