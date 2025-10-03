// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);


constexpr int Size = sizeof(TELEM)*8;
constexpr int my_log2(int n) {
    return (n <= 1) ? 0 : 1 + my_log2(n / 2);
}
constexpr int Shift_Bits = my_log2(Size);



TBitField::TBitField(int len)
{
    if (len < 0) throw -1;
    BitLen = len;
    MemLen = (len + Size - 1) >> Shift_Bits;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n >> Shift_Bits;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return TELEM(1) << (n & (Size - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0) throw - 1;
    if (n > BitLen) throw - 2;
    pMem[GetMemIndex(n)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0) throw - 1;
    if (n > BitLen) throw - 2;
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0) throw - 1;
    if (n > BitLen) throw - 2;
    return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) return *this;

    delete pMem;

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (this == &bf) return 1;
    if (BitLen != bf.BitLen) return 0;
    
    int l = 0;
    int r = MemLen - 1;
    while (l <= r)
    {
        if (pMem[l] != bf.pMem[l] && pMem[r] != bf.pMem[r])
            return 0;

        
        l++;
        r--;
    }
    return 1;
   
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (this == &bf) return 0;
    if (BitLen != bf.BitLen) return 1;

    int l = 0;
    int r = MemLen - 1;
    while (l <= r)
    {
        if (pMem[l] != bf.pMem[l] && pMem[r] != bf.pMem[r])
            return 1;


        l++;
        r--;
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int newBitLen = BitLen >= bf.BitLen ? BitLen : bf.BitLen;
    TBitField resBitField(newBitLen);
    TELEM n1, n2;
    for (int i = 0; i < resBitField.MemLen; i++)
    {
        n1 = i < MemLen ? pMem[i] : TELEM(0);
        n2 = i < bf.MemLen ? bf.pMem[i] : TELEM(0);
        resBitField.pMem[i] = n1 | n2;
    }
    return resBitField;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    /*int newBitLen = BitLen < bf.BitLen ? BitLen : bf.BitLen;
    TBitField resBitField(newBitLen);
    for (int i = 0; i < resBitField.MemLen; i++)
    {
        resBitField.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return resBitField;*/

    int newBitLen = BitLen >= bf.BitLen ? BitLen : bf.BitLen;
    TBitField resBitField(newBitLen);
    TELEM n1, n2;
    for (int i = 0; i < resBitField.MemLen; i++)
    {
        n1 = i < MemLen ? pMem[i] : TELEM(0);
        n2 = i < bf.MemLen ? bf.pMem[i] : TELEM(0);
        resBitField.pMem[i] = n1 & n2;
    }
    return resBitField;
}

TBitField TBitField::operator~(void) // отрицание
{
    int AllowedBits = ((TELEM(1) << BitLen) - 1);
    TBitField resBitField(BitLen);
    for (int i = 0; i < MemLen; i++)
    {
        resBitField.pMem[i] = ~pMem[i];
    }
    resBitField.pMem[MemLen - 1] &= AllowedBits;
    return resBitField;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int i;
    istr >> i;

    bf.SetBit(i);
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.MemLen; i++)
    {
        int size = Size; // колво бит
        for (size_t i = 0; i < size; i++)
        {
            if (bf.pMem[i] & (1 << i)) // проверка на существование
                std::cout << "1";
            else
                std::cout << "0";
        }
        std::cout << std::endl;
    }
    return ostr;
}
