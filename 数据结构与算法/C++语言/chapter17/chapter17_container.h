#pragma once
#ifndef chapter17_container_
#define chapter17_container_
// ���ڻ���װ������
struct container
{
    int id, weight; // ����Ļ�����������
    operator int() const { return weight; }
};
#endif // !chapter17_container_
