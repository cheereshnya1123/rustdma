#include "Pch.h"

// --------------------------------------------------------------------------------
// Decryption
// --------------------------------------------------------------------------------
bool checkBit(uint32_t Value, uint32_t BitPosition)
{
    return (Value & (1 << BitPosition)) != 0;
}

uint64_t decryptIl2cppHandle(int32_t ObjectHandleID)
{
    uint64_t rdi_1 = ((uint64_t)(ObjectHandleID >> 3));
    uint64_t rcx_1 = ((uint64_t)((ObjectHandleID & 7) - 1));
    uintptr_t ObjectArray = TargetProcess.Read<uintptr_t>((rcx_1 * 0x28) + (gameAssemblyBase + il2cppGCHandleBase + 0x8)) + (rdi_1 << 3);
    if (TargetProcess.Read<byte>((rcx_1 * 0x28) + (gameAssemblyBase + il2cppGCHandleBase + 0x14)) > 1)
    {
        return TargetProcess.Read<uintptr_t>(ObjectArray);
    }
    else
    {
        uint32_t eax = TargetProcess.Read<uint32_t>(ObjectArray);
        eax = ~eax;
        return eax;
    }
}

uintptr_t BaseNetworkable(uintptr_t Address)
{
    uint64_t v24;
    uint64_t* v4;
    int v5;
    unsigned int v6, v7;

    v4 = &v24;
    v5 = 2;
    v24 = TargetProcess.Read<uint64_t>(Address + 24);

    do
    {
        v7 = *(unsigned int*)v4;
        v4 = (uint64_t*)((char*)v4 + 4);
        v6 = (((v7 + 0x67EBA1FD) << 22) | ((unsigned int)(v7 + 0x67EBA1FD) >> 10)) + 0x6EEAA304;
        *((unsigned int*)v4 - 1) = (16 * v6) | (v6 >> 28);
        --v5;
    } while (v5);

    return decryptIl2cppHandle(v24);
}

uintptr_t Ulong(uintptr_t a1)
{
    uint64_t* v1;
    int v2;
    unsigned int v3, v4;
    uint64_t v7;

    v1 = &v7;
    v2 = 2;
    v7 = a1;

    do
    {
        v4 = *(unsigned int*)v1;
        v1 = (uint64_t*)((char*)v1 + 4);
        *((unsigned int*)v1 - 1) = ((v4 ^ 0x417CEB89u) << 9 | ((v4 ^ 0x417CEB89u) >> 23)) - 1922798068;
        --v2;
    } while (v2);

    return v7;
}

auto decrypt_inventory_pointer(std::uint64_t a1) -> std::uint64_t // inventory and eyes
{
    auto il2cpp_object = decryptIl2cppHandle((std::int32_t)Ulong(TargetProcess.Read<std::uint64_t>(a1 + 0x18)));
    return il2cpp_object;
}