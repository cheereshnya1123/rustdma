#include "Pch.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

//                                           CONSTRUCTS                                           //

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Config {
    struct ESP {
        inline static bool show = true;
        struct Player {
            inline static bool show = true;
            inline static bool sleepers = false;
            inline static bool names = false;
            inline static bool team = false;
            inline static bool boxes = true;
            inline static bool hide_team = false;
            inline static bool item = true;
            //struct Bones {
            //    inline static bool show = false;
            //    inline static bool boxes = false;
            //    inline static bool head = true;
            //    static constexpr const char* head_types[] = { "Circle", "Cross" };
            //    inline static int current_head_type = 0;
            //};
        };

        inline static bool barrels = false;
        inline static bool crates = false;
        inline static bool raid = false;
        inline static bool food = false;
        inline static bool scientists = true;
        inline static bool animals = true;
        inline static bool nodes = false;
        inline static bool wood = false;
        inline static bool stone = false;
        inline static bool metal = false;
        inline static bool sulfur = false;
        inline static bool collectables = false;
        inline static bool woodCollectable = false;
        inline static bool stoneCollectable = false;
        inline static bool metalCollectable = false;
        inline static bool sulfurCollectable = false;
        inline static bool hemp = false;
        inline static bool corpses = false;
        inline static bool distances = false;
        inline static float maxDistance = 400.0f;

        inline static bool unknown = false;
        inline static bool dropped = false;
    };

    struct Radar {
        inline static bool show = false;
        inline static bool players = false;
        inline static bool names = false;
        inline static bool sleepers = false;
        inline static bool team = false;
        inline static bool hideTeam = false;
        inline static bool barrels = false;
        inline static bool crates = false;
        inline static bool raid = false;
        inline static bool dropped = false;
        inline static bool corpses = false;
        inline static bool food = false;
        inline static bool scientists = false;
        inline static bool animals = false;
        inline static bool nodes = false;
        inline static bool wood = false;
        inline static bool stone = false;
        inline static bool metal = false;
        inline static bool sulfur = false;
        inline static bool collectables = false;
        inline static bool woodCollectable = false;
        inline static bool stoneCollectable = false;
        inline static bool metalCollectable = false;
        inline static bool sulfurCollectable = false;
        inline static bool hemp = false;
        inline static bool unknown = false;
        inline static bool distances = false;
        inline static float size = 0.2f;
        inline static float zoom = 1.0f;
    };

    struct Chams {
        struct Player {
            inline static bool show = false;
            inline static int material = Materials::Glow_Red;
        };

        struct Scientist {
            inline static bool show = false;
            inline static int material = Materials::Glow_Red;
        };
    };

    struct RCS {
        inline static float percentage = 100.0f;
    };

    struct Misc {
        inline static bool show = true;
        inline static int fps = 145;
        inline static bool crosshair = false;
        inline static float crosshairSize = 10.0f;
        inline static int opacity = 0;
    };
}

ImColor player_color(255, 0, 0, 255);
ImColor teammate_color(0, 255, 0, 255);
ImColor sleeper_color(192, 192, 192, 255);
ImColor head_color(0, 255, 0, 255);
ImColor scientist_color(0, 0, 255, 255);
ImColor raid_color(255, 215, 0, 255);
ImColor dropped_color(200, 200, 200, 255);
ImColor corpse_color(200, 200, 200, 255);
ImColor recycler_color(0, 200, 0, 255);
ImColor animal_color(255, 0, 255, 255);
ImColor stone_color(169, 169, 169, 255);
ImColor metal_color(150, 75, 0, 255);
ImColor sulfur_color(156, 195, 8, 255);
ImColor hemp_color(0, 102, 17, 255);
ImColor food_color(227, 11, 93, 255);
ImColor wood_color(255, 188, 134, 255);
ImColor barrel_color(112, 163, 204, 255);
ImColor crate_color(204, 154, 12, 255);
ImColor trap_color(255, 215, 0, 255);
ImColor unknown_color(255, 255, 255, 255);
ImColor radar_color(0, 0, 0, 255);
ImColor crosshair_color(255, 255, 255, 255);

enum LifeState {
    Alive,
    Dead
};

enum class EntityCategory {
    Player,
    Dynamic,
    Static
};

struct EntityInfo {
    std::string name;
    ImColor* color;
    bool* esp;
    bool* radar;
    EntityCategory category;
};

class BaseEntity {
public:
    uint64_t address = 0;
    uint64_t base_object = 0;
    uint64_t entity_object = 0;
    uint64_t entity_class = 0;
    uint64_t entity_transform = 0;
    uint64_t entity_visual_state = 0;
    uint64_t prefab_id;
    float distance;
    std::string dropped_name;
    Vector3 position;
    bool position_initialized = false;

    EntityInfo entity_info;
};

class BasePlayer : public BaseEntity {
public:
    uint32_t flags;
    uint32_t team;
    LifeState life_state;
    uint64_t model;
    uint64_t name_ptr;
    int name_length;
    std::wstring name;
    uint64_t skinned_multi_meshes;
    uint64_t renderer_lists;
    uint64_t skinned_list;

    bool is_dead = false;
    bool is_sleeping = false;
    bool is_wounded;

    uint64_t inventory_encrypted;
    uint64_t active_item_id;
    uint64_t current_active_item_id = 0;
    uint64_t inventory;
    uint64_t inventory_belt;
    uint64_t belt_contents_list;
    uint64_t belt_contents;
    std::vector<uint64_t> item_slots = std::vector<uint64_t>(6, 0);
    std::vector<uint64_t> item_ids = std::vector<uint64_t>(6, 0);
    uint64_t held_item_ptr;
    uintptr_t item_definition;
    uintptr_t item_display_name;
    uintptr_t item_display_name_english;
    uint64_t item_length;
    std::string held_item;

    //std::shared_ptr<Transform> transformPtr = nullptr;
};

static struct GameInfo {
    uintptr_t BaseNetworkable = 0;
    uintptr_t StaticBaseNet = 0;
    uintptr_t WrapperPtr = 0;
    uintptr_t Wrapper = 0;
    uintptr_t ParentStatic = 0;
    uintptr_t ParentClass = 0;
    uintptr_t ObjectDictionary = 0;
    uintptr_t EntityListBase = 0;
    uintptr_t Camera = 0;
    bool Error = false;
    int Errorcode = 0x0;

    GameInfo() = default;
};

struct dynamic_array {
    std::uint64_t base;
    std::uint64_t mem_id;
    std::uint64_t sz;
    std::uint64_t cap;
};

struct CachedRecoilData {
    float yaw_min;
    float yaw_max;
    float pitch_min;
    float pitch_max;
    bool usesNewRecoil;
};

enum class EntityType : uint64_t {
    PLAYER = 4108440852ULL,
    SCARECROW = 3473349223ULL,
    SCIENTISTNPC_ARENA = 3430609603ULL,
    SCIENTISTNPC_CARGO = 3623670799ULL,
    SCIENTISTNPC_CARGO_TURRET_ANY = 1639447304ULL,
    SCIENTISTNPC_CARGO_TURRET_LR300 = 881071619ULL,
    SCIENTISTNPC_CH47_GUNNER = 1017671955ULL,
    SCIENTISTNPC_EXCAVATOR = 4293908444ULL,
    SCIENTISTNPC_FULL_ANY = 1539172658ULL,
    SCIENTISTNPC_FULL_LR300 = 3763080634ULL,
    SCIENTISTNPC_FULL_MP5 = 3595426380ULL,
    SCIENTISTNPC_FULL_PISTOL = 712785714ULL,
    SCIENTISTNPC_FULL_SHOTGUN = 1410044857ULL,
    SCIENTISTNPC_HEAVY = 1536035819ULL,
    SCIENTISTNPC_JUNKPILE_PISTOL = 2066159302ULL,
    SCIENTISTNPC_OILRIG = 548379897ULL,
    SCIENTISTNPC_PATROL = 4272904018ULL,
    SCIENTISTNPC_PEACEKEEPER = 2390854225ULL,
    SCIENTISTNPC_ROAM_NVG_VARIANT = 4134517186ULL,
    SCIENTISTNPC_ROAM = 4199494415ULL,
    SCIENTISTNPC_ROAMTETHERED = 529928930ULL,
    NPC_TUNNELDWELLER = 732025282ULL,
    NPC_BANDIT_GUARD = 412745708ULL,
    NPC_UNDERWATERDWELLER = 1605597847ULL,
    WORKBENCH1 = 2561955800ULL,
    WORKBENCH2 = 601265145ULL,
    WORKBENCH3 = 2764275075ULL,
    TOOLCUPBOARD = 2476970476ULL,
    DROPPEDITEM1 = 545786656ULL,
    DROPPEDITEM2 = 3255145925ULL,
    BACKPACK = 1519640547ULL,
    CORPSE1 = 2400390439ULL,
    CORPSE2 = 3842948583ULL,
    CORPSE3 = 1236143239ULL,
    CORPSE4 = 2604534927ULL,
    CORPSE5 = 391715894ULL,
    LARGE_WOODEN_BOX = 2206646561ULL,
    SMALL_WOODEN_BOX = 1560881570ULL,
    HORIZONTAL_WOODEN_BARREL = 2261122309ULL,
    VERTICAL_WOODEN_BARREL = 1502013593ULL,
    COFFIN = 573676040ULL,
    RECYCLER = 1729604075ULL,
    RHIB = 2226588638ULL,
    ROWBOAT = 1283317166ULL,
    TUGBOAT = 268742921ULL,
    HORSE = 2626468473ULL,
    MINI = 2278499844ULL,
    SCRAP = 3484163637ULL,
    AIRBALLOON = 3111236903ULL,
    SUBMARINESOLO = 3623991100ULL,
    SUBMARINEDUO = 903349679ULL,
    BRADLEYAPC = 1456850188ULL,
    PATROLHELI = 3029415845ULL,
    CHINOOK = 1514383717ULL,
    WOOD = 2891219449ULL,
    METAL = 3774647716ULL,
    METAL2 = 3345228353ULL,
    METAL3 = 4225479497ULL,
    METAL4 = 3327726152ULL,
    SULFUR = 3058967796ULL,
    SULFUR2 = 152562243ULL,
    SULFUR3 = 2204178116ULL,
    SULFUR4 = 1227527004ULL,
    STONE = 4124824587ULL,
    STONE2 = 960501790ULL,
    STONE3 = 723721358ULL,
    STONE4 = 266547145ULL,
    BEAR = 1799741974ULL,
    POLARBEAR = 749308997ULL,
    BOAR = 502341109ULL,
    CHICKEN = 152398164ULL,
    STAG = 1378621008ULL,
    WOLF = 2288788453ULL,
    ZOMBIE = 2805320019ULL,
    HEMP = 3006540952ULL,
    MUSHROOM1 = 2697239269ULL,
    MUSHROOM2 = 178882626ULL,
    PUMPKIN = 2251957318ULL,
    CORN = 3019211920ULL,
    BERRY_WHITE = 1989241797ULL,
    BERRY_BLACK = 3408978181ULL,
    BERRY_BLUE = 2764599810ULL,
    BERRY_YELLOW = 3056106441ULL,
    BERRY_RED = 1378329388ULL,
    BERRY_GREEN = 3306182606ULL,
    POTATO = 726972295ULL,
    COLLECTSULFUR = 2972237931ULL,
    COLLECTSTONE = 2422310333ULL,
    COLLECTWOOD = 2107058515ULL,
    COLLECTMETAL = 4060169083ULL,
    BARREL1 = 966676416ULL,
    BARREL2 = 555882409ULL,
    BARREL_1 = 3364121927ULL,
    BARREL_2 = 3269883781ULL,
    BARREL_OIL = 3438187947ULL,
    CRATE_BASIC = 1603759333ULL,
    CRATE_ELITE = 3286607235ULL,
    CRATE_MINE = 1071933290ULL,
    CRATE_NORMAL = 2857304752ULL,
    CRATE_NORMAL2 = 1546200557ULL,
    CRATE_NORMAL_FOOD = 2066926276ULL,
    CRATE_NORMAL_MEDICAL = 1791916628ULL,
    CRATE_TOOLS = 1892026534ULL,
    CRATE_UNDERWATER_ADVANCED = 2803512399ULL,
    CRATE_UNDERWATER_BASIC = 3852690109ULL,
    CRATE_BRADLEY = 1737870479ULL,
    CRATE_HELI = 1314849795ULL,
    CRATE_FOOD = 2896170989ULL,
    AIRDROP = 3632568684ULL,
    AUTOTURRET = 3312510084ULL,
    FLAMETURRET = 4075317686ULL,
    GUNTRAP = 1348746224ULL,
    SAMSTATIC = 1102446446344ULL,
    SAMDEPLOYED = 1101571403615ULL,
    LANDDMINE = 1463807579ULL,
    BEARTRAP = 922529517ULL
};

////////////////////////////////////////////////////////////////////////////////////////////////////

