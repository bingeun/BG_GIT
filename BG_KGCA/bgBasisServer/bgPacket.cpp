#include "bgPacket.h"


void bgPacket::ReadData(void* buffer, int iSize)
{
	::CopyMemory(buffer, m_pstrReadPosition, iSize);
	m_pstrReadPosition += iSize;
}

void bgPacket::WriteData(void* buffer, int iSize)
{
	if (m_iReceivedSize >= PACKETBUFFERSIZE - 4)
	{
		// 오류
	}
	*m_PacketHeader.len += iSize;
	CopyMemory(m_pstrWritePosition, buffer, iSize);
	// 1차원 배열의 주소가 이동
	m_pstrWritePosition += iSize;
	// 실제 데이터의 바이트 용량
	m_iReceivedSize += iSize;
}

bgPacket& bgPacket::SetID(unsigned short ID)
{
	*m_PacketHeader.type = ID;
	return *this;
}

// 패킷을 생성할 때 sum = a.v + b.v + c.v + d.v + e.v;
bgPacket& bgPacket::operator << (int arg)
{
	WriteData(&arg, sizeof(int));
	return *this;
}

// 패킷에서 데이터를 추출할 때
bgPacket&  bgPacket::operator >> (int& arg)
{
	ReadData(&arg, sizeof(int));
	return *this;
}

bgPacket&     bgPacket::operator << (DWORD arg)
{
	WriteData(&arg, sizeof(DWORD));
	return *this;
}

bgPacket&     bgPacket::operator >> (DWORD& arg)
{
	ReadData(&arg, sizeof(DWORD));
	return *this;
}


bgPacket&     bgPacket::operator << (bool arg)
{
	WriteData(&arg, sizeof(bool));
	return *this;
}

bgPacket&     bgPacket::operator >> (bool& arg)
{
	ReadData(&arg, sizeof(bool));
	return *this;
}

bgPacket&     bgPacket::operator << (unsigned short arg)
{
	WriteData(&arg, sizeof(unsigned short));
	return *this;
}

bgPacket&     bgPacket::operator >> (unsigned short& arg)
{
	ReadData(&arg, sizeof(unsigned short));
	return *this;
}

bgPacket&     bgPacket::operator << (float arg)
{
	WriteData(&arg, sizeof(float));
	return *this;
}

bgPacket&     bgPacket::operator >> (float& arg)
{
	ReadData(&arg, sizeof(float));
	return *this;
}

bgPacket&     bgPacket::operator << (char* arg)
{
	int iLen = sizeof(char)*strlen(arg);
	WriteData(&arg, iLen);
	return *this;
}

bgPacket&     bgPacket::operator >> (char* arg)
{
	int iLen = sizeof(char)*strlen(this->m_pstrReadPosition);
	ReadData(&arg, sizeof(char)*iLen);
	return *this;
}

bgPacket&     bgPacket::operator << (bgPacket& arg)
{
	unsigned short type = arg.GetID();
	unsigned short size = arg.GetSize();

	WriteData(&type, sizeof(unsigned short));
	WriteData(&size, sizeof(unsigned short));
	WriteData(&arg.m_pstrWritePosition, size - 4);
	return *this;
}

bgPacket&     bgPacket::operator >> (bgPacket& arg)
{
	int type, size;
	char buffer[4096] = { 0, };
	ReadData(&type, sizeof(unsigned short));
	ReadData(&size, sizeof(unsigned short));
	ReadData(&buffer, size - 4);

	arg.SetID(type);
	arg.WriteData(buffer, size - 4);
	return *this;
}

void bgPacket::Clear()
{
	ZeroMemory(m_strPacketBuffer, PACKETBUFFERSIZE);

	m_PacketHeader.len = (WORD*)m_strPacketBuffer + 0;
	m_PacketHeader.type = (WORD*)m_strPacketBuffer + 2;

	m_pstrWritePosition = &m_strPacketBuffer[4];
	m_pstrReadPosition = &m_strPacketBuffer[4];

	m_iReceivedSize = 0;
	*m_PacketHeader.len = 4;
}

bgPacket::bgPacket(void)
{
	Clear();
	SetID(0);
}

bgPacket::bgPacket(unsigned short type)
{
	Clear();
	SetID(type);
}

bgPacket::~bgPacket(void)
{
}
