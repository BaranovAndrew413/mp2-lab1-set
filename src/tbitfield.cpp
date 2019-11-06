// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len=10)
{
	if (len < 0)
		throw len; 
		BitLen = len;
		MemLen = (BitLen / 32) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (BitLen > bf.BitLen) throw "non";
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n<0 || n>= BitLen) throw n;
	int p;
	p = n / 32;
	return p;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen) throw n;
	int p = n % 32;
	return 1 << p;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen) throw n;
	
		int b;
		b = GetMemIndex(n);
		TELEM mask = GetMemMask(n);
		pMem[b] = pMem[b] | mask;
	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen) throw n;
	int pos = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	mask = ~mask;
	pMem[pos] = mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen) throw n;
	
		int pos = GetMemIndex(n);
		TELEM mask = GetMemMask(n);
		int res = pMem[pos] & mask;
		return res;
	
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen) {
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	else {
		for (int i = 0; i < MemLen - 1; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 0;
			for (int i = (MemLen - 1) * 32; i < BitLen; i++)
				if (GetBit(i) != bf.GetBit(i)) return 0;
			return 1;
	} }
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
		return 0;
	else
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	
	int n;
	if (BitLen >= bf.BitLen) n = BitLen; else
		n = bf.BitLen;
	TBitField res(n);
	for (int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = pMem[i] | bf.pMem[i];
		
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int l;
	if (bf.BitLen > BitLen)
		l = bf.BitLen;
	else l = BitLen;
	TBitField res(l);
	for (int i = 0; i < bf.BitLen; i++)
		res.pMem[i] = bf.pMem[i];
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] &= pMem[i];
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField bf(BitLen);
	for (int i = 0; i < MemLen; i++) {
		bf.pMem[i] = ~pMem[i];
	}
	return bf;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	
	int i = 0;
	char c;
	do {
		istr >> c;
		if (c == '0') bf.ClrBit(i);
		if (c == '1') bf.SetBit(i);
		i++;
	} while (c == '0' || c == '1');
		return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		if (bf.GetBit(i) == 0)
			ostr << 0;
		else ostr << 1;
	return ostr;
}