//                                          DECLARATIONS                                          //

////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int screenWidth;
unsigned int halfScreenWidth;
unsigned int screenHeight;
unsigned int halfScreenHeight;

std::atomic<bool> isClearingCache = false;

int reads;
int scatterReads;

std::atomic<int> readCounter(0);
std::atomic<int> scatterReadCounter(0);

uint16_t entityDictionarySize;

std::unordered_map<uint64_t, BasePlayer> playerDictionary;
std::unordered_map<uint64_t, BaseEntity> dynamicDictionary;
std::unordered_map<uint64_t, BaseEntity> staticDictionary;

BasePlayer local_player;
std::vector<BasePlayer> g_PlayerList;
std::vector<BaseEntity> g_DynamicList;
std::vector<BaseEntity> g_StaticList;

std::mutex g_dataMutex;

ViewMatrix currentViewMatrix;
uint64_t gameAssemblyBase;

static GameInfo globalCache;

static CachedRecoilData lastAppliedRecoil;
std::unordered_map<std::string, CachedRecoilData> recoilCache;

void ResetCache() {
    isClearingCache.store(true);

    {
        std::lock_guard<std::mutex> lock(g_dataMutex);
        playerDictionary.clear();
        dynamicDictionary.clear();
        staticDictionary.clear();

        local_player = BasePlayer();
        g_PlayerList.clear();
        g_DynamicList.clear();
        g_StaticList.clear();
    }

    isClearingCache.store(false);
}

void IncrementReadCounter() {
    readCounter.fetch_add(1, std::memory_order_relaxed);
}

void IncrementScatterReadCounter() {
    scatterReadCounter.fetch_add(1, std::memory_order_relaxed);
}

void LogReadsPerSecond() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        reads = readCounter.exchange(0, std::memory_order_relaxed);
        scatterReads = scatterReadCounter.exchange(0, std::memory_order_relaxed);
    }
}

static GameInfo StartCache()
{
    if (!gameAssemblyBase) {
        std::cerr << "[Error] gameAssemblyBase is null!" << std::endl;
        return globalCache;
    }

    globalCache.BaseNetworkable = TargetProcess.Read<uintptr_t>(gameAssemblyBase + BaseNetworkableOffset);
    if (!globalCache.BaseNetworkable) {
        std::cerr << "[Error] Failed to read BaseNetworkable!" << std::endl;
        return globalCache;
    }

    globalCache.StaticBaseNet = TargetProcess.Read<uint64_t>(globalCache.BaseNetworkable + staticBaseNetOffset);
    if (!globalCache.StaticBaseNet) {
        std::cerr << "[Error] Failed to read StaticBaseNet!" << std::endl;
        return globalCache;
    }

    globalCache.WrapperPtr = TargetProcess.Read<uint64_t>(globalCache.StaticBaseNet + wrapperPtrOffset);
    if (!globalCache.WrapperPtr) {
        std::cerr << "[Error] Failed to read WrapperPtr!" << std::endl;
        return globalCache;
    }

    globalCache.Wrapper = BaseNetworkable(globalCache.WrapperPtr);
    if (!globalCache.Wrapper) {
        std::cerr << "[Error] Failed to decrypt Wrapper!" << std::endl;
        return globalCache;
    }

    globalCache.ParentStatic = TargetProcess.Read<uint64_t>(globalCache.Wrapper + parentStaticOffset);
    if (!globalCache.ParentStatic) {
        std::cerr << "[Error] Failed to read ParentStatic!" << std::endl;
        return globalCache;
    }

    globalCache.ParentClass = BaseNetworkable(globalCache.ParentStatic);
    if (!globalCache.ParentClass) {
        std::cerr << "[Error] Failed to decrypt ParentClass!" << std::endl;
        return globalCache;
    }

    globalCache.ObjectDictionary = TargetProcess.Read<uint64_t>(globalCache.ParentClass + objectDictionaryOffset);
    if (!globalCache.ObjectDictionary) {
        std::cerr << "[Error] Failed to read ObjectDictionary!" << std::endl;
        return globalCache;
    }

    globalCache.EntityListBase = TargetProcess.Read<uint64_t>(globalCache.ObjectDictionary + entityListBaseOffset);
    if (!globalCache.EntityListBase) {
        std::cerr << "[Error] Failed to read EntityListBase!" << std::endl;
        return globalCache;
    }

    globalCache.Camera = cameraSetup(gameAssemblyBase);

    return globalCache;
}

bool isValidPtr(uint64_t address) {
    return (address != 0)
        && (address > 0x10000)
        && (address < 0x7FFFFFFEFFFF);
}

static std::string WStringToUTF8(const std::wstring& wide) {
    if (wide.empty())
        return {};
    int requiredSize = WideCharToMultiByte(
        CP_UTF8, 0,
        wide.data(), (int)wide.size(),
        nullptr, 0, nullptr, nullptr
    );
    if (requiredSize <= 0)
        return {};
    std::string utf8Str(requiredSize, '\0');
    WideCharToMultiByte(
        CP_UTF8, 0,
        wide.data(), (int)wide.size(),
        &utf8Str[0], requiredSize,
        nullptr, nullptr
    );
    return utf8Str;
}

static std::wstring ReadRustWString(uint64_t address) {
    if (!isValidPtr(address))
        return {};
    int length = TargetProcess.Read<int>(address + 0x10);
    if (length <= 0 || length > 300)
        return {};
    std::vector<wchar_t> buffer(length + 1, L'\0');
    TargetProcess.Read(address + 0x14, buffer.data(), length * sizeof(wchar_t));

    return std::wstring(buffer.data());
}

void ApplyChamsToPlayers(VMMDLL_SCATTER_HANDLE read, VMMDLL_SCATTER_HANDLE write, const std::vector<uint64_t>& players, const std::vector<uint64_t> rendererLists, const std::vector<uint64_t> skinnedLists, uint32_t material)
{
    std::vector<int> materialsCounts(players.size());
    for (size_t i = 0; i < players.size(); i++) {
        if (rendererLists[i]) {
            TargetProcess.AddScatterReadRequest(read, rendererLists[i] + 0x18, &materialsCounts[i], sizeof(int));
        }
    }
    TargetProcess.ExecuteReadScatter(read);

    std::vector<std::vector<uint64_t>> renderEntries(players.size());
    for (size_t playerIdx = 0; playerIdx < players.size(); playerIdx++) {
        if (!skinnedLists[playerIdx] || materialsCounts[playerIdx] <= 0) continue;
        renderEntries[playerIdx].resize(materialsCounts[playerIdx]);
        for (int idx = 0; idx < materialsCounts[playerIdx]; idx++) {
            TargetProcess.AddScatterReadRequest(read, skinnedLists[playerIdx] + 0x20 + (idx * 0x8), &renderEntries[playerIdx][idx], sizeof(uint64_t));
        }
    }
    TargetProcess.ExecuteReadScatter(read);

    std::vector<std::vector<uint64_t>> unityObjects(players.size());
    for (size_t playerIdx = 0; playerIdx < players.size(); playerIdx++) {
        if (renderEntries[playerIdx].empty()) continue;
        unityObjects[playerIdx].resize(renderEntries[playerIdx].size());
        for (size_t idx = 0; idx < renderEntries[playerIdx].size(); idx++) {
            if (renderEntries[playerIdx][idx]) {
                TargetProcess.AddScatterReadRequest(read, renderEntries[playerIdx][idx] + 0x10, &unityObjects[playerIdx][idx], sizeof(uint64_t));
            }
        }
    }
    TargetProcess.ExecuteReadScatter(read);

    std::vector<std::vector<dynamic_array>> matLists(players.size());
    for (size_t playerIdx = 0; playerIdx < players.size(); playerIdx++) {
        if (unityObjects[playerIdx].empty()) continue;
        matLists[playerIdx].resize(unityObjects[playerIdx].size());
        for (size_t idx = 0; idx < unityObjects[playerIdx].size(); idx++) {
            if (unityObjects[playerIdx][idx]) {
                TargetProcess.AddScatterReadRequest(read, unityObjects[playerIdx][idx] + 0x148, &matLists[playerIdx][idx], sizeof(dynamic_array));
            }
        }
    }
    TargetProcess.ExecuteReadScatter(read);

    std::unordered_set<uint64_t> uniqueVirtualAddrs;
    for (size_t playerIdx = 0; playerIdx < players.size(); playerIdx++) {
        if (matLists[playerIdx].empty()) continue;
        for (const auto& matList : matLists[playerIdx]) {
            if (!matList.base || matList.sz < 1 || matList.sz > 8) continue;
            for (uint32_t matIdx = 0; matIdx < matList.sz; matIdx++) {
                uniqueVirtualAddrs.insert(matList.base + (matIdx * 0x4));
            }
        }
    }

    std::vector<uint64_t> validPhysicalAddrs;
    validPhysicalAddrs.reserve(uniqueVirtualAddrs.size());

    for (const auto& va : uniqueVirtualAddrs) {
        uint64_t pa;
        if (TargetProcess.VirtToPhys(va, pa)) {
            validPhysicalAddrs.push_back(pa);
        }
    }

    std::sort(validPhysicalAddrs.begin(), validPhysicalAddrs.end());
    auto last = std::unique(validPhysicalAddrs.begin(), validPhysicalAddrs.end());
    validPhysicalAddrs.erase(last, validPhysicalAddrs.end());

    for (const auto& pa : validPhysicalAddrs) {
        TargetProcess.AddScatterWriteRequest(write, pa, material);
    }

    TargetProcess.ExecuteWriteScatter(write, -1);
}

uint64_t GetActiveViewmodel() {
    uint64_t BaseViewModel = TargetProcess.Read<uint64_t>(gameAssemblyBase + BaseViewModelOffset);
    if (!BaseViewModel)
    {
        std::cout << "[ERROR] Failed to read BaseViewModel." << std::endl;
        return 0;
    }

    uint64_t BaseViewModelStatic = TargetProcess.Read<uint64_t>(BaseViewModel + 0xB8);
    if (!BaseViewModelStatic)
    {
        std::cout << "[ERROR] Failed to read BaseViewModelStatic." << std::endl;
        return 0;
    }

    uint64_t ViewModelList = TargetProcess.Read<uint64_t>(BaseViewModelStatic + ViewModelListOffset);
    if (!ViewModelList)
    {
        std::cout << "[ERROR] Failed to read ViewModelList." << std::endl;
        return 0;
    }

    uint64_t ListContent = TargetProcess.Read<uint64_t>(ViewModelList + 0x10); //Dict/List stuff (dont think it changes)
    if (!ListContent)
    {
        std::cout << "[ERROR] Failed to read ListContent." << std::endl;
        return 0;
    }

    uint64_t FirstEntry = TargetProcess.Read<uint64_t>(ListContent + 0x20);
    if (!FirstEntry)
    {
        std::cout << "[ERROR] Failed to read FirstEntry." << std::endl;
        return 0;
    }

    return FirstEntry;
}

uintptr_t GetRecoilProperties() {

    uint64_t AnimationEvents = TargetProcess.Read<uint64_t>(GetActiveViewmodel() + AnimationEventsOffset);
    if (!AnimationEvents)
    {
        std::cout << "[ERROR] Failed to read AnimationEvents." << std::endl;
        return 0;
    }

    uint64_t heldEntity = TargetProcess.Read<uint64_t>(AnimationEvents + heldEntityOffset);
    if (!heldEntity)
    {
        std::cout << "[ERROR] Failed to read heldEntity." << std::endl;
        return 0;
    }

    uint64_t recoilProperties = TargetProcess.Read<uint64_t>(heldEntity + RecoilPropertiesOffset);
    if (!recoilProperties)
    {
        std::cout << "[ERROR] Failed to read RecoilProperties." << std::endl;
        return 0;
    }

    return recoilProperties;
}

float ApplyRecoilScaling(float original) {
    if (Config::RCS::percentage <= 0.0f) return 0.0f;
    if (Config::RCS::percentage >= 100.0f) return original;

    float scaledValue = original * (Config::RCS::percentage / 100.0f);

    if (Config::RCS::percentage > 0.0f && Config::RCS::percentage < 100.0f) {
        float variationRange = 0.1f * scaledValue;

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-variationRange, variationRange);

        scaledValue += dis(gen);
    }

    return scaledValue;
}

void SaveRecoilCache(const std::string& filename = "recoil_cache.json") {
    nlohmann::json jsonCache;
    for (const auto& pair : recoilCache) {
        jsonCache[pair.first] = {
            {"yaw_min", pair.second.yaw_min},
            {"yaw_max", pair.second.yaw_max},
            {"pitch_min", pair.second.pitch_min},
            {"pitch_max", pair.second.pitch_max},
            {"usesNewRecoil", pair.second.usesNewRecoil},
        };
    }

    std::ofstream file(filename);
    file << jsonCache.dump(4);
    file.close();

    std::cout << "[INFO] Recoil cache saved." << std::endl;
}

