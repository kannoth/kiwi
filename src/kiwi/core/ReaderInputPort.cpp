// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "kiwi/core/Node.hpp"

#include "kiwi/core/Reader.hpp"
#include "kiwi/core/Writer.hpp"

#include "kiwi/core/ReaderOutputPort.hpp"
#include "kiwi/core/ReaderInputPort.hpp"


namespace kiwi{
namespace core{


// ----------------------------------------------------------- InputPort

ReaderInputPort::ReaderInputPort( Node* myNode )
:	_enabled(true)
	, _node(myNode)
{
	//nothing to do
}


/*
void 
ReaderInputPort::connect(ReaderOutputPort& outputPort, bool isMetaPort)
{
//ScopedBlockMacro(__sccop, "ReaderInputPort::connect" );
	if( !isEnabled() )
	{
		Debug::error() << "InputPort::connect() : input port disabled" << endl();
		return;
	}
	if( !outputPort.isEnabled() )
	{
		Debug::error() << "InputPort::connect() : output port disabled" << endl();
		return;
	}
	// if it is the subPort
	
		if(isCompatible(outputPort) )
		{
			if( isConnected() ) disconnect();
			_connectedNode = &outputPort;
			if( isMetaPort ) outputPort._connections.push_back(this);
			if( _subPort != 0 )	_subPort->connect(outputPort, false);

			_node->layoutChanged();
		}
		else
		{
			Debug::error() << "InputPort::connect() : uncompatible ports - connection failed" << endl();
			Debug::error() << outputPort.tags().str()
				<< " >> " << tags().str() << endl();
			return;
		}
	
}
*/

/*
void 
ReaderInputPort::disconnect()
{
//ScopedBlockMacro(scp_block,"InputPort::disconnect");
	if(_subPort != 0) _subPort->disconnect();
	if( !isConnected() ) return;

	ReaderOutputPort* temp = _connectedNode;
	_connectedNode = 0;
	// _connectedNode must be set to zero BEFORE calling disconnect
	// on the pointed object because it will try to call disconnect on
	// this from within the method (infinite loop).
	temp->disconnect(this);
}
*/

bool ReaderInputPort::connect(ReaderOutputPort& outputPort)
{
	ScopedBlockMacro( __scop, "ReaderInputPort::connect" )
	if( isEnabled() && outputPort.isEnabled() )
		if( isCompatible( outputPort.tags() ) )
			return PortConnector::connect( &outputPort );
	else return false;
}

bool ReaderInputPort::connect(ReaderOutputPort* outputPort)
{
	ScopedBlockMacro( __scop, "ReaderInputPort::connect" )
	if( (outputPort!=0) && isEnabled() && outputPort->isEnabled() )
		if( isCompatible( *outputPort ) )
			return PortConnector::connect( outputPort );
	else return false;
}


void 
ReaderInputPort::bind(ReaderInputPort& port)
{
//DEBUG_ONLY( Debug::print() << "input port rebinding" << endl(); )
	port._linkedInputPorts.add(&port);
	
}



portIndex_t 
ReaderInputPort::index() const 
{
	return _node->indexOf(*this);
}


Node* 
ReaderInputPort::node() const 
{
	return _node;
}



Tags ReaderInputPort::tags() const
{
	return node()->readerInputTags( index() ); // TODO (subport ?)
}

bool ReaderInputPort::isCompatible(ReaderOutputPort& output)	
{ 
	return ( tags().hasOneOf(output.tags()+Tags("any") ) );
}


bool ReaderInputPort::isCompatible(const kiwi::Tags& tag)	
{ 
	return ( tags().hasOneOf(tag + Tags("any") ) );
}

/*
bool 
ReaderInputPort::isConnected() const 
{ 
	return (_connectedNode != 0); 
}
*/

bool 
ReaderInputPort::isEnabled() const 
{
	return _enabled;
}


ReaderOutputPort* 
ReaderInputPort::connectedOutput() const 
{ 
	return PortConnector::connectedInstance(0);
}


kiwi::string 
ReaderInputPort::name() const
{
	return _node->readerInputName(_node->indexOf(*this));
}





// ----------------------------------------------------------- protected




void 
ReaderInputPort::setEnabled(bool status) 
{
	_enabled = status;
}



} //namespace
} //namespace
