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

#include "Constants.h"

namespace MpqLib
{
	namespace Mpq
	{
		/// <summary>
		/// An immutable file information. Is used to retrieve information
		/// about files in the archive without explicitly opening them.
		/// </summary>
		public ref class CFileInfo sealed
		{
			public:
				/// <summary>
				/// Parameterized constructor.
				/// </summary>
				/// <param name="FileName">The filename to use</param>
				/// <param name="Size">The size to use</param>
				/// <param name="CompressedSize">The compressed size to use</param>
				CFileInfo(System::String^ FileName, System::Int32 Size, System::Int32 CompressedSize);

				/// <summary>
				/// Retrieves the filename.
				/// </summary>
				property System::String^ FileName { System::String^ get(); }

				/// <summary>
				/// Retrieves the size (the size of the real, exported file).
				/// </summary>
				property System::Int32 Size { System::Int32 get(); }

				/// <summary>
				/// Retrieves the compressed size (the size of the file stored in the archive).
				/// </summary>
				property System::Int32 CompressedSize { System::Int32 get(); }

			private:
				System::String^ _FileName;
				System::Int32 _Size;
				System::Int32 _CompressedSize;
		};
	}
}