void LoadRecoilCache(const std::string& filename = "recoil_cache.json") {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "[INFO] No recoil cache file found." << std::endl;
        return;
    }

    nlohmann::json jsonCache;
    file >> jsonCache;
    file.close();

    for (const auto& item : jsonCache.items()) {
        CachedRecoilData data;
        data.yaw_min = item.value().value("yaw_min", 0.f);
        data.yaw_max = item.value().value("yaw_max", 0.f);
        data.pitch_min = item.value().value("pitch_min", 0.f);
        data.pitch_max = item.value().value("pitch_max", 0.f);
        data.usesNewRecoil = item.value().value("usesNewRecoil", false);

        recoilCache[item.key()] = data;
    }

    std::cout << "[INFO] Recoil cache loaded." << std::endl;
}

void RandomizeRecoil() {
    if (recoilCache.find(local_player.held_item) == recoilCache.end()) {
        return;
    }

    CachedRecoilData& cachedData = recoilCache[local_player.held_item];

    uint64_t recoilPropAddr = GetRecoilProperties();
    if (!recoilPropAddr) return;

    uint64_t newRecoilOverride = TargetProcess.Read<uint64_t>(recoilPropAddr + 0x80);
    uint64_t active_recoil_address = newRecoilOverride ? newRecoilOverride : recoilPropAddr;

    if (!active_recoil_address) return;

    float yaw_min_scaled = ApplyRecoilScaling(cachedData.yaw_min);
    float yaw_max_scaled = ApplyRecoilScaling(cachedData.yaw_max);
    float pitch_min_scaled = ApplyRecoilScaling(cachedData.pitch_min);
    float pitch_max_scaled = ApplyRecoilScaling(cachedData.pitch_max);

    uint64_t physAddress;

    if (TargetProcess.VirtToPhys(active_recoil_address + 0x18   , physAddress))
        TargetProcess.Write<float>(physAddress, yaw_min_scaled);

    if (TargetProcess.VirtToPhys(active_recoil_address + 0x1C, physAddress))
        TargetProcess.Write<float>(physAddress, yaw_max_scaled);

    if (TargetProcess.VirtToPhys(active_recoil_address + 0x20, physAddress))
        TargetProcess.Write<float>(physAddress, pitch_min_scaled);

    if (TargetProcess.VirtToPhys(active_recoil_address + 0x24, physAddress))
        TargetProcess.Write<float>(physAddress, pitch_max_scaled);

    lastAppliedRecoil.yaw_min = yaw_min_scaled;
    lastAppliedRecoil.yaw_max = yaw_max_scaled;
    lastAppliedRecoil.pitch_min = pitch_min_scaled;
    lastAppliedRecoil.pitch_max = pitch_max_scaled;
}

void ToggleSway()
{
    uintptr_t Viewmodel = GetActiveViewmodel();
    if (!Viewmodel) return;

    auto Bob = TargetProcess.Read<uintptr_t>(Viewmodel + 0xD0);
    auto Sway = TargetProcess.Read<uintptr_t>(Viewmodel + 0xD8);
    auto Lower = TargetProcess.Read<uintptr_t>(Viewmodel + 0x78);

    uint64_t physAddress;

    TargetProcess.VirtToPhys(Bob + 0x2C, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Bob + 0x28, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Bob + 0x24, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Bob + 0x20, physAddress);
    TargetProcess.Write<float>(physAddress, 0);

    TargetProcess.VirtToPhys(Sway + 0x24, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Sway + 0x20, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Sway + 0x30, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Sway + 0x2C, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Sway + 0x28, physAddress);
    TargetProcess.Write<float>(physAddress, 0);

    TargetProcess.VirtToPhys(Lower + 0x20, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Lower + 0x21, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Lower + 0x22, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
    TargetProcess.VirtToPhys(Lower + 0x28, physAddress);
    TargetProcess.Write<float>(physAddress, 0);
}

static ImVec2 getPlayerLookDirection(const ViewMatrix& matrix) {
    float forwardX = matrix.matrix[0][2];
    float forwardY = -matrix.matrix[2][2];
    float length = std::sqrt(forwardX * forwardX + forwardY * forwardY);

    if (length != 0.0f)
    {
        forwardX /= length;
        forwardY /= length;
    }
    return ImVec2(forwardX, forwardY);
}

EntityInfo getEntityInfo(uint64_t prefab_id) {
    switch (prefab_id) {
    case static_cast<uint64_t>(EntityType::PLAYER):
        return { "Player", &player_color, &Config::ESP::Player::show, &Config::Radar::players, EntityCategory::Player };
    case static_cast<uint64_t>(EntityType::SCARECROW):
        return { "Scarecrow", &scientist_color, &Config::ESP::scientists, &Config::Radar::scientists, EntityCategory::Player };
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_ARENA):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_CARGO):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_CARGO_TURRET_ANY):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_CARGO_TURRET_LR300):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_CH47_GUNNER):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_EXCAVATOR):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_FULL_ANY):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_FULL_LR300):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_FULL_MP5):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_FULL_PISTOL):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_FULL_SHOTGUN):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_HEAVY):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_JUNKPILE_PISTOL):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_OILRIG):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_PATROL):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_PEACEKEEPER):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_ROAM_NVG_VARIANT):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_ROAM):
    case static_cast<uint64_t>(EntityType::SCIENTISTNPC_ROAMTETHERED):
    case static_cast<uint64_t>(EntityType::NPC_TUNNELDWELLER):
    case static_cast<uint64_t>(EntityType::NPC_BANDIT_GUARD):
    case static_cast<uint64_t>(EntityType::NPC_UNDERWATERDWELLER):
        return { "Scientist", &scientist_color, &Config::ESP::scientists, &Config::Radar::scientists, EntityCategory::Player };
    case static_cast<uint64_t>(EntityType::WORKBENCH1):
        return { "Workbench 1", &raid_color, &Config::ESP::raid, &Config::Radar::raid, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::WORKBENCH2):
        return { "Workbench 2", &raid_color, &Config::ESP::raid, &Config::Radar::raid, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::WORKBENCH3):
        return { "Workbench 3", &raid_color, &Config::ESP::raid, &Config::Radar::raid, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::TOOLCUPBOARD):
        return { "TC", &raid_color, &Config::ESP::raid, &Config::Radar::raid, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::DROPPEDITEM1):
    case static_cast<uint64_t>(EntityType::DROPPEDITEM2):
        return { "Dropped Item", &dropped_color, &Config::ESP::dropped, &Config::Radar::dropped, EntityCategory::Dynamic };
    //case static_cast<uint64_t>(EntityType::BACKPACK):
    //    return { "Backpack", &dropped_color };
    case static_cast<uint64_t>(EntityType::CORPSE1):
    case static_cast<uint64_t>(EntityType::CORPSE2):
    case static_cast<uint64_t>(EntityType::CORPSE3):
    case static_cast<uint64_t>(EntityType::CORPSE4):
    case static_cast<uint64_t>(EntityType::CORPSE5):
        return { "Dead Body", &corpse_color, &Config::ESP::corpses, &Config::Radar::corpses, EntityCategory::Dynamic };
    case static_cast<uint64_t>(EntityType::LARGE_WOODEN_BOX):
        return { "Large Box", &raid_color, &Config::ESP::raid, &Config::Radar::raid, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::SMALL_WOODEN_BOX):
        return { "Small Box", &raid_color, &Config::ESP::raid, &Config::Radar::raid, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::HORIZONTAL_WOODEN_BARREL):
    case static_cast<uint64_t>(EntityType::VERTICAL_WOODEN_BARREL):
        return { "Wooden Barrel", &raid_color, &Config::ESP::raid, &Config::Radar::raid, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::COFFIN):
        return { "Coffin", &raid_color, &Config::ESP::raid, &Config::Radar::raid, EntityCategory::Static };
    //case static_cast<uint64_t>(EntityType::RECYCLER):
    //    return { "Recycler", &recycler_color };
    //case static_cast<uint64_t>(EntityType::RHIB):
    //    return "RHIB";
    //case static_cast<uint64_t>(EntityType::ROWBOAT):
    //    return "Row Boat";
    //case static_cast<uint64_t>(EntityType::TUGBOAT):
    //    return "Tug Boat";
    case static_cast<uint64_t>(EntityType::HORSE):
        return { "Horse", &animal_color, &Config::ESP::animals, &Config::Radar::animals, EntityCategory::Dynamic };
    //case static_cast<uint64_t>(EntityType::MINI):
    //    return "Mini Heli";
    //case static_cast<uint64_t>(EntityType::SCRAP):
    //    return "Scrap Heli";
    //case static_cast<uint64_t>(EntityType::AIRBALLOON):
    //    return "Air Balloon";
    //case static_cast<uint64_t>(EntityType::SUBMARINESOLO):
    //case static_cast<uint64_t>(EntityType::SUBMARINEDUO):
    //    return "SubMarine";
    //case static_cast<uint64_t>(EntityType::BRADLEYAPC):
    //    return "Bradley";
    //case static_cast<uint64_t>(EntityType::PATROLHELI):
    //    return "Patrol Heli";
    //case static_cast<uint64_t>(EntityType::CHINOOK):
    //    return "Chinook";
    case static_cast<uint64_t>(EntityType::WOOD):
        return { "Wood", &wood_color, &Config::ESP::wood, &Config::Radar::wood, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::METAL):
    case static_cast<uint64_t>(EntityType::METAL2):
    case static_cast<uint64_t>(EntityType::METAL3):
    case static_cast<uint64_t>(EntityType::METAL4):
        return { "Metal", &metal_color, &Config::ESP::metal, &Config::Radar::metal, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::SULFUR):
    case static_cast<uint64_t>(EntityType::SULFUR2):
    case static_cast<uint64_t>(EntityType::SULFUR3):
    case static_cast<uint64_t>(EntityType::SULFUR4):
        return { "Sulfur", &sulfur_color, &Config::ESP::sulfur, &Config::Radar::sulfur, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::STONE):
    case static_cast<uint64_t>(EntityType::STONE2):
    case static_cast<uint64_t>(EntityType::STONE3):
    case static_cast<uint64_t>(EntityType::STONE4):
        return { "Stone", &stone_color, &Config::ESP::stone, &Config::Radar::stone, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::BEAR):
    case static_cast<uint64_t>(EntityType::POLARBEAR):
        return { "Bear", &animal_color, &Config::ESP::animals, &Config::Radar::animals, EntityCategory::Dynamic };
    case static_cast<uint64_t>(EntityType::BOAR):
        return { "Boar", &animal_color, &Config::ESP::animals, &Config::Radar::animals, EntityCategory::Dynamic };
    case static_cast<uint64_t>(EntityType::CHICKEN):
        return { "Chicken", &animal_color, &Config::ESP::animals, &Config::Radar::animals, EntityCategory::Dynamic };
    case static_cast<uint64_t>(EntityType::STAG):
        return { "Stag", &animal_color, &Config::ESP::animals, &Config::Radar::animals, EntityCategory::Dynamic };
    case static_cast<uint64_t>(EntityType::WOLF):
        return { "Wolf", &animal_color, &Config::ESP::animals, &Config::Radar::animals, EntityCategory::Dynamic };
    case static_cast<uint64_t>(EntityType::ZOMBIE):
        return { "Zombie", &animal_color, &Config::ESP::animals, &Config::Radar::animals, EntityCategory::Dynamic };
    case static_cast<uint64_t>(EntityType::HEMP):
        return { "Hemp", &hemp_color, &Config::ESP::hemp, &Config::Radar::hemp, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::MUSHROOM1):
    case static_cast<uint64_t>(EntityType::MUSHROOM2):
        return { "Mushroom", &food_color, &Config::ESP::food, &Config::Radar::food, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::PUMPKIN):
        return { "Pumpkin", &food_color, &Config::ESP::food, &Config::Radar::food, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CORN):
        return { "Corn", &food_color, &Config::ESP::food, &Config::Radar::food, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::BERRY_WHITE):
    case static_cast<uint64_t>(EntityType::BERRY_BLACK):
    case static_cast<uint64_t>(EntityType::BERRY_BLUE):
    case static_cast<uint64_t>(EntityType::BERRY_YELLOW):
    case static_cast<uint64_t>(EntityType::BERRY_RED):
    case static_cast<uint64_t>(EntityType::BERRY_GREEN):
        return { "Berry", &food_color, &Config::ESP::food, &Config::Radar::food, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::POTATO):
        return { "Potato", &food_color, &Config::ESP::food, &Config::Radar::food, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::COLLECTSULFUR):
        return { "Sulfur C", &sulfur_color, &Config::ESP::sulfurCollectable, &Config::Radar::sulfurCollectable, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::COLLECTSTONE):
        return { "Stone C", &stone_color, &Config::ESP::stoneCollectable, &Config::Radar::stoneCollectable, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::COLLECTWOOD):
        return { "Wood C", &wood_color, &Config::ESP::woodCollectable, &Config::Radar::woodCollectable, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::COLLECTMETAL):
        return { "Metal C", &metal_color, &Config::ESP::metalCollectable, &Config::Radar::metalCollectable, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::BARREL1):
    case static_cast<uint64_t>(EntityType::BARREL2):
    case static_cast<uint64_t>(EntityType::BARREL_1):
    case static_cast<uint64_t>(EntityType::BARREL_2):
        return { "Barrel", &barrel_color, &Config::ESP::barrels, &Config::Radar::barrels, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::BARREL_OIL):
        return { "Oil Barrel", &barrel_color, &Config::ESP::barrels, &Config::Radar::barrels, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_BASIC):
        return { "Basic Crate", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_ELITE):
        return { "Elite Crate", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_MINE):
        return { "Mine Crate", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_NORMAL):
    case static_cast<uint64_t>(EntityType::CRATE_NORMAL2):
        return { "Crate", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_NORMAL_FOOD):
        return { "Food Crate", &food_color, &Config::ESP::food, &Config::Radar::food, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_NORMAL_MEDICAL):
        return { "Med Crate", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_TOOLS):
        return { "Tool Crate", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_UNDERWATER_ADVANCED):
        return { "Advanced Crate", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_UNDERWATER_BASIC):
        return { "Basic Crate", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_BRADLEY):
    case static_cast<uint64_t>(EntityType::CRATE_HELI):
        return { "Elite Crate", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::CRATE_FOOD):
        return { "Food Crate", &food_color, &Config::ESP::food, &Config::Radar::food, EntityCategory::Static };
    case static_cast<uint64_t>(EntityType::AIRDROP):
        return { "Airdrop", &crate_color, &Config::ESP::crates, &Config::Radar::crates, EntityCategory::Static };
    //case static_cast<uint64_t>(EntityType::AUTOTURRET):
    //    return { "Auto Turret", &trap_color };
    //case static_cast<uint64_t>(EntityType::FLAMETURRET):
    //    return { "Flame Turret", &trap_color };
    //case static_cast<uint64_t>(EntityType::GUNTRAP):
    //    return { "Shotgun Trap", &trap_color };
    //case static_cast<uint64_t>(EntityType::SAMSTATIC):
    //case static_cast<uint64_t>(EntityType::SAMDEPLOYED):
    //    return { "Sam Site", &trap_color };
    //case static_cast<uint64_t>(EntityType::LANDDMINE):
    //    return { "Landmine", &trap_color };
    //case static_cast<uint64_t>(EntityType::BEARTRAP):
    //    return { "Bear Trap", &trap_color };
    default:
        return { "Unknown", &unknown_color, &Config::ESP::unknown, &Config::Radar::unknown, EntityCategory::Dynamic };
    }
}

