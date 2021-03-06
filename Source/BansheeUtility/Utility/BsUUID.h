//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "Prerequisites/BsPlatformDefines.h"
#include "String/BsString.h"
#include "Prerequisites/BsTypes.h"
#include "Prerequisites/BsRTTIPrerequisites.h"
#include "Utility/BsUtil.h"

namespace bs
{
	/** @addtogroup Utility-Core
	 *  @{
	 */

	/** Represents a universally unique identifier. */
	struct BS_UTILITY_EXPORT UUID
	{
		/** Initializes an empty UUID. */
		UUID()
			: mData()
		{ }

		/** Initializes an UUID using Banshee's UUID representation. */
		UUID(UINT32 data1, UINT32 data2, UINT32 data3, UINT32 data4)
		{
			mData[0] = data1;
			mData[1] = data2;
			mData[2] = data3;
			mData[3] = data4;
		}

		/** Initializes an UUID using its string representation. */
		explicit UUID(const String& uuid);

		bool operator==(const UUID& rhs) const
		{
			return mData[0] == rhs.mData[0] && mData[1] == rhs.mData[1] && mData[2] == rhs.mData[2] && mData[3] == rhs.mData[3];
		}

		bool operator!=(const UUID& rhs) const
		{
			return !(*this == rhs);
		}

		bool operator<(const UUID& rhs) const
		{
			for(UINT32 i = 0; i < 4; i++)
			{
				if (mData[i] < rhs.mData[i])
					return true;
				else if (mData[i] > rhs.mData[i])
					return false;

				// Move to next element if equal
			}

			// They're equal
			return false;
		}

		/** Checks has the UUID been initialized to a valid value. */
		bool empty() const
		{
			return mData[0] == 0 && mData[1] == 0 && mData[2] == 0 && mData[3] == 0;
		}

		/** Converts the UUID into its string representation. */
		String toString() const;

		static UUID EMPTY;
	private:
		friend struct std::hash<UUID>;

		UINT32 mData[4];
	};

	BS_ALLOW_MEMCPY_SERIALIZATION(UUID)

	/**
	 * Utility class for generating universally unique identifiers.
	 *
	 * @note	Thread safe.
	 */
	class BS_UTILITY_EXPORT UUIDGenerator
	{
	public:
		/**	Generate a new random universally unique identifier. */
		static UUID generateRandom();
	};

	/** @} */
}

/** @cond STDLIB */
/** @addtogroup Utility
 *  @{
 */

namespace std
{
/**	Hash value generator for UUID. */
template<>
struct hash<bs::UUID>
{
	size_t operator()(const bs::UUID& value) const
	{
		size_t hash = 0;
		bs::hash_combine(hash, value.mData[0]);
		bs::hash_combine(hash, value.mData[1]);
		bs::hash_combine(hash, value.mData[2]);
		bs::hash_combine(hash, value.mData[3]);

		return hash;
	}
};
}

/** @} */
/** @endcond */