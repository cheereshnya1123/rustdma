//#include "pch.h"
//
//class Transform
//{
//public:
//    struct Symbol
//    {
//        char name[0x2C];
//        int index;
//        int level;
//    };
//
//    struct Matrix
//    {
//        Vector4 Position;
//        Vector4 Rotation;
//        Vector4 Scale;
//    };
//
//    typedef int Index;
//
//
//    struct MatrixData
//    {
//        BYTE Pad0[0x10];
//        DWORD cbMatrices;
//        DWORD cbHeap;
//        Matrix** pMatrices;
//        Index** pIndices;
//    };
//
//    struct StringPtr
//    {
//        char* pString;
//    };
//
//    struct Transform_internal;
//
//    struct Extra
//    {
//        BYTE Pad0[0x30];
//        Transform_internal** heap;
//        BYTE Pad1[0x28];
//        StringPtr* pString;
//    };
//
//    struct Transform_internal
//    {
//        BYTE Pad0[0x0C];
//        DWORD TypeFlag;
//        BYTE Pad1[0x18];
//        Transform* self;
//        Extra* pExtra;
//        MatrixData* mData;
//        DWORD EntryIndex;
//        BYTE Pad2[0x2C];
//        Transform_internal** pChildern;
//        BYTE Pad3[0x08];
//        DWORD cbChilden;
//        BYTE Pad4[0x0C];
//        Transform_internal* pParent;
//    };
//
//    MatrixData mData;
//    Matrix* pMatrix = nullptr;
//    Index* pIndex = nullptr;
//    Symbol* pSymbol = nullptr;
//    WORD cbSymbols = 0;
//    WORD cbIndices = 0;
//
//    void DumpSymbols(QWORD c_cached, int level = 0)
//    {
//        memset(pSymbol[cbSymbols].name, 0, 0x2C);
//
//        auto pStr = TargetProcess.Read<QWORD>(TargetProcess.Read<QWORD>(c_cached + 0x30) + 0x60);
//        if (pStr)
//        {
//            TargetProcess.Read(pStr, pSymbol[cbSymbols].name, 43);
//            pSymbol[cbSymbols].index = TargetProcess.Read<DWORD>(c_cached + 0x40);
//            if (cbIndices < pSymbol[cbSymbols].index)
//                cbIndices = pSymbol[cbSymbols].index;
//            pSymbol[cbSymbols].level = level;
//            cbSymbols++;
//        }
//        level++;
//
//        DWORD cbChildren = TargetProcess.Read<DWORD>(c_cached + 0x80);
//        if (!cbChildren)
//            return;
//        QWORD pChildren = TargetProcess.Read<QWORD>(c_cached + 0x70);
//        if (!pChildren)
//            return;
//
//        for (DWORD i = 0; i < cbChildren; i++)
//        {
//            QWORD cTrans = TargetProcess.Read<QWORD>(pChildren + i * 0x8);
//            DumpSymbols(cTrans, level);
//        }
//    }
//
//    QWORD get_root(QWORD pTrans)
//    {
//        QWORD pTransParent = TargetProcess.Read<QWORD>(pTrans + 0x90);
//        if (!pTransParent)
//            return pTrans;
//        return get_root(pTransParent);
//    }
//
//public:
//    QWORD Root;
//    QWORD Identity;
//    Transform(QWORD c_transform)
//    {
//        auto pCachedPtr = TargetProcess.Read<QWORD>(c_transform + 0x10);
//        auto internal = TargetProcess.Read<Transform_internal>(pCachedPtr);
//
//        mData = TargetProcess.Read<MatrixData>((QWORD)internal.mData);
//        Identity = (QWORD)mData.pMatrices;
//        pSymbol = (Symbol*)malloc(mData.cbMatrices * sizeof(Symbol));
//        pMatrix = (Matrix*)malloc(mData.cbMatrices * sizeof(Matrix));
//
//        Root = get_root(pCachedPtr);
//        DumpSymbols(Root);
//
//        pIndex = (Index*)malloc(cbIndices * sizeof(Index));
//
//        TargetProcess.Read((QWORD)mData.pMatrices, pMatrix, mData.cbMatrices * sizeof(Matrix));
//        TargetProcess.Read((QWORD)mData.pIndices, pIndex, cbIndices * sizeof(Index));
//    }
//
//    void update(VMMDLL_SCATTER_HANDLE scatter)
//    {
//        TargetProcess.AddScatterReadRequest(scatter, (QWORD)mData.pMatrices, pMatrix, mData.cbMatrices * sizeof(Matrix));
//    }
//
//    Vector3 get_position(const char* symbol, bool extended = false)
//    {
//        int index = -1;
//        for (int i = 0; i < cbSymbols; i++)
//            if (!memcmp(pSymbol[i].name, symbol, strlen(symbol) > 15 ? 15 : strlen(symbol)))
//            {
//                index = pSymbol[i].index;
//                break;
//            }
//        if (index != -1)
//        {
//            const __m128 Muti_YWZY = { -2.00, 2.000, -2.00, 0.000 };
//            const __m128 Muti_ZXWZ = { 2.000, -2.00, -2.00, 0.000 };
//            const __m128 Muti_WYZW = { -2.00, -2.00, 2.000, 0.000 };
//            auto Matrix_Base = _mm_load_ps((float*)&pMatrix[index].Position);
//
//            for (int i = pIndex[index] + extended; i >= 0; i = pIndex[i])
//            {
//                auto Matrix_Position = _mm_load_ps((float*)&pMatrix[i].Position);
//                auto Matrix_Rotation = _mm_load_ps((float*)&pMatrix[i].Rotation);
//                auto Matrix_Scale = _mm_mul_ps(_mm_load_ps((float*)&pMatrix[i].Scale), Matrix_Base);
//
//                auto Rotation_WYZW = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0xDB));
//                auto Rotation_YWZY = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0x71));
//                auto Rotation_ZXWZ = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0x8E));
//
//                auto Rotation_XXXX = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0x00));
//                auto Rotation_YYYY = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0x55));
//                auto Rotation_ZZZZ = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0xAA));
//
//                auto Scale_XXXX = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Scale), 0x00));
//                auto Scale_YYYY = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Scale), 0x55));
//                auto Scale_ZZZZ = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Scale), 0xAA));
//
//                Matrix_Base =
//                    _mm_add_ps(
//                        _mm_add_ps(
//                            _mm_add_ps(
//                                _mm_mul_ps(
//                                    _mm_sub_ps(
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_YYYY, Muti_YWZY), Rotation_YWZY),
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_ZZZZ, Muti_ZXWZ), Rotation_ZXWZ)),
//                                    Scale_XXXX), Matrix_Scale),
//                            _mm_add_ps(
//                                _mm_mul_ps(
//                                    _mm_sub_ps(
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_ZZZZ, Muti_WYZW), Rotation_WYZW),
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_XXXX, Muti_YWZY), Rotation_YWZY)),
//                                    Scale_YYYY),
//                                _mm_mul_ps(
//                                    _mm_sub_ps(
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_XXXX, Muti_ZXWZ), Rotation_ZXWZ),
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_YYYY, Muti_WYZW), Rotation_WYZW)),
//                                    Scale_ZZZZ))),
//                        Matrix_Position);
//            }
//            return Vector3(Matrix_Base.m128_f32[0], Matrix_Base.m128_f32[1], Matrix_Base.m128_f32[2]);
//        }
//        return Vector3(0, 0, 0);
//    }
//
//    Vector3 get_position(int index, bool extended = false)
//    {
//        if (index >= 0 && index < cbIndices)
//        {
//            const __m128 Muti_YWZY = { -2.00, 2.000, -2.00, 0.000 };
//            const __m128 Muti_ZXWZ = { 2.000, -2.00, -2.00, 0.000 };
//            const __m128 Muti_WYZW = { -2.00, -2.00, 2.000, 0.000 };
//            auto Matrix_Base = _mm_load_ps((float*)&pMatrix[index].Position);
//
//            for (int i = pIndex[index] + extended; i >= 0; i = pIndex[i])
//            {
//                auto Matrix_Position = _mm_load_ps((float*)&pMatrix[i].Position);
//                auto Matrix_Rotation = _mm_load_ps((float*)&pMatrix[i].Rotation);
//                auto Matrix_Scale = _mm_mul_ps(_mm_load_ps((float*)&pMatrix[i].Scale), Matrix_Base);
//
//                auto Rotation_WYZW = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0xDB));
//                auto Rotation_YWZY = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0x71));
//                auto Rotation_ZXWZ = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0x8E));
//
//                auto Rotation_XXXX = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0x00));
//                auto Rotation_YYYY = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0x55));
//                auto Rotation_ZZZZ = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Rotation), 0xAA));
//
//                auto Scale_XXXX = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Scale), 0x00));
//                auto Scale_YYYY = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Scale), 0x55));
//                auto Scale_ZZZZ = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(Matrix_Scale), 0xAA));
//
//                Matrix_Base =
//                    _mm_add_ps(
//                        _mm_add_ps(
//                            _mm_add_ps(
//                                _mm_mul_ps(
//                                    _mm_sub_ps(
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_YYYY, Muti_YWZY), Rotation_YWZY),
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_ZZZZ, Muti_ZXWZ), Rotation_ZXWZ)),
//                                    Scale_XXXX), Matrix_Scale),
//                            _mm_add_ps(
//                                _mm_mul_ps(
//                                    _mm_sub_ps(
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_ZZZZ, Muti_WYZW), Rotation_WYZW),
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_XXXX, Muti_YWZY), Rotation_YWZY)),
//                                    Scale_YYYY),
//                                _mm_mul_ps(
//                                    _mm_sub_ps(
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_XXXX, Muti_ZXWZ), Rotation_ZXWZ),
//                                        _mm_mul_ps(_mm_mul_ps(Rotation_YYYY, Muti_WYZW), Rotation_WYZW)),
//                                    Scale_ZZZZ))),
//                        Matrix_Position);
//            }
//            return Vector3(Matrix_Base.m128_f32[0], Matrix_Base.m128_f32[1], Matrix_Base.m128_f32[2]);
//        }
//        return Vector3(0, 0, 0);
//    }
//
//    void dbg_draw(const ViewMatrix& viewMatrix, ImDrawList* drawList)
//    {
//        for (int i = 0; i < cbSymbols; i++)
//        {
//            auto current_id = pSymbol[i].index;
//            auto point = WorldToScreen(get_position(current_id), viewMatrix);
//
//            if (point.x > 0.f && point.y > 0.f) // Ensure valid screen coordinates
//            {
//                drawList->AddCircleFilled(ImVec2(point.x, point.y), 5.0f, IM_COL32(0, 255, 0, 255)); // Green circle
//            }
//
//            if (pSymbol[current_id].index != (int)pIndex[current_id] + 1)
//            {
//                point = WorldToScreen(get_position(current_id, true), viewMatrix);
//                if (point.x > 0.f && point.y > 0.f)
//                {
//                    drawList->AddCircleFilled(ImVec2(point.x, point.y), 5.0f, IM_COL32(255, 0, 0, 255)); // Red circle
//                }
//            }
//        }
//    }
//
//
//
//    void dbg_print()
//    {
//        printf("Unity.Transform[%p]\n", Root);
//        printf("  Identity: %p\n", Identity);
//        printf("  Symbols: %i\n", cbSymbols);
//        printf("  Matrices: %i\n", mData.cbMatrices);
//        printf("  Indices: %i\n", cbIndices);
//        printf("  Heap: %i\n", mData.cbHeap);
//        if (cbIndices < mData.cbMatrices)
//            printf("     [INFO]: Detected the use of Extended Matrices\n");
//        printf("  Matrices:\n");
//
//        printf("  Extra:\n");
//        for (int i = 0; i < cbSymbols; i++)
//        {
//            auto point = get_position(pSymbol[i].name);
//            printf("    %s[%i] (%.2f, %.2f, %.2f)\n", pSymbol[i].name, pSymbol[i].index, point.x, point.y, point.z);
//            if (pSymbol[i].index)
//            {
//                printf("       Linked By: ");
//                printf("%s[%i]->", pSymbol[i].name, pSymbol[i].index);
//                for (int l = pIndex[pSymbol[i].index]; l >= 0; l = pIndex[l])
//                {
//                    bool found = false;
//                    for (int x = 0; x < cbSymbols; x++)
//                    {
//                        if (pSymbol[x].index == l)
//                        {
//                            if (l)
//                                printf("%s[%i]->", pSymbol[l].name, l);
//                            else
//                                printf("%s[%i]", pSymbol[l].name, l);
//                            found = true;
//                            break;
//                        }
//                    }
//                    if (!found)
//                    {
//                        if (l)
//                            printf("UNKNOWN[%i]->", l);
//                        else
//                            printf("UNKNOWN[%i]", l);
//                    }
//
//                }printf("\n");
//            }
//            else
//            {
//                printf("       No Links\n");
//            }
//        }
//    }
//};