void AddOutlinedText(ImDrawList* drawList, ImVec2 pos, ImU32 textColor, const char* text) {
    ImU32 outlineColor = IM_COL32(50, 50, 50, 255);

    drawList->AddText(ImVec2(pos.x - 1, pos.y), outlineColor, text);
    drawList->AddText(ImVec2(pos.x + 1, pos.y), outlineColor, text);
    drawList->AddText(ImVec2(pos.x, pos.y - 1), outlineColor, text);
    drawList->AddText(ImVec2(pos.x, pos.y + 1), outlineColor, text);

    drawList->AddText(pos, textColor, text);
}

void DrawRadar(const std::vector<BaseEntity>& list, const Vector3& localPos, float zoomFactor, float centerX, float centerY, ImDrawList* drawList) {
    for (const auto& entityData : list)
    {
        if (!(*entityData.entity_info.radar))
            continue;

        ImU32 color = ImGui::ColorConvertFloat4ToU32(*entityData.entity_info.color);

        float offsetX = (entityData.position.x - localPos.x) * zoomFactor;
        float offsetY = (entityData.position.z - localPos.z) * zoomFactor;
        float drawX = centerX + offsetX;
        float drawY = centerY - offsetY;

        drawList->AddCircleFilled(ImVec2(drawX, drawY), 5.0f, color);

        if (Config::Radar::distances)
        {
            char distLabel[32];
            snprintf(distLabel, sizeof(distLabel), "%.0fm", entityData.distance);

            ImVec2 textPos(drawX, drawY - 15.0f);
            drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), distLabel);
        }
    }
}


void DrawESP(ImDrawList* drawList, const std::vector<BaseEntity>& entityList) {
    for (const auto& itemData : entityList)
    {
        if (itemData.distance > Config::ESP::maxDistance)
            continue;

        if (!(*itemData.entity_info.esp))
            continue;

        std::string prefab_name = itemData.entity_info.name;
        std::string prefabID = std::to_string(itemData.prefab_id);
        ImU32 textColor = ImGui::ColorConvertFloat4ToU32(*itemData.entity_info.color);

        if (prefab_name == "Dropped Item")
            prefab_name = itemData.dropped_name;

        Vector2 screenPos = WorldToScreen(itemData.position, currentViewMatrix);
        if (screenPos.x <= 0.f && screenPos.y <= 0.f)
            continue;

        if (prefab_name == "Unknown" && Config::ESP::unknown)
            AddOutlinedText(drawList, ImVec2(screenPos.x, screenPos.y), textColor, prefabID.c_str());
        else
            AddOutlinedText(drawList, ImVec2(screenPos.x, screenPos.y), textColor, prefab_name.c_str());

        if (Config::ESP::distances) {
            char distStr[32];
            snprintf(distStr, sizeof(distStr), "%.0fm", itemData.distance);
            AddOutlinedText(drawList, ImVec2(screenPos.x, screenPos.y + 15), IM_COL32(255, 255, 255, 255), distStr);
        }
    }
}

std::string stringItem(uintptr_t item) {
    uintptr_t ItemDefinition = TargetProcess.Read<uintptr_t>(item + Offsets::Item::info); // public ItemDefinition info;
    uintptr_t ItemDisplayName = TargetProcess.Read<uintptr_t>(ItemDefinition + Offsets::ItemDefinition::displayName);
    uintptr_t ItemDisplayEnglish = TargetProcess.Read<uintptr_t>(ItemDisplayName + 0x18);
    std::wstring Name = ReadRustWString(ItemDisplayEnglish);
    std::string output(Name.begin(), Name.end());
    return output;
}

std::unordered_map<uint64_t, uint64_t> createEntityDictionary(VMMDLL_SCATTER_HANDLE read) {
    std::unordered_map<uint64_t, uint64_t> entityDictionary;

    if (globalCache.Error) {
        printf("Error in cache, cannot proceed with entity creation.\n");
        globalCache = StartCache();
        return {};
    }

    uint32_t entityListSize = TargetProcess.Read<uint32_t>(globalCache.ObjectDictionary + entityListSizeOffset);
    if (!local_player.address) {
        local_player.address = TargetProcess.Read<uint64_t>(globalCache.EntityListBase + 0x20);
    }

    if (!entityListSize) {
        printf("Failed to read entity list size\n");
        return {};
    }

    std::vector<uint64_t> entities(entityListSize, 0);

    for (size_t i = 1; i < entityListSize; i++) {
        TargetProcess.AddScatterReadRequest(read, globalCache.EntityListBase + 0x20 + (i * 0x8), &entities[i], sizeof(uint64_t));
    }
    TargetProcess.ExecuteReadScatter(read);

    for (auto& entity : entities) {
        TargetProcess.AddScatterReadRequest(read, entity + 0x30, &entityDictionary[entity], sizeof(uint64_t));
    }
    TargetProcess.ExecuteReadScatter(read);

    return entityDictionary;
}

std::tuple <std::unordered_map<uint64_t, BasePlayer>, std::unordered_map<uint64_t, BaseEntity>, std::unordered_map<uint64_t, BaseEntity>> filterEntityDictionary(const std::unordered_map<uint64_t, uint64_t>& inputDict) {
    auto filteredPlayerDictionary = playerDictionary;
    auto filteredDynamicDictionary = dynamicDictionary;
    auto filteredStaticDictionary = staticDictionary;

    for (const auto& [address, prefab_id] : inputDict) {
        EntityInfo entityInfo = getEntityInfo(prefab_id);
        std::string prefab_name = entityInfo.name;

        auto removeFromAllDictionaries = [&](uint64_t address) {
            filteredPlayerDictionary.erase(address);
            filteredDynamicDictionary.erase(address);
            filteredStaticDictionary.erase(address);
            };

        bool needsUpdate = false;

        auto checkDictionary = [&](auto& dictionary) -> bool {
            auto it = dictionary.find(address);
            return (it != dictionary.end() && it->second.prefab_id != prefab_id);
            };

        if (checkDictionary(filteredDynamicDictionary) ||
            checkDictionary(filteredStaticDictionary) ||
            checkDictionary(filteredPlayerDictionary)) {
            needsUpdate = true;
        }

        if (needsUpdate) {
            removeFromAllDictionaries(address);
        }

        switch (entityInfo.category) {
        case EntityCategory::Player: {
            BasePlayer player;
            player.prefab_id = prefab_id;
            player.entity_info = entityInfo;
            filteredPlayerDictionary[address] = player;
            break;
        }
        case EntityCategory::Dynamic: {
            BaseEntity entity;
            entity.prefab_id = prefab_id;
            entity.entity_info = entityInfo;
            filteredDynamicDictionary[address] = entity;
            break;
        }
        case EntityCategory::Static: {
            BaseEntity entity;
            entity.prefab_id = prefab_id;
            entity.entity_info = entityInfo;
            filteredStaticDictionary[address] = entity;
            break;
        }
        default:
            break;
        }
    }

    auto removeInvalidEntities = [&](auto& dictionary) {
        for (auto it = dictionary.begin(); it != dictionary.end(); ) {
            if (inputDict.find(it->first) == inputDict.end()) {
                it = dictionary.erase(it);
            }
            else {
                ++it;
            }
        }
        };

    removeInvalidEntities(filteredPlayerDictionary);
    removeInvalidEntities(filteredDynamicDictionary);
    removeInvalidEntities(filteredStaticDictionary);

    return std::make_tuple(
        filteredPlayerDictionary, filteredDynamicDictionary, filteredStaticDictionary
    );
}

