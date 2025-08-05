#ifndef OFFSETS_H
#define OFFSETS_H

constexpr uint64_t il2cppGCHandleBase = 0xE7C3AC0;
constexpr uint64_t BaseNetworkableOffset = 0xE4FB7E8;
constexpr uint64_t cameraManagerOffset = 0xE506248;

// bn chain
constexpr uint64_t staticBaseNetOffset = 0xB8;
constexpr uint64_t wrapperPtrOffset = 0x10;
constexpr uint64_t parentStaticOffset = 0x10;
constexpr uint64_t objectDictionaryOffset = 0x20;

// camera chain
constexpr uint64_t cameraStaticOffset = 0xB8;
constexpr uint64_t cameraObjectOffset = 0x60;
constexpr uint64_t cameraOffset = 0x10;

constexpr uint64_t entityListSizeOffset = 0x18;
constexpr uint64_t entityListBaseOffset = 0x10;

constexpr uint64_t matrixOffset = 0x30C;

namespace Offsets {
	namespace BasePlayer {
		constexpr uint64_t playerModel = 0x3B0; // public PlayerModel
		constexpr uint64_t currentTeam = 0x400; // public ulong
		constexpr uint64_t clActiveItem = 0x430; // private BasePlayer.EncryptedValue<ItemId>
		constexpr uint64_t playerFlags = 0x530; // public BasePlayer.PlayerFlags
		constexpr uint64_t inventoryValue = 0x4D0; // private BasePlayer.HiddenValue<PlayerInventory>
		constexpr uint64_t _displayName = 0x5F8; // protected string
	}

	namespace PlayerModel {
		constexpr uint64_t position = 0x1D8; // internal Vector3
		constexpr uint64_t _multiMesh = 0x3C8; // private SkinnedMultiMesh
	}

	namespace SkinnedMultiMesh {
		constexpr uint64_t renderersList = 0x58; // private readonly List<Renderer>
	}

	namespace PlayerInventory {
		constexpr uint64_t containerBelt = 0x60; // public ItemContainer
	}

	namespace BaseCombatEntity {
		constexpr uint64_t lifestate = 0x214; // public BaseCombatEntity.LifeState
	}

	namespace Item {
		constexpr uint64_t info = 0x88; // public ItemDefinition
	}

	namespace ItemContainer {
		constexpr uint64_t itemList = 0x58; // public List<Item>
	}

	namespace ItemDefinition {
		constexpr uint64_t itemid = 0xA0; // public int
		constexpr uint64_t displayName = 0x38; // public Translate.Phrase
	}

	namespace TranslatePhrase {
		constexpr uint64_t english = 0x18; // public string
	}
}

//find types and classes for these and organize
constexpr uint64_t BaseViewModelOffset = 239909544;
constexpr uint64_t ViewModelListOffset = 0xD8; // public static List<BaseViewModel> %3f9aacc07cd7cf77136147db7ebf3493742812ae; // 0x1A0 RECLASS
constexpr uint64_t AnimationEventsOffset = 0xE0; //Non static ->  	internal AnimationEvents %24666129ef4e1a3d1804f08987a98ee991162d44; // 0xC0
constexpr uint64_t heldEntityOffset = 0x28; //public HeldEntity targetEntity; // 0x28
constexpr uint64_t RecoilPropertiesOffset = 0x330; //public class BaseProjectile -> RecoilProperties

extern uintptr_t gameAssemblyBase;
bool checkBit(uint32_t Value, uint32_t BitPosition);
uint64_t decryptIl2cppHandle(int32_t ObjectHandleID);
uintptr_t BaseNetworkable(uintptr_t Address);
uintptr_t Ulong(uintptr_t a1);
std::uint64_t decrypt_inventory_pointer(std::uint64_t a1);
uint64_t c_decrypt_uint32_t(uint64_t a1);
#endif