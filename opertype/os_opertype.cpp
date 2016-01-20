// OperServ OperType (C) 2016 Peter "SaberUK" Powell

#include "module.h"

class OSOperTypeCommand : public Command
{
public:
	OSOperTypeCommand(Module* creator)
		: Command(creator, "operserv/opertype", 2, 2)
	{
		this->SetDesc("Sets the oper type of the specified user");
		this->SetSyntax("\037nick\037 \037oper type\037");
	}

	void Execute(CommandSource& source, const std::vector<Anope::string>& parameters) anope_override
	{
		// Ensure that the target user is online.
		User* target;
		if (!(target = User::Find(parameters[0], true)))
		{
			source.Reply(NICK_X_NOT_IN_USE, parameters[0].c_str());
			return;
		}

		// Broadcast the SVSOPER to the remote server.
		UplinkSocket::Message() << "SVSOPER " << target->GetUID() << " :" << parameters[1].replace_all_cs(" ", "_");
		source.Reply("\002%s's\002 oper type has been set to \002%s\002.", target->nick.c_str(), parameters[1].c_str());
	}

	bool OnHelp(CommandSource& source, const Anope::string&) anope_override
	{
		this->SendSyntax(source);
		source.Reply(" ");
		source.Reply("Sets the oper type of the specified user");
		return true;
	}
};

class OSOperType : public Module
{
private:
	OSOperTypeCommand command;

public:
	OSOperType(const Anope::string& moduleName, const Anope::string& creator)
		: Module(moduleName, creator, THIRD)
		, command(this)
	{
		if (IRCD->GetProtocolName().find("InspIRCd") == std::string::npos)
			throw ModuleException("This module only works with InspIRCd");
	}
};

MODULE_INIT(OSOperType)