void updateData()
{
    auto lastPlayerChamsUpdateTime = std::chrono::steady_clock::now();
    auto lastScientistChamsUpdateTime = std::chrono::steady_clock::now();
    auto lastStaticUpdateTime = std::chrono::steady_clock::now();
    auto lastEntityUpdateTime = std::chrono::steady_clock::now();

    auto scatter = TargetProcess.CreateScatterHandle();
    auto write = TargetProcess.CreateScatterHandle(-1);

    while (true) {
        while (isClearingCache.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastEntityUpdateTime).count() >= 5) {
            std::async(std::launch::async, [&]() {
                std::unordered_map<uint64_t, uint64_t> newDict = createEntityDictionary(scatter);
                auto filteredData = filterEntityDictionary(newDict);
                {
                    std::lock_guard<std::mutex> lock(g_dataMutex);
                    entityDictionarySize = newDict.size();
                    std::tie(playerDictionary, dynamicDictionary, staticDictionary) = std::move(filteredData);
                }
                });
            lastEntityUpdateTime = now;
        }

        std::unordered_map<uint64_t, std::vector<wchar_t>> nameBuffers;

        BasePlayer temp_local_player;
        temp_local_player.address = local_player.address;
        std::vector<BasePlayer> tempPlayers;
        std::vector<BaseEntity> tempStatics;
        std::vector<BaseEntity> tempDynamics;

        TargetProcess.AddScatterReadRequest(scatter, temp_local_player.address + Offsets::BasePlayer::playerModel, &temp_local_player.model, sizeof(uint64_t));
        TargetProcess.AddScatterReadRequest(scatter, temp_local_player.address + Offsets::BasePlayer::currentTeam, &temp_local_player.team, sizeof(uint32_t));
        if (!temp_local_player.inventory_encrypted) {
            TargetProcess.AddScatterReadRequest(scatter, temp_local_player.address + Offsets::BasePlayer::inventoryValue, &temp_local_player.inventory_encrypted, sizeof(uint64_t));
        }
        TargetProcess.AddScatterReadRequest(scatter, temp_local_player.address + Offsets::BasePlayer::clActiveItem, &temp_local_player.active_item_id, sizeof(uint64_t));

        for (auto& [address, player] : playerDictionary) {
            if (!player.model) {
                TargetProcess.AddScatterReadRequest(scatter, address + Offsets::BasePlayer::playerModel, &player.model, sizeof(uint64_t));
            }
            TargetProcess.AddScatterReadRequest(scatter, address + Offsets::BasePlayer::playerFlags, &player.flags, sizeof(uint32_t));
            TargetProcess.AddScatterReadRequest(scatter, address + Offsets::BasePlayer::currentTeam, &player.team, sizeof(uint32_t));
            if (!player.name_ptr) {
                TargetProcess.AddScatterReadRequest(scatter, address + Offsets::BasePlayer::_displayName, &player.name_ptr, sizeof(uint64_t));
            }
            TargetProcess.AddScatterReadRequest(scatter, address + Offsets::BaseCombatEntity::lifestate, &player.life_state, sizeof(LifeState));

            if (!player.inventory_encrypted) {
                TargetProcess.AddScatterReadRequest(scatter, address + Offsets::BasePlayer::inventoryValue, &player.inventory_encrypted, sizeof(uint64_t));
            }
            TargetProcess.AddScatterReadRequest(scatter, address + Offsets::BasePlayer::clActiveItem, &player.active_item_id, sizeof(uint64_t));

            //if (Config::ESP::Player::Bones::show) {
            //    
            //}

        }

        for (auto& [address, entity] : dynamicDictionary) {
            if (!entity.base_object) {
                TargetProcess.AddScatterReadRequest(scatter, address + 0x10, &entity.base_object, sizeof(uint64_t));
            }
        }

        for (auto& [address, entity] : staticDictionary) {
            if (!entity.base_object) {
                TargetProcess.AddScatterReadRequest(scatter, address + 0x10, &entity.base_object, sizeof(uint64_t));
            }
        }

        TargetProcess.ExecuteReadScatter(scatter);

        TargetProcess.AddScatterReadRequest(scatter, temp_local_player.model + Offsets::PlayerModel::position, &temp_local_player.position, sizeof(Vector3));
        if (!temp_local_player.inventory) {
            temp_local_player.inventory = decrypt_inventory_pointer(temp_local_player.inventory_encrypted);
        }
        if (!temp_local_player.inventory_belt) {
            TargetProcess.AddScatterReadRequest(scatter, temp_local_player.inventory + Offsets::PlayerInventory::containerBelt, &temp_local_player.inventory_belt, sizeof(uint64_t));
        }

        for (auto& [address, player] : playerDictionary) {
            if (player.model) {
                TargetProcess.AddScatterReadRequest(scatter, player.model + Offsets::PlayerModel::position, &player.position, sizeof(Vector3));
                if (!player.skinned_multi_meshes) {
                    TargetProcess.AddScatterReadRequest(scatter, player.model + Offsets::PlayerModel::_multiMesh, &player.skinned_multi_meshes, sizeof(uint64_t));
                }
            }
            if (!player.name_length) {
                TargetProcess.AddScatterReadRequest(scatter, player.name_ptr + 0x10, &player.name_length, sizeof(int));
            }
            player.is_sleeping = (player.flags & 16);
            player.is_wounded = (player.flags & 64);
            player.is_dead = (player.life_state & LifeState::Dead);
            if (!player.inventory) {
                player.inventory = decrypt_inventory_pointer(player.inventory_encrypted);
            }
            if (!player.inventory_belt) {
                TargetProcess.AddScatterReadRequest(scatter, player.inventory + Offsets::PlayerInventory::containerBelt, &player.inventory_belt, sizeof(uint64_t));
            }
        }

        for (auto& [address, entity] : dynamicDictionary) {
            if (!entity.entity_object) {
                TargetProcess.AddScatterReadRequest(scatter, entity.base_object + 0x30, &entity.entity_object, sizeof(uint64_t));
            }
        }

        for (auto& [address, entity] : staticDictionary) {
            if (!entity.entity_object) {
                TargetProcess.AddScatterReadRequest(scatter, entity.base_object + 0x30, &entity.entity_object, sizeof(uint64_t));
            }
        }
        TargetProcess.ExecuteReadScatter(scatter);

        if (!temp_local_player.belt_contents_list) {
            TargetProcess.AddScatterReadRequest(scatter, temp_local_player.inventory_belt + Offsets::ItemContainer::itemList, &temp_local_player.belt_contents_list, sizeof(uint64_t));
        }

        for (auto& [address, player] : playerDictionary) {
            player.distance = Vector3::Distance(temp_local_player.position, player.position);
            if (player.name.empty()) {
                nameBuffers[address] = std::vector<wchar_t>(player.name_length + 1, L'\0');
                TargetProcess.AddScatterReadRequest(scatter, player.name_ptr + 0x14, nameBuffers[address].data(), player.name_length * sizeof(wchar_t));
            }

            if (!player.renderer_lists) {
                TargetProcess.AddScatterReadRequest(scatter, player.skinned_multi_meshes + Offsets::SkinnedMultiMesh::renderersList, &player.renderer_lists, sizeof(uint64_t));
            }

            if (!player.belt_contents_list) {
                TargetProcess.AddScatterReadRequest(scatter, player.inventory_belt + Offsets::ItemContainer::itemList, &player.belt_contents_list, sizeof(uint64_t));
            }
        }

        for (auto& [address, entity] : dynamicDictionary) {
            if (!entity.entity_class) {
                TargetProcess.AddScatterReadRequest(scatter, entity.entity_object + 0x30, &entity.entity_class, sizeof(uint64_t));
            }
        }

        for (auto& [address, entity] : staticDictionary)
        {
            if (!entity.entity_class) {
                TargetProcess.AddScatterReadRequest(scatter, entity.entity_object + 0x30, &entity.entity_class, sizeof(uint64_t));
            }
        }
        TargetProcess.ExecuteReadScatter(scatter);

        if (!temp_local_player.belt_contents) {
            TargetProcess.AddScatterReadRequest(scatter, temp_local_player.belt_contents_list + 0x10, &temp_local_player.belt_contents, sizeof(uint64_t));
        }

        for (auto& [address, player] : playerDictionary) {
            if (player.name.empty()) {
                player.name = std::wstring(nameBuffers[address].data(), player.name_length);
            }
            if (!player.belt_contents) {
                TargetProcess.AddScatterReadRequest(scatter, player.belt_contents_list + 0x10, &player.belt_contents, sizeof(uint64_t));
            }
            if (!player.skinned_list) {
                TargetProcess.AddScatterReadRequest(scatter, player.renderer_lists + 0x10, &player.skinned_list, sizeof(uint64_t));
            }
        }

        for (auto& [address, entity] : dynamicDictionary) {
            if (!entity.entity_transform) {
                TargetProcess.AddScatterReadRequest(scatter, entity.entity_class + 0x8, &entity.entity_transform, sizeof(uint64_t));
            }
        }

        for (auto& [address, entity] : staticDictionary) {
            if (!entity.entity_transform) {
                TargetProcess.AddScatterReadRequest(scatter, entity.entity_class + 0x8, &entity.entity_transform, sizeof(uint64_t));
            }
        }
        TargetProcess.ExecuteReadScatter(scatter);

        if (temp_local_player.active_item_id != temp_local_player.current_active_item_id) {
            if (temp_local_player.belt_contents != 0)
            {
                for (int j = 0; j < 6; j++)
                {
                    TargetProcess.AddScatterReadRequest(scatter, temp_local_player.belt_contents + 0x20 + (j * 8), &temp_local_player.item_slots[j], sizeof(uint64_t));
                }
            }
        }

        for (auto& [address, player] : playerDictionary) {
            if (player.active_item_id != player.current_active_item_id) {
                if (player.belt_contents != 0)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        TargetProcess.AddScatterReadRequest(scatter, player.belt_contents + 0x20 + (j * 8), &player.item_slots[j], sizeof(uint64_t));
                    }
                }
            }
        }

        for (auto& [address, entity] : dynamicDictionary) {
            if (!entity.entity_visual_state) {
                TargetProcess.AddScatterReadRequest(scatter, entity.entity_transform + 0x38, &entity.entity_visual_state, sizeof(uint64_t));
            }
        }

        for (auto& [address, entity] : staticDictionary) {
            if (!entity.entity_visual_state) {
                TargetProcess.AddScatterReadRequest(scatter, entity.entity_transform + 0x38, &entity.entity_visual_state, sizeof(uint64_t));
            }
        }
        TargetProcess.ExecuteReadScatter(scatter);

        if (temp_local_player.active_item_id != temp_local_player.current_active_item_id) {
            if (temp_local_player.belt_contents != 0) {
                for (int j = 0; j < 6; j++)
                {
                    if (temp_local_player.item_slots[j] != 0)
                    {
                        TargetProcess.AddScatterReadRequest(scatter, temp_local_player.item_slots[j] + Offsets::ItemDefinition::itemid, &temp_local_player.item_ids[j], sizeof(uint64_t));
                    }
                }
            }
        }

        for (auto& [address, player] : playerDictionary) {
            if (player.active_item_id != player.current_active_item_id) {
                if (player.belt_contents != 0) {
                    for (int j = 0; j < 6; j++)
                    {
                        if (player.item_slots[j] != 0)
                        {
                            TargetProcess.AddScatterReadRequest(scatter, player.item_slots[j] + Offsets::ItemDefinition::itemid, &player.item_ids[j], sizeof(uint64_t));
                        }
                    }
                }
            }
        }

        for (auto& [address, entity] : dynamicDictionary) {
            if (entity.entity_info.name == "Unknown" && !Config::ESP::unknown)
                continue;
            TargetProcess.AddScatterReadRequest(scatter, entity.entity_visual_state + 0x90, &entity.position, sizeof(Vector3));
        }

        for (auto& [address, entity] : staticDictionary) {
            if (!entity.position_initialized) {
                TargetProcess.AddScatterReadRequest(scatter, entity.entity_visual_state + 0x90, &entity.position, sizeof(Vector3));
                entity.position_initialized = true;
            }
        }
        TargetProcess.ExecuteReadScatter(scatter);

        for (auto& [address, entity] : staticDictionary) {
            entity.distance = Vector3::Distance(temp_local_player.position, entity.position);
        }

        for (auto& [address, entity] : dynamicDictionary) {
            entity.distance = Vector3::Distance(temp_local_player.position, entity.position);

            if (entity.entity_info.name == "Dropped Item" && entity.dropped_name.empty()) {
                uintptr_t ItemDefinition = TargetProcess.Read<uintptr_t>(address + 0x198);
                uintptr_t String1 = TargetProcess.Read<uintptr_t>(ItemDefinition + 0x88);
                uintptr_t String2 = TargetProcess.Read<uintptr_t>(String1 + 0x28);
                std::wstring dropped = ReadRustWString(String2);
                std::string output(dropped.begin(), dropped.end());
                entity.dropped_name = output;
            }
        }

        if (temp_local_player.active_item_id != temp_local_player.current_active_item_id) {
            for (int j = 0; j < 6; j++)
            {

                if (temp_local_player.active_item_id == temp_local_player.item_ids[j])
                {
                    temp_local_player.held_item_ptr = temp_local_player.item_slots[j];
                    break;
                }
            }
        }

        for (auto& [address, player] : playerDictionary) {
            if (player.active_item_id != player.current_active_item_id) {
                for (int j = 0; j < 6; j++)
                {

                    if (player.active_item_id == player.item_ids[j])
                    {
                        player.held_item_ptr = player.item_slots[j];
                        break;
                    }
                }
            }
        }

        if (temp_local_player.active_item_id != temp_local_player.current_active_item_id) {
            uint64_t decryptedItemId = Ulong(temp_local_player.active_item_id);
            temp_local_player.current_active_item_id = temp_local_player.active_item_id;
            for (int j = 0; j < 6; j++)
            {
                if (decryptedItemId == temp_local_player.item_ids[j])
                {
                    temp_local_player.held_item = stringItem(temp_local_player.item_slots[j]);
                    break;
                }
            }
        }

        for (auto& [address, player] : playerDictionary)
        {
            if (player.active_item_id != player.current_active_item_id) {
                uint64_t decryptedItemId = Ulong(player.active_item_id);
                for (int j = 0; j < 6; j++)
                {
                    if (decryptedItemId == player.item_ids[j])
                    {
                        TargetProcess.AddScatterReadRequest(scatter, player.item_slots[j] + Offsets::Item::info, &player.item_definition, sizeof(uintptr_t));
                        break;
                    }
                }
            }
        }
        TargetProcess.ExecuteReadScatter(scatter);
        
        for (auto& [address, player] : playerDictionary)
        {
            if (player.active_item_id != player.current_active_item_id) {
                TargetProcess.AddScatterReadRequest(scatter, player.item_definition + Offsets::ItemDefinition::displayName, &player.item_display_name, sizeof(uintptr_t));
            }
        }
        TargetProcess.ExecuteReadScatter(scatter);
        
        for (auto& [address, player] : playerDictionary)
        {
            if (player.active_item_id != player.current_active_item_id) {
                TargetProcess.AddScatterReadRequest(scatter, player.item_display_name + 0x18, &player.item_display_name_english, sizeof(uintptr_t));
            }
        }
        TargetProcess.ExecuteReadScatter(scatter);
        
        for (auto& [address, player] : playerDictionary)
        {
            if (player.active_item_id != player.current_active_item_id) {
                player.current_active_item_id = player.active_item_id;
                std::wstring Name = ReadRustWString(player.item_display_name_english);
                std::string output(Name.begin(), Name.end());
                player.held_item = output;
            }

            tempPlayers.push_back(player);
        }

        for (auto& [address, entity] : dynamicDictionary)
        {
            tempDynamics.push_back(entity);
        }

        for (auto& [address, entity] : staticDictionary)
        {
            tempStatics.push_back(entity);
        }

        {
            std::lock_guard<std::mutex> lock(g_dataMutex);
            local_player = temp_local_player;
            g_PlayerList = tempPlayers;
            g_DynamicList = tempDynamics;
            g_StaticList = tempStatics;
        }

        if (!playerDictionary.empty() && std::chrono::duration_cast<std::chrono::seconds>(now - lastPlayerChamsUpdateTime).count() >= 5) {
            std::vector<uint64_t> playerAddresses;
            std::vector<uint64_t> playerRendererLists;
            std::vector<uint64_t> playerSkinnedList;
            std::vector<uint64_t> scientistAddresses;
            std::vector<uint64_t> scientistRendererLists;
            std::vector<uint64_t> scientistSkinnedList;

            for (auto& [address, player] : playerDictionary) {
                if (player.entity_info.name == "Player" && Config::Chams::Player::show)
                {
                    playerAddresses.push_back(address);
                    playerRendererLists.push_back(player.renderer_lists);
                    playerSkinnedList.push_back(player.skinned_list);
                }
                else if (player.entity_info.name == "Scientist" && Config::Chams::Scientist::show)
                {
                    scientistAddresses.push_back(address);
                    scientistRendererLists.push_back(player.renderer_lists);
                    scientistSkinnedList.push_back(player.skinned_list);
                }
            }

            if (!playerAddresses.empty()) {
                ApplyChamsToPlayers(scatter, write, playerAddresses, playerRendererLists, playerSkinnedList, Config::Chams::Player::material);
            }

            if (!scientistAddresses.empty()) {
                ApplyChamsToPlayers(scatter, write, scientistAddresses, scientistRendererLists, scientistSkinnedList, Config::Chams::Scientist::material);
            }

            lastPlayerChamsUpdateTime = now;
        }


        Sleep(5);
    }
}

