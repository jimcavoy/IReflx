#pragma once

#include <memory>

namespace ThetaStream
{
	class CommandLineParser
	{
	public:
		CommandLineParser();
		~CommandLineParser();
		CommandLineParser(const CommandLineParser& other);
		CommandLineParser& operator=(const CommandLineParser& rhs);
		CommandLineParser(CommandLineParser&& src) noexcept;
		CommandLineParser& operator=(CommandLineParser&& rhs) noexcept;

		void parse(int argc, char** argv, const char* appname);

		const char* sourceIp() const;
		const char* destinationIp() const;
		const char* sourceInterfaceAddress() const;
		const char* destinationInterfaceAddress() const;
		int sourcePort() const;
		int destinationPort() const;
		int ttl() const;

	private:
		class Impl;
		std::unique_ptr<Impl> _pimpl;
	};

}
