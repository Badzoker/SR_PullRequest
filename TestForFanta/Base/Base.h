#pragma once
//#include "Base.inl"
// _declspec : Ŭ���� ������ (� ����� �ϴ��� Ŭ������ ����ϴ� Ű����)

class _declspec(dllexport) CBase
{
protected:
	inline explicit CBase();
	inline virtual ~CBase();

public:
	inline unsigned long AddRef();
	inline unsigned long Release();

private:
	unsigned long m_dwRefCnt;

public:
	inline virtual void Free() = 0;

};

#include "Base.inl"