// --------------------------------------------------------------------------------
// ImGui/Win32/Dx11 setup
// --------------------------------------------------------------------------------

static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static bool                         g_SwapChainOccluded = false;
static UINT                         g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

void colorEditor(const char* label, ImColor& color) {
    ImGui::SameLine(ImGui::GetWindowWidth() - 30);
    ImGui::ColorEdit4(label, (float*)&color.Value, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
}

bool initializeTargetProcess(bool memmap)
{
    while (!TargetProcess.Init("RustClient.exe", memmap, false))
    {
        std::cout << "Failed to initialize memory read. Retrying...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    gameAssemblyBase = TargetProcess.GetBaseAddress("GameAssembly.dll");
    if (!gameAssemblyBase)
    {
        std::cout << "Failed to find GameAssembly.dll base\n";
        return false;
    }

    Beep(500, 500);
    return true;
}

int main()
{
    LoadRecoilCache();

    bool memmap = true;
    std::string input;

    std::cout << "Most users can enable memory mapping. Some 75T cards do not support memory mapping. Enable memory mapping? (y/n): ";
    std::cin >> input;

    if (input == "y")
    {
        memmap = true;
    }
    else if (input == "n")
    {
        memmap = false;
    }
    else
    {
        std::cout << "Invalid input. Defaulting to true.\n";
    }

    if (!initializeTargetProcess(memmap))
    {
        return 1;
    }

    std::thread(LogReadsPerSecond).detach();

    globalCache = StartCache();

    std::thread(updateData).detach();

    ImGui_ImplWin32_EnableDpiAwareness();
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    halfScreenWidth = screenWidth / 2;
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    halfScreenHeight = screenHeight / 2;

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"Quasar", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Quasar", WS_POPUP, 0, 0, screenWidth, screenHeight, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // 4) Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup theme
    ImGui::StyleColorsDark();
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;
    style->FrameRounding = 4.0f;
    style->GrabRounding = 4.0f;
    colors[ImGuiCol_FrameBg] = ImVec4(0.45f, 0.27f, 0.70f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.45f, 0.27f, 0.70f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.45f, 0.27f, 0.70f, 0.67f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.07f, 0.24f, 0.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.24f, 0.11f, 0.31f, 0.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.67f, 0.34f, 0.78f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.67f, 0.34f, 0.78f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.59f, 0.29f, 0.70f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.67f, 0.34f, 0.78f, 0.80f);
    colors[ImGuiCol_Tab] = ImVec4(0.31f, 0.13f, 0.38f, 0.86f);
    colors[ImGuiCol_TabSelected] = ImVec4(0.45f, 0.10f, 0.57f, 1.00f);
    colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.60f, 0.22f, 0.73f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.34f, 0.78f, 0.80f);
    colors[ImGuiCol_Button] = ImVec4(0.31f, 0.13f, 0.38f, 0.86f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.10f, 0.57f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.f, 0.f, 0.f, 0.f);
    colors[ImGuiCol_Header] = ImVec4(0.31f, 0.13f, 0.38f, 0.86f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.67f, 0.34f, 0.78f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.10f, 0.57f, 1.00f);

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    static bool equalKeyDown = false;
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    bool closeWindow = false;
    while (!closeWindow)
    {
        while (isClearingCache.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        if (ImGui::IsKeyPressed(ImGuiKey_Equal))
        {
            if (!equalKeyDown)
            {
                Config::Misc::show = !Config::Misc::show;
                equalKeyDown = true;
            }
        }
        else
        {
            equalKeyDown = false;
        }

        {
            MSG msg;
            while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                    closeWindow = true;
            }
            if (closeWindow)
                break;

            if (globalCache.Camera)
            {
                currentViewMatrix = TargetProcess.Read<ViewMatrix>(globalCache.Camera + matrixOffset);
            }
            else
            {
                globalCache = StartCache();
            }

            // Handle window being minimized or screen locked
            if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
            {
                ::Sleep(10);
                continue;
            }
            g_SwapChainOccluded = false;

            // Handle window resize (we don't resize directly in the WM_SIZE handler)
            if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
            {
                CleanupRenderTarget();
                g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
                g_ResizeWidth = g_ResizeHeight = 0;
                CreateRenderTarget();
            }
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (Config::Radar::show)
        {
            ImGui::SetNextWindowPos(ImVec2(10, 10));
            ImGui::SetNextWindowSize(ImVec2(screenHeight * Config::Radar::size, screenHeight * Config::Radar::size));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGui::ColorConvertFloat4ToU32(radar_color));
            ImGui::Begin("Radar", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoNav |
                ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_NoScrollbar
            );

            ImVec2 screenSize = ImGui::GetContentRegionAvail();
            ImVec2 windowPos = ImGui::GetWindowPos();
            float centerX = windowPos.x + screenSize.x * 0.5f;
            float centerY = windowPos.y + screenSize.y * 0.5f;

            ImDrawList* drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(
                ImVec2(windowPos.x, windowPos.y),
                ImVec2(windowPos.x + screenSize.x, windowPos.y + screenSize.y),
                ImGui::ColorConvertFloat4ToU32(radar_color)
            );

            drawList->AddCircleFilled(ImVec2(centerX, centerY), 5.0f, ImGui::ColorConvertFloat4ToU32(teammate_color));

            for (auto& playerData : g_PlayerList)
            {
                bool is_scientist = (playerData.entity_info.name == "Scientist");

                if (playerData.is_sleeping && !Config::Radar::sleepers)
                    continue;

                if (is_scientist && !Config::Radar::scientists)
                    continue;

                if (!is_scientist && !Config::Radar::players)
                    continue;

                float offsetX = (playerData.position.x - local_player.position.x) * Config::Radar::zoom;
                float offsetY = (playerData.position.z - local_player.position.z) * Config::Radar::zoom;

                float drawX = centerX + offsetX;
                float drawY = centerY - offsetY;

                ImU32 color;
                if (is_scientist)
                {
                    color = ImGui::ColorConvertFloat4ToU32(scientist_color);
                }
                else if (local_player.team != 0 && local_player.team == playerData.team)
                {
                    color = ImGui::ColorConvertFloat4ToU32(teammate_color);
                    if (Config::Radar::hideTeam)
                        continue;
                }
                else
                {
                    color = playerData.is_sleeping ? ImGui::ColorConvertFloat4ToU32(sleeper_color) : ImGui::ColorConvertFloat4ToU32(player_color);
                }

                drawList->AddCircleFilled(ImVec2(drawX, drawY), 5.0f, color);

                if (Config::Radar::distances)
                {
                    char distLabel[32];
                    snprintf(distLabel, sizeof(distLabel), "%.0fm", playerData.distance);

                    ImVec2 textPos(drawX, drawY - 15.0f);
                    drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), distLabel);
                }

                if (Config::Radar::names && !playerData.name.empty())
                {
                    std::string utf8Name = WStringToUTF8(playerData.name);
                    ImGui::SetCursorScreenPos(ImVec2(drawX, drawY + 8.0f));
                    ImGui::Text(utf8Name.c_str());
                }

                if (Config::Radar::team && playerData.team != 0)
                {
                    std::string team = std::to_string(playerData.team);
                    ImGui::SetCursorScreenPos(ImVec2(drawX - 8.0f, drawY));
                    ImGui::Text("%s", team.c_str());
                }
            }

            DrawRadar(g_DynamicList, local_player.position, Config::Radar::zoom, centerX, centerY, drawList);
            DrawRadar(g_StaticList, local_player.position, Config::Radar::zoom, centerX, centerY, drawList);

            ImVec2 dir2D = getPlayerLookDirection(currentViewMatrix);

            float lineLen = 150.0f;
            float lineX = centerX + dir2D.x * lineLen;
            float lineY = centerY + dir2D.y * lineLen;
            drawList->AddLine(ImVec2(centerX, centerY), ImVec2(lineX, lineY),
                ImGui::ColorConvertFloat4ToU32(teammate_color), 2.0f);

            ImGui::End();
            ImGui::PopStyleColor();
        }

        if (Config::ESP::show)
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(screenWidth, screenHeight));
            ImGui::Begin("ESP Fullscreen", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoNav |
                ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_NoBackground |
                ImGuiWindowFlags_NoScrollbar
            );

            ImDrawList* drawList = ImGui::GetWindowDrawList();

            if (true)
            {
                if (Config::ESP::Player::show)
                {
                    for (auto& playerData : g_PlayerList)
                    {
                        bool is_scientist = (playerData.entity_info.name == "Scientist");

                        if (is_scientist && !Config::ESP::scientists)
                            continue;

                        if (playerData.is_sleeping && !Config::ESP::Player::sleepers)
                            continue;

                        if (Config::ESP::Player::hide_team && local_player.team != 0 && local_player.team == playerData.team)
                            continue;

                        if (playerData.distance > Config::ESP::maxDistance)
                            continue;

                        ImVec2 finalBoxMin, finalBoxMax;
                        float finalBoxWidth = 0, finalBoxHeight = 0;
                        bool shouldDrawText = false;

                        //if (Config::ESP::Player::Bones::show)
                        //{
                        //    if (!playerData.transformPtr) continue;

                        //    std::unordered_map<std::string, Vector2> bonePositions = {
                        //        {"head", WorldToScreen(playerData.transformPtr->get_position("head"), currentViewMatrix)},
                        //        {"neck", WorldToScreen(playerData.transformPtr->get_position("neck"), currentViewMatrix)},
                        //        {"jaw", WorldToScreen(playerData.transformPtr->get_position("jaw"), currentViewMatrix)},
                        //        {"spine4", WorldToScreen(playerData.transformPtr->get_position("spine4"), currentViewMatrix)},
                        //        {"spine3", WorldToScreen(playerData.transformPtr->get_position("spine3"), currentViewMatrix)},
                        //        {"spine2", WorldToScreen(playerData.transformPtr->get_position("spine2"), currentViewMatrix)},
                        //        {"spine1", WorldToScreen(playerData.transformPtr->get_position("spine1"), currentViewMatrix)},
                        //        {"pelvis", WorldToScreen(playerData.transformPtr->get_position("pelvis"), currentViewMatrix)},
                        //        {"l_upperarm", WorldToScreen(playerData.transformPtr->get_position("l_upperarm"), currentViewMatrix)},
                        //        {"r_upperarm", WorldToScreen(playerData.transformPtr->get_position("r_upperarm"), currentViewMatrix)},
                        //        {"l_forearm", WorldToScreen(playerData.transformPtr->get_position("l_forearm"), currentViewMatrix)},
                        //        {"r_forearm", WorldToScreen(playerData.transformPtr->get_position("r_forearm"), currentViewMatrix)},
                        //        {"l_hand", WorldToScreen(playerData.transformPtr->get_position("l_hand"), currentViewMatrix)},
                        //        {"r_hand", WorldToScreen(playerData.transformPtr->get_position("r_hand"), currentViewMatrix)},
                        //        {"l_hip", WorldToScreen(playerData.transformPtr->get_position("l_hip"), currentViewMatrix)},
                        //        {"r_hip", WorldToScreen(playerData.transformPtr->get_position("r_hip"), currentViewMatrix)},
                        //        {"l_knee", WorldToScreen(playerData.transformPtr->get_position("l_knee"), currentViewMatrix)},
                        //        {"r_knee", WorldToScreen(playerData.transformPtr->get_position("r_knee"), currentViewMatrix)},
                        //        {"l_foot", WorldToScreen(playerData.transformPtr->get_position("l_foot"), currentViewMatrix)},
                        //        {"r_foot", WorldToScreen(playerData.transformPtr->get_position("r_foot"), currentViewMatrix)},
                        //        {"l_toe", WorldToScreen(playerData.transformPtr->get_position("l_toe"), currentViewMatrix)},
                        //        {"r_toe", WorldToScreen(playerData.transformPtr->get_position("r_toe"), currentViewMatrix)}
                        //    };

                        //    if (Config::ESP::Player::Bones::head)
                        //    {
                        //        Vector2 headScreenPos = bonePositions["head"];
                        //        Vector2 neckScreenPos = bonePositions["neck"];

                        //        float radius = sqrt(pow(headScreenPos.x - neckScreenPos.x, 2) + pow(headScreenPos.y - neckScreenPos.y, 2)) * 1.5;

                        //        if (Config::ESP::Player::Bones::current_head_type == 0)
                        //        {
                        //            drawList->AddCircle(ImVec2(headScreenPos.x, headScreenPos.y), radius, head_color, 32, 2.0f);
                        //        }
                        //        else if (Config::ESP::Player::Bones::current_head_type == 1)
                        //        {
                        //            drawList->AddLine(ImVec2(headScreenPos.x - radius, headScreenPos.y), ImVec2(headScreenPos.x + radius, headScreenPos.y), head_color, 2.0f);
                        //            drawList->AddLine(ImVec2(headScreenPos.x, headScreenPos.y - radius), ImVec2(headScreenPos.x, headScreenPos.y + radius), head_color, 2.0f);
                        //        }
                        //    }

                        //    auto DrawBone = [&](const std::string& part1, const std::string& part2)
                        //        {
                        //            if (bonePositions[part1].x > 0 && bonePositions[part2].x > 0)
                        //            {
                        //                ImU32 lineColor = player_color;

                        //                if (local_player.team != 0 && local_player.team == playerData.team)
                        //                {
                        //                    lineColor = ImGui::ColorConvertFloat4ToU32(teammate_color);
                        //                }

                        //                drawList->AddLine(ImVec2(bonePositions[part1].x, bonePositions[part1].y),
                        //                    ImVec2(bonePositions[part2].x, bonePositions[part2].y),
                        //                    lineColor, 2.0f);
                        //            }
                        //        };


                        //    DrawBone("head", "neck");
                        //    DrawBone("neck", "spine4");
                        //    DrawBone("spine4", "spine3");
                        //    DrawBone("spine3", "spine2");
                        //    DrawBone("spine2", "spine1");
                        //    DrawBone("spine1", "pelvis");

                        //    DrawBone("neck", "l_upperarm");
                        //    DrawBone("neck", "r_upperarm");
                        //    DrawBone("l_upperarm", "l_forearm");
                        //    DrawBone("r_upperarm", "r_forearm");
                        //    DrawBone("l_forearm", "l_hand");
                        //    DrawBone("r_forearm", "r_hand");

                        //    DrawBone("pelvis", "l_hip");
                        //    DrawBone("pelvis", "r_hip");
                        //    DrawBone("l_hip", "l_knee");
                        //    DrawBone("r_hip", "r_knee");
                        //    DrawBone("l_knee", "l_foot");
                        //    DrawBone("r_knee", "r_foot");
                        //    DrawBone("l_foot", "l_toe");
                        //    DrawBone("r_foot", "r_toe");

                        //    float minX = FLT_MAX, minY = FLT_MAX;
                        //    float maxX = FLT_MIN, maxY = FLT_MIN;

                        //    for (const auto& bone : bonePositions)
                        //    {
                        //        const Vector2& pos = bone.second;
                        //        if (pos.x > 0 && pos.y > 0)
                        //        {
                        //            minX = std::min(minX, pos.x);
                        //            minY = std::min(minY, pos.y);
                        //            maxX = std::max(maxX, pos.x);
                        //            maxY = std::max(maxY, pos.y);
                        //        }
                        //    }

                        //    if (minX < FLT_MAX && minY < FLT_MAX && maxX > FLT_MIN && maxY > FLT_MIN)
                        //    {

                        //        finalBoxMin = ImVec2(minX, minY);
                        //        finalBoxMax = ImVec2(maxX, maxY);
                        //        finalBoxWidth = maxX - minX;
                        //        finalBoxHeight = maxY - minY;
                        //        shouldDrawText = true;

                        //        ImU32 color;
                        //        if (is_scientist)
                        //        {
                        //            color = scientist_color;
                        //        }
                        //        else if (local_player.team != 0 && local_player.team == playerData.team)
                        //        {
                        //            color = teammate_color;
                        //            if (Config::ESP::Player::hide_team)
                        //                continue;
                        //        }
                        //        else
                        //        {
                        //            color = playerData.is_sleeping ? sleeper_color : player_color;
                        //        }

                        //        if (Config::ESP::Player::Bones::boxes)
                        //        {
                        //            drawList->AddRect(finalBoxMin, finalBoxMax, color);
                        //        }
                        //    }

                        //}
                        if (Config::ESP::Player::boxes)
                        {
                            Vector3 feetPos = playerData.position;
                            feetPos.y -= 0.15f;
                            Vector3 headPos = playerData.position;
                            headPos.y += 1.7f;

                            Vector2 screenFeet = WorldToScreen(feetPos, currentViewMatrix);
                            Vector2 screenHead = WorldToScreen(headPos, currentViewMatrix);

                            if ((screenFeet.x <= 0.f && screenFeet.y <= 0.f) || (screenHead.x <= 0.f && screenHead.y <= 0.f))
                                continue;

                            if (!((screenFeet.x <= 0.f && screenFeet.y <= 0.f) || (screenHead.x <= 0.f && screenHead.y <= 0.f))) {
                                float boxHeight = (screenFeet.y - screenHead.y);
                                if (boxHeight > 0.f) {
                                    float boxWidth = boxHeight / 2.0f;
                                    float x = screenHead.x - (boxWidth / 2.f);
                                    float y = screenHead.y;

                                    finalBoxMin = ImVec2(x, y);
                                    finalBoxMax = ImVec2(x + boxWidth, y + boxHeight);
                                    finalBoxWidth = boxWidth;
                                    finalBoxHeight = boxHeight;
                                    shouldDrawText = true;
                                }
                            }

                            ImU32 color;
                            if (is_scientist)
                            {
                                color = scientist_color;
                            }
                            else if (local_player.team != 0 && local_player.team == playerData.team)
                            {
                                color = teammate_color;
                                if (Config::ESP::Player::hide_team)
                                    continue;
                            }
                            else
                            {
                                color = playerData.is_sleeping ? sleeper_color : player_color;
                            }

                            drawList->AddRect(finalBoxMin, finalBoxMax, color, 0.0f, 0, 0.5f);

                        }

                        if (shouldDrawText) {
                            if (playerData.is_wounded) {
                                std::string downedText = "DOWNED";
                                ImVec2 downedTextSize = ImGui::CalcTextSize(downedText.c_str());
                                ImVec2 downedTextPos = ImVec2(finalBoxMin.x + (finalBoxWidth - downedTextSize.x) / 2, finalBoxMin.y + (finalBoxHeight - downedTextSize.y) / 2);
                                AddOutlinedText(drawList, downedTextPos, IM_COL32(255, 255, 255, 255), downedText.c_str());
                            }

                            if (playerData.is_dead) {
                                std::string deadText = "DEAD";
                                ImVec2 deadTextSize = ImGui::CalcTextSize(deadText.c_str());
                                ImVec2 deadTextPos = ImVec2(finalBoxMin.x + (finalBoxWidth - deadTextSize.x) / 2, finalBoxMin.y + (finalBoxHeight - deadTextSize.y) / 2);
                                AddOutlinedText(drawList, deadTextPos, IM_COL32(255, 255, 255, 255), deadText.c_str());
                            }

                            std::string topText;
                            if (Config::ESP::Player::item) topText += playerData.held_item;
                            if (Config::ESP::Player::team && playerData.team != 0) {
                                if (!topText.empty()) topText += " ";
                                topText += "[" + std::to_string(playerData.team) + "]";
                            }
                            if (!topText.empty()) {
                                ImVec2 topTextSize = ImGui::CalcTextSize(topText.c_str());
                                ImVec2 topPos = ImVec2(finalBoxMin.x + (finalBoxWidth - topTextSize.x) / 2, finalBoxMin.y - topTextSize.y);
                                AddOutlinedText(drawList, topPos, IM_COL32(255, 255, 255, 255), topText.c_str());
                            }

                            std::string bottomText;
                            if (Config::ESP::Player::names && !playerData.name.empty()) bottomText += WStringToUTF8(playerData.name);
                            if (Config::ESP::distances) {
                                char distStr[32];
                                snprintf(distStr, sizeof(distStr), " [%.0fm]", playerData.distance);
                                bottomText += distStr;
                            }
                            if (!bottomText.empty()) {
                                ImVec2 bottomTextSize = ImGui::CalcTextSize(bottomText.c_str());
                                ImVec2 bottomPos = ImVec2(finalBoxMin.x + (finalBoxWidth - bottomTextSize.x) / 2, finalBoxMax.y);
                                AddOutlinedText(drawList, bottomPos, IM_COL32(255, 255, 255, 255), bottomText.c_str());
                            }
                        }
                    }
                }

                DrawESP(drawList, g_DynamicList);
                DrawESP(drawList, g_StaticList);
            }

            ImGui::End();
        }

        if (Config::Misc::crosshair)
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
            ImGui::Begin("Crosshair", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoNav |
                ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_NoBackground
            );

            ImDrawList* drawList = ImGui::GetWindowDrawList();
            ImVec2 screenCenter = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);

            drawList->AddLine(ImVec2(screenCenter.x - Config::Misc::crosshairSize, screenCenter.y),
                ImVec2(screenCenter.x + Config::Misc::crosshairSize, screenCenter.y),
                crosshair_color, 2.0f);

            drawList->AddLine(ImVec2(screenCenter.x, screenCenter.y - Config::Misc::crosshairSize),
                ImVec2(screenCenter.x, screenCenter.y + Config::Misc::crosshairSize),
                crosshair_color, 2.0f);

            ImGui::End();
        }

        if (Config::Misc::show)
        {
            ImGui::Begin("Quasar - Toggle this menu with =", NULL, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text("If you purchased this software from anywhere, you've been scammed.");
            ImGui::Text("Reads/s: %d", reads);
            ImGui::Text("Scatter Reads/s: %d", scatterReads);
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            ImGui::Text("Entities: %d", entityDictionarySize);

            if (ImGui::Button("Reset Cache")) {
                ResetCache();
            }
            if (ImGui::BeginTabBar("Admin Tabs"))
            {
                if (ImGui::BeginTabItem("ESP"))
                {
                    /*ImGui::Text("%d", screenWidth);
                    ImGui::Text("%d", screenHeight);*/
                    ImGui::Checkbox("ESP", &Config::ESP::show);
                    if (Config::ESP::show)
                    {
                        ImGui::Indent(16.0f);
                        ImGui::Checkbox("Players", &Config::ESP::Player::show);
                        colorEditor("ESP Enemy Color", player_color);
                        if (Config::ESP::Player::show)
                        {
                            ImGui::Indent(16.0f);
                            ImGui::Checkbox("Sleepers", &Config::ESP::Player::sleepers);
                            colorEditor("ESP Sleeper Color", sleeper_color);
                            ImGui::Checkbox("Player Names", &Config::ESP::Player::names);
                            ImGui::Checkbox("Player Teams", &Config::ESP::Player::team);
                            ImGui::Checkbox("Boxes", &Config::ESP::Player::boxes);
                            ImGui::Checkbox("Hide Teammates", &Config::ESP::Player::hide_team);
                            colorEditor("ESP Teammate Color", teammate_color);
                            ImGui::Checkbox("Held Item", &Config::ESP::Player::item);

                            //ImGui::Checkbox("Bones (quite buggy currently so I do not recommend)", &Config::ESP::Player::Bones::show);
                            //if (Config::ESP::Player::Bones::show)
                            //{
                            //    ImGui::Indent(16.0f);
                            //    ImGui::Checkbox("Bone Boxes", &Config::ESP::Player::Bones::boxes);
                            //    ImGui::Checkbox("Head", &Config::ESP::Player::Bones::head);
                            //    colorEditor("ESP Head Color", head_color);
                            //    if (Config::ESP::Player::Bones::head)
                            //    {
                            //        ImGui::Indent(16.0f);
                            //        ImGui::Combo("Type", &Config::ESP::Player::Bones::current_head_type, Config::ESP::Player::Bones::head_types, IM_ARRAYSIZE(Config::ESP::Player::Bones::head_types));
                            //        ImGui::Unindent(16.0f);
                            //    }
                            //    ImGui::Unindent(16.0f);
                            //}

                            ImGui::Unindent(16.0f);
                        }
                        ImGui::Checkbox("Barrels", &Config::ESP::barrels);
                        colorEditor("Esp Barrels Color", barrel_color);
                        ImGui::Checkbox("Crates", &Config::ESP::crates);
                        colorEditor("Esp Crates Color", crate_color);
                        ImGui::Checkbox("Raid Items (TCs/Boxes)", &Config::ESP::raid);
                        colorEditor("Raid Color", raid_color);
                        ImGui::Checkbox("Food", &Config::ESP::food);
                        colorEditor("Esp Food Color", food_color);
                        ImGui::Checkbox("Scientists", &Config::ESP::scientists);
                        colorEditor("Esp Scientists Color", scientist_color);
                        ImGui::Checkbox("Animals", &Config::ESP::animals);
                        colorEditor("Esp Animals Color", animal_color);
                        ImGui::Checkbox("Nodes", &Config::ESP::nodes);
                        if (Config::ESP::nodes) {
                            ImGui::Indent(16.0f);
                            ImGui::Checkbox("Wood", &Config::ESP::wood);
                            colorEditor("Wood Color", wood_color);
                            ImGui::Checkbox("Stone", &Config::ESP::stone);
                            colorEditor("Stone Color", stone_color);
                            ImGui::Checkbox("Metal", &Config::ESP::metal);
                            colorEditor("Metal Color", metal_color);
                            ImGui::Checkbox("Sulfur", &Config::ESP::sulfur);
                            colorEditor("Sulfur Color", sulfur_color);
                            ImGui::Unindent(16.0f);
                        }
                        else {
                            Config::ESP::wood = false;
                            Config::ESP::stone = false;
                            Config::ESP::metal = false;
                            Config::ESP::sulfur = false;
                        }
                        ImGui::Checkbox("Collectables", &Config::ESP::collectables);
                        if (Config::ESP::collectables) {
                            ImGui::Indent(16.0f);
                            ImGui::Checkbox("Wood C", &Config::ESP::woodCollectable);
                            colorEditor("Wood C Color", wood_color);
                            ImGui::Checkbox("Stone C", &Config::ESP::stoneCollectable);
                            colorEditor("Stone C Color", stone_color);
                            ImGui::Checkbox("Metal C", &Config::ESP::metalCollectable);
                            colorEditor("Metal C Color", metal_color);
                            ImGui::Checkbox("Sulfur C", &Config::ESP::sulfurCollectable);
                            colorEditor("Sulfur C Color", sulfur_color);
                            ImGui::Unindent(16.0f);
                        }
                        else {
                            Config::ESP::woodCollectable = false;
                            Config::ESP::stoneCollectable = false;
                            Config::ESP::metalCollectable = false;
                            Config::ESP::sulfurCollectable = false;
                        }
                        ImGui::Checkbox("Hemp", &Config::ESP::hemp);
                        colorEditor("ESP Hemp Color", hemp_color);
                        ImGui::Checkbox("Corpses", &Config::ESP::corpses);
                        colorEditor("ESP Corpse Color", corpse_color);
                        ImGui::Checkbox("Dropped Items", &Config::ESP::dropped);
                        colorEditor("ESP Dropped Color", dropped_color);
                        ImGui::Checkbox("Unknown entities", &Config::ESP::unknown);
                        colorEditor("ESP Unknown Color", unknown_color);

                        ImGui::Unindent(16.0f);
                        ImGui::Separator();
                        ImGui::Indent(16.0f);
                        ImGui::Checkbox("Distances", &Config::ESP::distances);
                        ImGui::SliderFloat("Max ESP Distance", &Config::ESP::maxDistance, 0.f, 400.f, "%.0f m");
                        ImGui::Unindent(16.0f);
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Radar"))
                {
                    ImGui::Checkbox("Radar", &Config::Radar::show);
                    colorEditor("Radar Background Color", radar_color);
                    ImGui::Indent(16.0f);
                    if (Config::Radar::show)
                    {
                        ImGui::Checkbox("Players", &Config::Radar::players);
                        colorEditor("Radar Players Color", player_color);
                        if (Config::Radar::players)
                        {
                            ImGui::Indent(16.0f);
                            ImGui::Checkbox("Sleepers", &Config::Radar::sleepers);
                            colorEditor("Radar Sleeper Color", sleeper_color);
                            ImGui::Checkbox("Player Names", &Config::Radar::names);
                            ImGui::Checkbox("Player Teams", &Config::Radar::team);
                            ImGui::Checkbox("Hide Teammates", &Config::Radar::hideTeam);
                            colorEditor("Radar Teammate Color", teammate_color);
                            ImGui::Unindent(16.0f);
                        }
                        ImGui::Checkbox("Barrels", &Config::Radar::barrels);
                        colorEditor("Radar Barrel Color", barrel_color);
                        ImGui::Checkbox("Crates", &Config::Radar::crates);
                        colorEditor("Radar Crate Color", crate_color);
                        ImGui::Checkbox("Raid Items (TCs/Boxes)", &Config::Radar::raid);
                        colorEditor("Radar TCs Color", raid_color);
                        ImGui::Checkbox("Food", &Config::Radar::food);
                        colorEditor("Radar Food Color", food_color);
                        ImGui::Checkbox("Scientists", &Config::Radar::scientists);
                        colorEditor("Radar Scientist Color", scientist_color);
                        ImGui::Checkbox("Animals", &Config::Radar::animals);
                        colorEditor("Radar Animal Color", animal_color);
                        ImGui::Checkbox("Nodes", &Config::Radar::nodes);
                        if (Config::Radar::nodes) {
                            ImGui::Indent(16.0f);
                            ImGui::Checkbox("Wood", &Config::Radar::wood);
                            colorEditor("Wood Color", wood_color);
                            ImGui::Checkbox("Stone", &Config::Radar::stone);
                            colorEditor("Stone Color", stone_color);
                            ImGui::Checkbox("Metal", &Config::Radar::metal);
                            colorEditor("Metal Color", metal_color);
                            ImGui::Checkbox("Sulfur", &Config::Radar::sulfur);
                            colorEditor("Sulfur Color", sulfur_color);
                            ImGui::Unindent(16.0f);
                        }
                        else {
                            Config::Radar::wood = false;
                            Config::Radar::stone = false;
                            Config::Radar::metal = false;
                            Config::Radar::sulfur = false;
                        }
                        ImGui::Checkbox("Collectables", &Config::Radar::collectables);
                        if (Config::Radar::collectables) {
                            ImGui::Indent(16.0f);
                            ImGui::Checkbox("Wood C", &Config::Radar::woodCollectable);
                            colorEditor("Wood C Color", wood_color);
                            ImGui::Checkbox("Stone C", &Config::Radar::stoneCollectable);
                            colorEditor("Stone C Color", stone_color);
                            ImGui::Checkbox("Metal C", &Config::Radar::metalCollectable);
                            colorEditor("Metal C Color", metal_color);
                            ImGui::Checkbox("Sulfur C", &Config::Radar::sulfurCollectable);
                            colorEditor("Sulfur C Color", sulfur_color);
                            ImGui::Unindent(16.0f);
                        }
                        else {
                            Config::Radar::woodCollectable = false;
                            Config::Radar::stoneCollectable = false;
                            Config::Radar::metalCollectable = false;
                            Config::Radar::sulfurCollectable = false;
                        }
                        ImGui::Checkbox("Hemp", &Config::Radar::hemp);
                        colorEditor("Radar Hemp Color", hemp_color);
                        ImGui::Unindent(16.0f);
                        ImGui::Separator();
                        ImGui::Indent(16.0f);
                        ImGui::Checkbox("Distances", &Config::Radar::distances);
                        ImGui::SliderFloat("Size", &Config::Radar::size, 0.0f, 1.0f, "Scale: %.2f");
                        ImGui::SliderFloat("Zoom", &Config::Radar::zoom, 0.5f, 5.0f, "Scale: %.2f");
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Memory write"))
                {
                    ImGui::Checkbox("Player Chams", &Config::Chams::Player::show);

                    if (ImGui::Button("Red [Default]"))
                    {
                        Config::Chams::Player::material = Materials::Glow_Red;
                    }

                    if (ImGui::Button("White (visible through walls)"))
                    {
                        Config::Chams::Player::material = Materials::manpad_crt_hdr;
                    }
                    if (ImGui::Button("Mirror (visible through walls)"))
                    {
                        Config::Chams::Player::material = Materials::GlowBlend;
                    }
                    if (ImGui::Button("Gray (visible through walls)"))
                    {
                        Config::Chams::Player::material = Materials::Hidden::Internal_DeferredShading;
                    }

                    if (ImGui::Button("Bright sky blue"))
                    {
                        Config::Chams::Player::material = Materials::LightningBolt;
                    }

                    ImGui::InputScalar("Material ID##player", ImGuiDataType_U32, &Config::Chams::Player::material);

                    ImGui::Separator();

                    ImGui::Checkbox("Scientist Chams", &Config::Chams::Scientist::show);

                    if (ImGui::Button("Red [Default]##scientist"))
                    {
                        Config::Chams::Scientist::material = Materials::Glow_Red;
                    }
                    if (ImGui::Button("White (visible through walls)##scientist"))
                    {
                        Config::Chams::Scientist::material = Materials::manpad_crt_hdr;
                    }
                    if (ImGui::Button("Mirror (visible through walls)##scientist"))
                    {
                        Config::Chams::Scientist::material = Materials::GlowBlend;
                    }
                    if (ImGui::Button("Gray (visible through walls)##scientist"))
                    {
                        Config::Chams::Scientist::material = Materials::Hidden::Internal_DeferredShading;
                    }
                    if (ImGui::Button("Bright sky blue##scientist"))
                    {
                        Config::Chams::Scientist::material = Materials::LightningBolt;
                    }

                    ImGui::InputScalar("Material ID##scientist", ImGuiDataType_U32, &Config::Chams::Scientist::material);

                    ImGui::Separator();

                    ImGui::SliderFloat("[100% = Normal Recoil]", &Config::RCS::percentage, 0.0f, 100.0f, "%.0f%%");

                    if (ImGui::Button("Apply Recoil")) {
                        RandomizeRecoil();
                    }

                    ImGui::Text("Held item: %s", local_player.held_item.c_str());
                    ImGui::Text("Applied Recoil (Randomized):");
                    ImGui::Text("Yaw Min: %.2f | Yaw Max: %.2f", lastAppliedRecoil.yaw_min, lastAppliedRecoil.yaw_max);
                    ImGui::Text("Pitch Min: %.2f | Pitch Max: %.2f", lastAppliedRecoil.pitch_min, lastAppliedRecoil.pitch_max);

                    ImGui::Separator();

                    if (ImGui::Button("Remove Sway"))
                    {
                        ToggleSway();
                    }

                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Settings"))
                {
                    ImGui::Checkbox("Crosshair", &Config::Misc::crosshair);
                    colorEditor("Crosshair Color", crosshair_color);
                    if (Config::Misc::crosshair)
                    {
                        ImGui::Indent(16.0f);
                        ImGui::SliderFloat("Crosshair Size", &Config::Misc::crosshairSize, 0.0f, 30.0f, "Scale: %.2f");
                        ImGui::Unindent(16.0f);
                    }
                    ImGui::Separator();
                    ImGui::SliderInt("Overlay FPS Limit", &Config::Misc::fps, 1, 300, "%d fps");
                    ImGui::Separator();
                    if (ImGui::SliderInt("Opacity", &Config::Misc::opacity, 0, 1))
                    {
                        colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, Config::Misc::opacity);
                        colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.07f, 0.24f, Config::Misc::opacity);
                        colors[ImGuiCol_TitleBgActive] = ImVec4(0.24f, 0.11f, 0.31f, Config::Misc::opacity);
                    }
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
            ImGui::End();
        }

        ImGui::Render();
        const float clear_color_with_alpha[4] = { 0.f, 0.f, 0.f, 1.f };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(0, 0);

        // Simple FPS limit logic
        auto now = std::chrono::high_resolution_clock::now();
        float desiredFrameTime = 1.0f / static_cast<float>(Config::Misc::fps);
        float elapsed = std::chrono::duration<float>(now - lastFrameTime).count();
        if (elapsed < desiredFrameTime)
        {
            float msToSleep = (desiredFrameTime - elapsed) * 1000.f;
            if (msToSleep > 1.f)
                std::this_thread::sleep_for(std::chrono::milliseconds((int)msToSleep));
        }
        lastFrameTime = std::chrono::high_resolution_clock::now();
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}