#pragma once
#ifndef chapter17_container_
#define chapter17_container_
// 用于货箱装载问题
struct container
{
    int id, weight; // 货箱的货物类别和重量
    operator int() const { return weight; }
};
#endif // !chapter17_container_
