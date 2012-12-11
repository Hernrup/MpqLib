//+-----------------------------------------------------------------------------
//|
//| Copyright (C) 2008, Magnus Ostberg, aka Magos
//| Contact: MagosX@GMail.com, http://www.magosx.com
//|
//| This file is part of MpqLib.
//| MpqLib is a library to manipulate (open, read, write) MoPaQ archives and
//| its contained files for the game WarCraft 3. It can (and is supposed to)
//| be freely used in tools and programs made by other developers.
//|
//| WarCraft is a trademark of Blizzard Entertainment, Inc.
//|
//| MpqLib is free software: you can redistribute it and/or modify
//| it under the terms of the GNU General Public License as published by
//| the Free Software Foundation, either version 3 of the License, or
//| (at your option) any later version.
//|
//| MpqLib is distributed in the hope that it will be useful,
//| but WITHOUT ANY WARRANTY; without even the implied warranty of
//| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//| GNU General Public License for more details.
//|
//| You should have received a copy of the GNU General Public License
//| along with MpqLib. If not, see <http://www.gnu.org/licenses/>.
//|
//| This header must remain unaltered if changes are made to the file.
//| Additional information may be added as needed.
//|
//+-----------------------------------------------------------------------------
#pragma once

//Disables the literal warning/error bug, as explained at:
//https://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=282773
#pragma warning(push)
#pragma warning(disable:4693)

#include "Include.h"

namespace MpqLib
{
	/// <summary>
	/// Contains all (global) constants.
	/// </summary>
	public ref class CConstants abstract sealed
	{
		public:
			/// <summary>
			/// Represents an invalid ID.
			/// </summary>
			literal int InvalidId = -1;

			/// <summary>
			/// Represents an invalid index.
			/// </summary>
			literal int InvalidIndex = -1;

		internal:
			literal System::UInt32 DefaultHashTableSize = 32;
	};
}

#pragma warning(pop)
