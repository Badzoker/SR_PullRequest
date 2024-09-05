#pragma once
//#include "Base.inl"
// _declspec : 클래스 지시자 (어떤 기능을 하는지 클래스를 명시하는 키워드)

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